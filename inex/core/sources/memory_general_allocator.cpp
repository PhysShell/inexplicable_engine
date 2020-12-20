#include "pch.h"
#include "memory_general_allocator.h"


namespace inex {
namespace memory {

// #ifdef DEBUG_MEMORY_MANAGER
// #   ifdef LOGGER
// #       undef LOGGER
// #   endif // #ifdef LOGGER
// #   define LOGGER( ... )	inex::logging::Msg( __VA_ARGS__ ); printf( __VA_ARGS__ ); printf( "%s", "\n" );
// #endif // #ifdef DEBUG_MEMORY_MANAGER

//general_allocator::general_allocator ( ) :

constexpr static u32 Kb = 1024;
constexpr static u32 Mb = 1048576;

// dummy type to be registered in memory leak detector
struct general_allocator_user_memory { };

inline
u64     bits_to_bytes ( u64 value )
{
    return              value / 8;
}

inline
s64  pointer_difference ( pvoid begin, pvoid end )
{
    return  s64
                (
                    reinterpret_cast< pstr > ( end )
                    - reinterpret_cast< pstr > ( begin )
                );
}

general_allocator::general_allocator ( ) :
    m_arena     ( ),
    m_arena_end ( nullptr )
{
    m_monitor.size  = m_monitor.deallocations = m_monitor.allocations   = 0;
}

void    general_allocator::initialize ( pvoid arena, size_t const size, pcstr id )
{
    if( !( 16 == 16UL ) )
            exit( 1 );

    ASSERT_D(   ( INEX_ALIGNOF( header ) /* % */ == alignment_value ),
                "Alignment expectation isn't met.\nNeeded:\t%d\nGotten:\t%d",
                alignment_value,
                INEX_ALIGNOF( header ) );

    m_arena_id				= id;
    m_arena					=  memory::ie_new< header_type >( );
    m_helper				= 0;
    //m_arena->dummy			= 0;
    if ( arena )
    {
        m_helper				= memory::ie_new< header_type >( );
        size_t s				= (size+sizeof(header_type)-1)/sizeof(header_type) + 1;
        m_helper->s.size		= s;
        m_helper->s.ptr			= ( header_type * )arena;
        LOGGER( "HELPER INFO %p, %d", m_helper->s.ptr, m_helper->s.size );
    }

    // logging::Msg(   "* General allocator of size:\t%d\n "
    //                 "with address:\t\t\t\t%p named '%s' created.",
    //                 0,
    //                 m_arena,
    //                 m_arena_id );

    m_monitor.size  = size;
}

pvoid	general_allocator::malloc_impl ( u32 size )
{
    // LOGGER( "--------------------------------------------------" );
    header_type *p, *prevp;
    u32 nunits;
    nunits      = ( size + sizeof( header_type ) - 1 ) / sizeof( header_type ) + 1;
    if ( ( prevp = m_arena_end ) == nullptr )
    {
        m_arena->s.ptr	        = m_arena_end = prevp = m_arena;
    }

    for ( p = prevp->s.ptr; ; prevp = p, p = p->s.ptr )
    {
        if ( p->s.size >= nunits )		/*   */
        {
            if ( p->s.size == nunits )	/*   */
                prevp->s.ptr    = p->s.ptr;
            else						/*  "" */
            {
                p->s.size       -= nunits;
                p               += p->s.size;
                p->s.size       = nunits;
            }

            m_arena_end         = prevp;
            ++                  m_monitor.allocations;
            pvoid user_memory   = ( pvoid )( p + 1 );
            memory_register_pointer ( user_memory, typeid( general_allocator_user_memory ).name( ) );
            return              user_memory;
        }

        if ( p == m_arena_end )
        {
            ++                  m_monitor.allocations;
            p                   = on_malloc( nunits );
        }
    }

    ASSERT_D( 0, "Memory corruption in general allocator");
}

general_allocator::header_type* general_allocator::on_malloc ( unsigned nu )
{
    // LOGGER( "ask for more memory" );
    char *cp;
    header_type *up;
    if ( m_helper && nu < m_helper->s.size )
    {
        // LOGGER( "needed %d, available %d", nu, m_helper->s.size);

        nu						= m_helper->s.size;
        cp						= ( pstr )m_helper->s.ptr;

        // LOGGER( "+++++++%p", m_helper->s.ptr );
        memory::ie_delete		( m_helper );

        m_monitor.size          += nu;

        goto allocation_finished_goto;
    }
    else
    {
        // LOGGER( "preallocated memory is useless" );
        // preallocated memory is useless
        if ( m_helper )
        {
            free					( m_helper->s.ptr );
            memory::ie_delete		( m_helper );
        }
    }

    LOGGER( "***Allocating from OS!***" );
    if ( nu < 0.5*Kb )
        nu      = 0.5*Kb ;
    cp          = ( pstr )memory::require_arena_from_os( nu /** sizeof( header_type )*/ );

    /***********************/
    allocation_finished_goto:
    /***********************/

    m_monitor.size          += nu ;//* sizeof( header_type );

    up          = ( header_type * ) cp;
    up->s.size  = nu;
    memory_register_pointer( pvoid( up + 1 ), typeid( general_allocator_user_memory ).name( ) );
    free_impl   ( pvoid ( up + 1 ) );
    --          m_monitor.deallocations;
    return      m_arena_end;
}

void    general_allocator::free_impl ( pvoid ap )
{
    header_type         *bp, *p;
    bp                  = ( header_type * ) ap - 1;
    for ( p = m_arena_end; !( bp > p && bp < p->s.ptr ); p = p->s.ptr )
    {
        if ( p >= p->s.ptr && ( bp > p || bp < p->s.ptr ) )     break;
    }

    if ( bp + bp->s.size == p->s.ptr )
    {
        bp->s.size      += p->s.ptr->s.size;
        bp->s.ptr       = p->s.ptr->s.ptr;
    } else
        bp->s.ptr       = p->s.ptr;

    if ( p + p->s.size == bp )
    {
        p->s.size       += bp->s.size;
        p->s.ptr        = bp->s.ptr;
    } else
        p->s.ptr        = bp;

    m_arena_end         = p;
    memory_unregister_pointer   ( ap );
    ++                  m_monitor.deallocations;
    --                  m_monitor.allocations;
}

void    general_allocator::dump_memory_statistics ( ) const
{
    // the bigger deallocs value, the bigger the fragmented size
    float raw_memory    = m_monitor.size - m_monitor.allocations * sizeof ( header_type );
    float fragmented    = m_monitor.deallocations / raw_memory * 100;
    float size_in_kb    = m_monitor.size;
    size_in_kb          /= 1*Kb;
    LOGGER( "Statistics for '%s' allocator:\n"
            "\tSize: %0.*fKb\n"
            "\tAllocated chunks: '%u'\n"
            "\tDeallocations: '%u'\n"
            "\tFragmentation: '%0.*f'%%\n",
            m_arena_id, 2, size_in_kb, m_monitor.allocations, m_monitor.deallocations, fragmented, 2 );
}

void	general_allocator::finalize		( )
{
    LOGGER( "* Destroying allocator *" );
    dump_memory_statistics  ( );
    memory::ie_delete	    ( m_arena );
}

/*
memory::general_allocator	g_allocator;
memory::platform::region	region;
region.size					= 128;
region.address				= memory::platform::allocate_raw_arena( region.size );
g_allocator.initialize		( region.address, region.size, "filesystem" );
*/

} // namespace memory
} // namespace inex
