#include "stdafx.h"
#include "memory_general_allocator.h"


namespace inex {
namespace memory {

//general_allocator::general_allocator ( ) :

static general_allocator::header base;

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
}

pvoid    general_allocator::malloc_impl ( size_t const size )
{
    header          * p, *previous;
    // size in bytes. + 1 byte for housekeeper
    size_t          units =
    { ( size + sizeof ( header ) + 1 ) / sizeof ( header ) + 1 };
    LOGGER( "* Computed:\t%d bytes to be allocated from '%d' bits.", units, size );

    if ( ( previous = m_last_allocated ) == nullptr )
    {
        base.next   = m_last_allocated = previous = &base;
        base.size   = 0u;
    }

    for ( p = previous->next; ; previous = p, p = p->next )
    {
        LOGGER( "* Size of block:\t%d.", p->size, units );
        if ( p->size >= units )
        {
            if ( p->size == units  )
            {
                previous->next  = p->next;
            }
            else
            {
                LOGGER( "* chunk not match but appropriate" );
                p->size         -=  units;
                //if ( ! ( ( pvoid ) ( p + 1 ) ) )       LOGGER( "ERROR!!!!!" );

                //LOGGER( "* p->size:\t'%d'.", p->size );
                LOGGER( "* need to return chunk at: '%p'", ( pvoid ) ( p + 1 ) );
                // memset( ( pvoid ) ( p + 1 ), 0, size );
                // LOGGER( ( pstr ) p + 1 );
                p               +=  units;
                //INEX_DEBUG_WAIT;
                p->size         =   units;
                //            INEX_DEBUG_WAIT;
            }
            // LOGGER( "* ready to return memory" );
            m_last_allocated    = previous;
            return              ( pvoid ) ( p + 1 );
        }

        if ( p == m_last_allocated )
        {
            // LOGGER( "* p == m_last_allocated happened" );
            m_last_allocated    = on_malloc( units );
            p->next                   = m_last_allocated;
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
        blocks_allocated->size  = new_size;
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
    LOGGER( "* Freeing the chunk of:\t%d bytes, at %p.", bp->size, bp );
    LOGGER( "* Actual pointer:\t at %p.", block );
    size_t len              = strlen( ( pstr ) block );
    if ( len > ( bp->size - 1 ) * __CHAR_BIT__  )
    {
        LOGGER( "! Warning: '%p' overflowes its '%d' bytes: usage '%d' bits.",
                block,
                bp->size - 1,
                len );
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
