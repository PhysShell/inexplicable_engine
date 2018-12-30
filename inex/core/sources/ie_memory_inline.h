#ifndef INEX_MEMORY_INLINE_H_INCLUDED
#	define INEX_MEMORY_INLINE_H_INCLUDED

#include <typeinfo>

namespace inex {
namespace memory {

template < typename type_allocated >
inline
type_allocated*	ie_allocate ( size_t count, pcvoid )
{
    //return  INEX_SCAST( type_allocated*, memory_allocate(count*sizeof(type_allocated), typeid(type_allocated).name()) );

    return			static_cast< type_allocated* >( memory_allocate(count * sizeof( type_allocated ), typeid( type_allocated ).name( ) ) );
//	return          (type_allocated*)memory_allocate(count*sizeof(type_allocated), typeid(type_allocated).name());
}

template < typename type_allocated >
inline
type_allocated*	ie_new ( )
{
	type_allocated* pointer			= static_cast< type_allocated* >( memory_allocate( sizeof( type_allocated ), typeid( type_allocated ).name( ) ) );
	new	( pointer ) type_allocated	{ };
	return 			pointer;
}

template < typename type_allocated, typename construction_parameter_1 >
inline
type_allocated*	ie_new( construction_parameter_1 const& parameter_1 )
{
	type_allocated* pointer			= static_cast< type_allocated* >( memory_allocate( sizeof( type_allocated ), typeid( type_allocated ).name( ) ) );
	new	( pointer ) type_allocated 	{ parameter_1 };
	return 			pointer;
}

template <
	typename type_allocated,
	typename construction_parameter_1,
	typename construction_parameter_2
>
inline
type_allocated*	ie_new (	construction_parameter_1 const&		parameter_1,
							construction_parameter_2 const&		parameter_2 )
{
	type_allocated* pointer			= static_cast< type_allocated* >( memory_allocate( sizeof( type_allocated ), typeid( type_allocated ).name( ) ) );
	new	( pointer ) type_allocated	{ parameter_1, parameter_2 };
	return 							pointer;
}

template < typename type_allocated >
inline
void	ie_delete ( type_allocated*& pointer )
{
    //logging::Log("type_allocated*&obj:   ");
    if ( pointer )
	{
        pointer->~type_allocated	( );
        memory_free( static_cast< pvoid >( pointer ) );
        pointer	=   nullptr;
    }
}

template < typename type_allocated >
inline
void ie_delete ( type_allocated* const& obj )
{
    //logging::Log("type_allocated*const&obj:   ");

    if ( obj )
	{
        obj->~type_allocated( );
        memory_free( static_cast< pvoid >( obj ) );
        const_cast< type_allocated*& >( obj )	= nullptr;
    }
}

} // namespace memory
} // namespace inex
#endif //#ifndef INEX_MEMORY_INLINE_H_INCLUDED
