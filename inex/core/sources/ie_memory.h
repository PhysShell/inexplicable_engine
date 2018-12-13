#ifndef IE_MEMORY_H_INCLUDED
#	define IE_MEMORY_H_INCLUDED

namespace inex {
namespace core {
namespace memory {

//DEBUG_MEMORY_MANAGER
//

// name is for MEMDBG
pvoid   memory_allocate				( size_t size, pcstr name = 0 );
void    memory_free					( pvoid pointer );
// call these in memory_allocate\dealloc etc
void    memory_register_pointer		( pvoid pointer, pcstr type );
void    memory_unregister_pointer	( pvoid pointer );
void    memory_check_pointer		( );

void    finalize        			( );
void    dump_memory_contents      	( );

template < typename type_allocated >
inline
type_allocated*	ie_allocate ( size_t count, pcvoid = 0 );

template < typename type_allocated >
inline
type_allocated*	ie_new ( );

template < typename type_allocated, typename construction_parameter_1 >
inline
type_allocated*	ie_new ( construction_parameter_1 const& parameter_1 );

template <
	typename type_allocated,
	typename construction_parameter_1,
	typename construction_parameter_2
>
inline
type_allocated*	ie_new (	construction_parameter_1 const&		parameter_1,
							construction_parameter_2 const&		parameter_2 );

template < typename type_allocated >
inline
void	ie_delete ( type_allocated*& pointer );

// what's the reference to const PTRs
template < typename type_allocated >
inline
void	ie_delete ( type_allocated* const& obj );

} // namespace memory
} // names core
} // namespace inex

#include "ie_memory_inline.h"

//namespace inex {
//    using core::memory::ie_new;
//    using core::memory::ie_delete;
//}
#endif //#ifndef IE_MEMORY_H_INCLUDED
