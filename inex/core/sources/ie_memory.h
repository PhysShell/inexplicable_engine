#ifndef INEX_MEMORY_H_INCLUDED
#	define INEX_MEMORY_H_INCLUDED

namespace inex {
namespace memory {

void 	preinitialize				( );
void 	initialize					( );
void    finalize        			( );

inline
pvoid 	require_arena_from_os		( size_t const size );

INEX_CORE_API
pvoid   memory_allocate				( size_t size, pcstr name = 0 );
INEX_CORE_API
void    memory_free					( pvoid pointer );
void    memory_register_pointer		( pvoid pointer, pcstr type );
void    memory_unregister_pointer	( pvoid pointer );
void    memory_check_pointer		( );
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

inline
INEX_CORE_API
void	copy ( pvoid const destination, size_t const destination_size, pcvoid const source, size_t const size )
{
	INEX_UNREFERENCED_PARAMETERS( destination_size );
	ASSERT_S					( destination_size >= size );
	memcpy						( destination, source, size );
}

} // namespace memory
} // namespace inex

#include "ie_memory_inline.h"

//namespace inex {
//    using core::memory::ie_new;
//    using core::memory::ie_delete;
//}
#endif //#ifndef INEX_MEMORY_H_INCLUDED
