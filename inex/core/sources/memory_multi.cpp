#include "stdafx.h"
#include "memory_platform.h"

namespace inex {
namespace memory {
namespace platform {

pvoid	allocate_raw_arena	( size_t const size )
{
	pvoid 				arena;
	return 				( arena = std::malloc ( size ) ) ? arena : nullptr ;
}

} // namespace platform
} // namespace memory
} // namespace inex