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

    sizeof ( &base ); sizeof ( header );
}

pvoid    general_allocator::malloc_impl ( size_t const size )
{
    LOGGER          ( "*****\tMALLOC IMPL\t******" );
    header          * p, *previous;
    // size in bytes. + 1 byte for housekeeper
    size_t          units =
    { ( size + sizeof ( header ) + 1 ) / sizeof ( header ) + 1 };
    LOGGER( "* Computed:\t%d bytes to be allocated from '%d' bits.", units, size );

    //LOGGER( "previous:\t'%p'", previous );

    // m_last_allocated should point to last allocated
    // and previous->next should point to what?
    // new header, cuz it implies that if 'for'
    // 
    if ( ( previous = m_last_allocated ) == nullptr )
    {
        LOGGER( "PREVIOUS is 0000" );
        base.next   = m_last_allocated = previous = &base;
        base.size   = 0ul;
    }

    //LOGGER( "m_last_allocated:\t'%p'", m_last_allocated->next );
    // not moving pointer up the stack!!!!

    // need to get previous->next to point to m_last_allocated...


    for ( p = previous->next; ; previous = p, p = p->next )
    {
        ASSERT_D( m_last_allocated == previous,
                "* Last allocated:\t%p, prev:\t%p", m_last_allocated, previous );

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

                p               +=  units; // make it point to beginning of new chunk
                LOGGER( "* New housekeeper is at: '%p'",  ( header* ) ( p ) );
                // LOGGER( "* chunk starts at: '%p'",  ( header* ) ( p + 1 ) );
                // LOGGER( "*\tends at:\t'%p'", ( header* ) p + units );
                p->size         =   units;

                //previous->next      = p;
                //LOGGER( "\nprevious->next:\t'%p'", previous->next );
            }

            //p->next             = &base;

            // previous            = p;
            //previous            = p;

            // 111previous            = m_last_allocated;

            // p->next             = &base;
            // p->next->size             = 100;

            //previous->size              = units;
            // previous->next              = &base;

            for ( header* ptr = &base; ; )
            {
                LOGGER( "Ptr:\t'%p' ( next: '%p' ). Sz:\t'%d'", ptr, ptr->next, ptr->size );
                if ( ( ptr = ptr->next ) == &base )             break;
                INEX_DEBUG_WAIT;
            }



            // LOGGER( "***prev->size:\t'%d', prev->next->size:\t'%d'", previous->size,
            //                                                         previous->next->size );


            // LOGGER( "*\prev:\t'%p'\n*\tprev->nex:\t'%p'", previous, previous->next );

            // LOGGER( "***prev->size:\t'%d', prev->next->size:\t'%d'", previous->size,
            //                                                         previous->next->size );
            //m_last_allocated    = p;
           // previous
            
            //LOGGER( )
            return              ( pvoid ) ( p + 1 );
        }

        if ( p == m_last_allocated )
        {
            LOGGER( "* p == m_last_allocated happened" );
            p                       = on_malloc( units );
            if ( base.size == 0 )
            {
                base.size           = p->size;
                p->next       = &base;
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
        blocks_allocated->size  = new_size;
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
