////////////////////////////////////////////////////////////////////////////
//	Created		: 25.10.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MEMORY_FIXED_SIZE_ALLOCATOR_H_INCLUDED
#   define MEMORY_FIXED_SIZE_ALLOCATOR_H_INCLUDED

#   include <inex/core/sources/memory_base_allocator.h>

namespace inex {
namespace memory {

template < typename T, class ThreadPolicy >
class fixed_size_allocator : public base_allocator
{

}; // class fixed_size_allocator

} // namespace memory
} // namespace inex

#endif // #ifndef MEMORY_FIXED_SIZE_ALLOCATOR_H_INCLUDED