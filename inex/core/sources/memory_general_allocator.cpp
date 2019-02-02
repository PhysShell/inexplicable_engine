#include "stdafx.h"
#include "memory_general_allocator.h"


namespace inex {
namespace memory {

void    general_allocator::initialize ( pvoid arena, size_t const size, pcstr id )
{
    m_arena                 = arena;
    m_arena_end             = ( u8 * ) arena + size;
    m_arena_id              = id;
    // now i need linked list.......
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
