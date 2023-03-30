////////////////////////////////////////////////////////////////////////////
//	Created 	: 30.06.2022
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_CONSTRUCTION_H_INCLUDED
#	define INEX_CONSTRUCTION_H_INCLUDED

#	include <inex/threading_functions.h>

namespace inex {

struct bind_pointer_to_buffer_mt_safe_placement_new_predicate 
{
	template <class T>
	void operator () (T * pointer)
	{
		new (pointer) T();
	}
}; // struct bind_pointer_to_buffer_mt_safe_placement_new_predicate 

template <class T, class Construct_Predicate>
void   bind_pointer_to_buffer_mt_safe (T * &						pointer, 
									   char							(& buffer_for_T)[sizeof(T)], 
									   threading::atomic32_type &	creation_flag,
									   Construct_Predicate			construct_predicate)
{
	if ( !pointer )
	{
		threading::atomic32_value_type const previous_creation_flag	=	threading::interlocked_exchange(creation_flag, 1);
		if ( previous_creation_flag == 0 )
		{
			construct_predicate						((T *)buffer_for_T);
			threading::interlocked_exchange_pointer	((pvoid &)pointer, buffer_for_T);
		}
		else
			while ( !pointer ) ;
	}
}

} // namespace inex

#endif // #ifndef INEX_CONSTRUCTION_H_INCLUDED