#include "stdafx.h"
#include "memory_general_allocator.h"


namespace inex {
namespace memory {

//general_allocator::general_allocator ( ) :

inline
s64  pointer_difference ( pvoid begin, pvoid end )
{
    return  s64
                (
                    reinterpret_cast< pstr > ( end )
                    - reinterpret_cast< pstr > ( begin )
                );
}

static general_allocator::header base;
static size_t                    end;
pvoid                           end_p;

void    general_allocator::initialize ( pvoid arena, size_t const size, pcstr id )
{
    if( !( 16 == 16UL ) )
            exit( 1 );

    ASSERT_D(   ( INEX_ALIGNOF( header ) /* % */ == alignment_value ),
                "Alignment expectation isn't met.\nNeeded:\t%d\nGotten:\t%d",
                alignment_value,
                INEX_ALIGNOF( header ) );

    m_arena_id               = id;
    // m_arena->size            = size;
    // m_arena                  = arena ? ( header* )arena : nullptr;
    // m_last_allocated         = m_arena;
    m_last_allocated            = nullptr;

    logging::Msg(   "* General allocator of size:\t%d\n "
                    "with address:\t\t\t\t%p named '%s' created.",
                    0,
                    &base,
                    m_arena_id );

    sizeof ( &base ); sizeof ( header );
}

inline
u64     bits_to_bytes ( u64 value )
{
    return              value / __CHAR_BIT__;
}

pvoid    general_allocator::malloc_impl ( size_t const size )
{
    ASSERT_D( 0, "Malloc implementation is not yet working correctly" );
    header          * p, *previous;
    // size in bytes. + 1 byte for housekeeper
    size_t          units =
    { ( size + sizeof ( header ) + 1 ) / sizeof ( header ) + 1 };
    LOGGER( "\n* Computed:\t%d bytes to be allocated from '%d' bits.", units, size );

    if ( ( previous = m_last_allocated ) == nullptr )
    {
        base.next   = m_last_allocated = previous = &base;
        base.size   = 0ul;
    }

    for ( p = previous->next; ; previous = p, p = p->next )
    {
        ASSERT_D( m_last_allocated == previous,
                "* Last allocated:\t%p, next:\t%p", m_last_allocated, previous );

        LOGGER( 
                "* Last allocated:\t%p, next:\t%p", m_last_allocated, previous );


        LOGGER( "*\n Size of block:\t%d.", p->size, units );
        LOGGER( "* Last allocated:\t%p", previous );
        LOGGER( "* previous->next:\t'%p'", p );
        if ( p->size >= units )
        {
            if ( p->size == units  )
            {
                ASSERT_S( 1 != 1 );
                previous->next  = p->next;
            }
            else
            {
                LOGGER( "* chunk not match but appropriate" );
                p->size         -=  units;
                LOGGER( "need to slide by %d bytes\n", p->size );
                // LOGGER( "p = %p", p );

                LOGGER( "* BYTES p->size:\t%d, Needed p->size:\t%d", p->size, p->size / 2 );

                //p->size                     = bits_to_bytes( p->size );
                p                           += ( p->size / 2 );

                s64   local_difference       = pointer_difference( end_p, p );
                //LOGGER( "ptrdiff should be negative: %d", local_difference );

                ASSERT_D( local_difference <= 0, "Out of bones %d bytes. Exceeded value: %d", end,
                        local_difference );

                LOGGER( "* New housekeeper is at: '%p'",  ( header* ) ( p ) );
                LOGGER( "* chunk starts at: '%p'",  ( header* ) ( p + 1 ) );
                LOGGER( "*\tends at:\t'%p'", ( header* ) p + units );

                ( *p ).size         =    units;
                LOGGER( "* BYTES p->size:\t%d, BITS p->size:\t%d", p->size, p->size * 8 );
                LOGGER( "Units %d bytes", p->size );
                INEX_DEBUG_WAIT;
            }

            // correct iteration might not be possible,
            // should maybe use p->next = base to make point to beginning

            for ( header* ptr = m_last_allocated; ; )
            {
                LOGGER( "Ptr:\t'%p' ( next: '%p' ). Sz:\t'%d'", ptr, ptr->next, ptr->size );
                if ( ( ptr = ptr->next ) == m_last_allocated )             break;
                INEX_DEBUG_WAIT;
            }

            ASSERT_D            (   ( u64 ) ( p + 1 ) % alignment_value == 0,
                                    "%p reaminder !=0 %d",
                                    p + 1, ( u64 ) ( p + 1 ) % alignment_value );
                                
            m_last_allocated    = previous;
            //m_last_allocated    ->next  = p;
            return              ( pvoid ) ( p + 1 );
        }

        if ( p == m_last_allocated )
        {
            LOGGER( "* p == m_last_allocated happened" );
            p                       = on_malloc( units );
            if ( base.size == 0 )
            {
                base.size           = p->size;
                p->next             = &base;
                m_last_allocated    = p;
                m_last_allocated    ->next              = p;
                //base.next           = p->next;

                // LOGGER( "base next:\t'%p'", base.next );
            }
            // here previous==previous->next==base!! so need to work it around above
            //m_last_allocated            =   previous->next;
        }
    }
}

general_allocator::header*   general_allocator::on_malloc ( size_t const size )
{
        s32 constexpr new_size  = 512 * sizeof( header );
        size_t units            = size;
        if ( size < new_size )  units                   = new_size;
        pvoid raw_region        = require_arena_from_os( units );
        LOGGER( "*\tAllocating new chunk:\t%d bytes, at %p.", new_size, raw_region );
        LOGGER( ( u64 )raw_region % alignment_value ? "!\tNot aligned by %d bytes."
                : "*\tAligned by %d bytes.", alignment_value );
        header* blocks_allocated = ( header* )raw_region;
        blocks_allocated->size  = bits_to_bytes( new_size );
        end                     =  pointer_difference( raw_region, ( pvoid ) ( (  ptrdiff_t ) raw_region + new_size ) );
        end_p                   = ( pstr )raw_region + new_size;
        LOGGER( "* contains :\t%d bytes. ends at:\t%p", end, end_p );
        //blocks_allocated->next  = nullptr;
        //free                    ( ( pvoid ) ( blocks_allocated + 1 ) );
        //sizeof ( header );
        //memset                  ( ( pvoid ) ( blocks_allocated + 1 ), 0, units - sizeof( header ) );
        // LOGGER (    "* Zeroed '%d' bytes, staring form: '%p'.",
        //             units - sizeof( header ),
        //             blocks_allocated + 1 );

        return                  blocks_allocated;
}

/**
 * It frees the end of the memory allocated, not start
**/
void    general_allocator::free_impl ( pvoid block )
{
    header   * bp, * p;
    bp                      = ( header* ) block - 1;
    // printf ( "pvoid:\t%p\nheader:\t%p\n", ( pvoid ) bp, ( header* ) block - 1 );
    LOGGER( "* Freeing the chunk of:\t%d bytes, at %p.", bp->size, bp );
    LOGGER( "* Actual pointer:\t at %p.", block );
    size_t len              = strlen( ( pstr ) block );
    if ( len > ( bp->size ) * __CHAR_BIT__  )
    {
        LOGGER( "! Warning: '%p' overflowes its '%d' bytes: usage '%d' bits.",
                block,
                bp->size - 1,
                len );

        if ( ( !bp->next ) == 1 ) { LOGGER( "NPTR" ); }
    }

    for (   p               = m_last_allocated;
            !( bp > p && bp < p->next );
            p               = p->next )
    {
        if ( p >= p->next && ( bp > p || bp < p->next ) )   break;
    }

    if ( bp + bp->size == p->next )
    {
        bp->size            +=  p->next->size;
        bp->next            =   p->next->next;
    }
    else
    {
        bp->next            =   p->next;
    }

    if ( p + p->size == bp )
    {
        p->size             +=  bp->size;
        p->next             =   bp->next;
    }
    else
    {
        p->next             =   bp;
    }

    m_last_allocated        =   p;


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
