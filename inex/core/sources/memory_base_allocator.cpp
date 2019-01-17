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

} // namespace ui
} // namespace memory
