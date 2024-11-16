#pragma once
#include <inex/threading_functions.h>
namespace inex {
namespace threading {

class INEX_CORE_API single_threading_policy : private inex::detail::noncopyable {
public:
	typedef			u32					u32_type;

	struct mutex_raii : inex::detail::noncopyable
	{
		mutex_raii	(single_threading_policy const &) {}
		void clear	();
		~mutex_raii	() {}
	};

public:
	template <typename T>
	static	inline	u32	intrusive_ptr_increment	( T& object )
	{
		return	increment(object.m_reference_count);
	}

	template <typename T>
	static	inline	u32	intrusive_ptr_decrement	( T& object )
	{
		return	decrement(object.m_reference_count);
	}

	template <class IntType>
	static	inline	IntType			increment	( IntType& value )
	{
		ASSERT_S	( value != std::numeric_limits<typename std::remove_cv<IntType>::type>::max( ) );
		return	++value;
	}

	template <class IntType>
	static	inline	IntType			decrement	( IntType& value )
	{
		ASSERT_S	( value != std::numeric_limits<typename std::remove_cv<IntType>::type>::min( )  );
		return	--value;
	}

	template <class IntType>
	static	inline	IntType			compare_exchange	( IntType& dest, IntType src, IntType comparand )
	{
		IntType out_result	=	dest;
		if ( dest == comparand )
			dest			=	src;

		return					out_result;
	}

	static	inline	pvoid			compare_exchange_pointer	( pvoid& dest, pvoid src, pvoid comparand )
	{
		pvoid out_result	=	dest;
		if ( dest == comparand )
			dest			=	src;

		return					out_result;
	}

	template <class IntType, class OtherIntType>
	static	inline	IntType			operator_or	( IntType& out_left, OtherIntType const right ) { IntType out_result = out_left; out_left |= right; return out_result; }

	template <class IntType, class OtherIntType>
	static	inline	IntType			operator_and( IntType & out_left, OtherIntType const right ) { IntType out_result = out_left; out_left &= right; return out_result;  }

					bool			try_lock	() const { return true; }
					void			lock		() const { ; }
					void			unlock		() const { ; }

}; // class single_threading_policy

class multi_threading_policy {
public:
	typedef			volatile threading::atomic32_type		u32_type;

	template <typename T>
	static	inline	u32	intrusive_ptr_increment	( T& object )
	{
		return	increment(object.m_reference_count);
	}

	template <typename T>
	static	inline	u32	intrusive_ptr_decrement	( T& object )
	{
		return	decrement(object.m_reference_count);
	}

	template <class IntType>
	static	inline	IntType			increment	( IntType& value )
	{
		ASSERT_S	( value != std::numeric_limits<typename std::remove_cv<IntType>::type>::max( ) );
		return	interlocked_increment( value );
	}

	template <class IntType>
	static	inline	IntType			decrement	( IntType& value )
	{
		ASSERT_S	( value != std::numeric_limits<typename std::remove_cv<IntType>::type>::min( ) );
		return	interlocked_decrement( value );
	}

	template <class IntType>
	static	inline	IntType			compare_exchange	( IntType volatile& dest, IntType src, IntType comparand )
	{
		return	interlocked_compare_exchange	( dest, src, comparand );
	}

	static	inline	pvoid			compare_exchange_pointer	( atomic_ptr_type& dest, pvoid src, pvoid comparand )
	{
		return	interlocked_compare_exchange_pointer	( dest, src, comparand );
	}

	template <class IntType, class OtherIntType>
	static	inline	IntType			operator_or	( IntType & out_left, OtherIntType const right )
	{
		NOT_IMPLEMENTED	( );
		return	0;
		//return threading::interlocked_or((threading::atomic32_type &)out_left, (threading::atomic32_value_type)right);
	}

	template <class IntType, class OtherIntType>
	static	inline	IntType			operator_and ( IntType & out_left, OtherIntType const right )
	{
		NOT_IMPLEMENTED	( );
		return	0;
		//return threading::interlocked_and((threading::atomic32_type &)out_left, (threading::atomic32_value_type)right);
	}

}; // class multi_threading_policy

class mutex;
class event;
class mutex_tasks_unaware;
class event_tasks_unaware;
class simple_lock;

template < typename T >
struct policy_resolver {
	typedef single_threading_policy	policy_type;
}; // struct policy_resolver

template < >
struct policy_resolver< multi_threading_policy > {
	typedef multi_threading_policy	policy_type;
}; // struct policy_resolver< mutex >

template < >
struct policy_resolver< mutex > {
	typedef multi_threading_policy	policy_type;
}; // struct policy_resolver< mutex >

template < >
struct policy_resolver< event > {
	typedef multi_threading_policy	policy_type;
}; // struct policy_resolver< mutex >

template < >
struct policy_resolver< mutex_tasks_unaware > {
	typedef multi_threading_policy	policy_type;
}; // struct policy_resolver< mutex >

template < >
struct policy_resolver< event_tasks_unaware > {
	typedef multi_threading_policy	policy_type;
}; // struct policy_resolver< mutex >

template < >
struct policy_resolver< simple_lock > {
	typedef multi_threading_policy	policy_type;
}; // struct policy_resolver< mutex >

} // namespace threading
} // namespace inex