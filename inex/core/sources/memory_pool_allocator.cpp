#include "pch.h"
#include <inex/core/sources/memory_pool_allocator.h>

namespace inex {
namespace memory {

pool_allocator::pool_allocator ( ) :
	m_arena		( ),
	m_monitor	( )
{

}

} // namespace ui
} // namespace memory
