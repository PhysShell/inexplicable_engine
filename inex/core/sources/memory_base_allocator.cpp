#include "stdafx.h"
#include "memory_base_allocator.h"


namespace inex {
namespace memory {

base_allocator::base_allocator ( ) :
    m_arena     ( nullptr ),
    m_arena_end ( nullptr ),
    m_arena_id  ( nullptr )
{
}

void	base_allocator::initialize (  )

} // namespace ui
} // namespace memory
