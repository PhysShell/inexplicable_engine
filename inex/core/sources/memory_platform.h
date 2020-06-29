////////////////////////////////////////////////////////////////////////////
//	Created 	: 17.01.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MEMORY_PLATFORM_H_INCLUDED
#	define MEMORY_PLATFORM_H_INCLUDED

namespace inex {
namespace memory {
namespace platform {

struct region
{
	u64		size;
	pvoid	address;
}; // struct region

pvoid	allocate_raw_arena	( size_t const size );

} // namespace platform
} // namespace memory
} // namespace inex

#endif // #ifndef MEMORY_PLATFORM_H_INCLUDED
