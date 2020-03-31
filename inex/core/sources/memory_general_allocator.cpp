#include "stdafx.h"
#include "memory_general_allocator.h"


namespace inex {
namespace memory {

#ifdef DEBUG_MEMORY_MANAGER
#   ifdef LOGGER
#       undef LOGGER
#   endif // #ifdef LOGGER
#   define LOGGER( ... )	inex::logging::Msg( __VA_ARGS__ ); printf( __VA_ARGS__ ); printf( "%s", "\n" );
#endif // #ifdef DEBUG_MEMORY_MANAGER

//general_allocator::general_allocator ( ) :

inline
u64     bits_to_bytes ( u64 value )
{
    return              value / __CHAR_BIT__;
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

    logging::Msg(   "* General allocator of size:\t%d\n "
                    "with address:\t\t\t\t%p named '%s' created.",
                    0,
                    m_arena,
                    m_arena_id );
}

pvoid	general_allocator::malloc_impl ( u32 size )
{
    LOGGER( "--------------------------------------------------" );
    header_type *p, *prevp;
    u32 nunits;
    nunits = (size+sizeof(header_type)-1)/sizeof(header_type) + 1;
    if ( ( prevp = m_arena_end ) == nullptr )
    {
        m_arena->s.ptr	= m_arena_end = prevp = m_arena;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits)		/*   */
        {
            if (p->s.size == nunits)	/*   */
                prevp->s.ptr = p->s.ptr;
            else						/*  "" */
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }

        m_arena_end = prevp;
        return ( pvoid )( p + 1 );
    }

    if ( p == m_arena_end ) /*     */
        p = on_malloc( nunits );
    }
}

general_allocator::header_type* general_allocator::on_malloc ( unsigned nu )
{
    LOGGER( "ask for more memory" );
    char *cp;
    header_type *up;
    if ( m_helper && nu < m_helper->s.size )
    {
        LOGGER( "needed %d, available %d", nu, m_helper->s.size);

        nu						= m_helper->s.size;
        cp						= ( pstr )m_helper->s.ptr;

        LOGGER( "+++++++%p", m_helper->s.ptr );
        memory::ie_delete		( m_helper );
        goto allocation_finished_goto;
    }
    else
    {
        LOGGER( "preallocated memory is useless" );
        // preallocated memory is useless
        if ( m_helper )
        {
            free					( m_helper->s.ptr );
            memory::ie_delete		( m_helper );
        }

    }

    LOGGER( "***Allocating from OS!***" );
    if ( nu < 1024 )
        nu      = 1024;
    cp          = ( pstr )memory::require_arena_from_os( nu * sizeof( header_type ) );
    
    /***********************/
    allocation_finished_goto:
    /***********************/

    // already checked in memory::require_arena_from_os
    // if ( cp == 0 ) /*     */
    // 	ASSERT_S( 0 );

    up          = ( header_type * ) cp;
    up->s.size  = nu;
    free_impl   ( pvoid ( up + 1 ) );
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
}

void	general_allocator::finalize		( )
{
    memory::ie_delete	( m_arena );
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
