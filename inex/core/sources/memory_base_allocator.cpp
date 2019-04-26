#include "stdafx.h"
#include "memory_base_allocator.h"


namespace inex {
namespace memory {

base_allocator::base_allocator ( ) :
    m_arena_id  ( nullptr )
{
}

void    base_allocator::initialize ( pvoid arena, size_t const size, pcstr id )
{
}

void    base_allocator::finalize (  )
{
}

pvoid    base_allocator::malloc_impl ( size_t const size )
{
	return				0;
}

void    base_allocator::free_impl ( pvoid )
{
}

} // namespace memory
} // namespace inex
