#ifndef UTILS_H_INCLUDED
#	define UTILS_H_INCLUDED

#	include <mutex>

namespace inex {
namespace detail {

struct INEX_CORE_API noncopyable
{
			noncopyable	( ) = default;
private:
			noncopyable	( noncopyable const& ) = delete;
}; // struct noncopyable

struct nonassignable
{
private:
	void	operator =	( nonassignable const& ) = delete;
}; // struct nonassignable
} // namespace detail

template < typename data_type >
struct stack
{
public:
                stack       ( );
                ~stack      ( );

                stack       ( stack const& )    = delete;
    stack&      operator =	( stack const& )    = delete;

    void        push        ( data_type const& rhs );
    void        pop         ( );
    bool        is_empty    ( ) const;
    data_type&  back        ( );

private:
    struct Node
	{
		data_type	value;
		Node*		previous;
	}; // struct Node

    Node*       m_first;
    Node*       m_last;
}; // struct stack

template < typename T >
class singleton : public detail::nonassignable, public detail::noncopyable
{
public:
	virtual		~singleton< T >	( )	= default;

	static	T*	get_instance	( )
	{
		std::call_once( m_once, [ ]( ){ m_instance.reset( new T ); } );
		return					m_instance.get( );
	}

	template < typename ... Args >
	static	T*	get_instance	( Args && ... pars )
	{
	    auto helper             = [ ]( auto&& ...pars )  { return sizeof ... ( pars ); };
		std::call_once( m_once, [ args = forward_as_tuple(pars...), helper ]( ) { m_instance.reset( new T( std::forward( args  ) ) ); } );
		return					m_instance.get( );
	}


private:
	static	std::unique_ptr< T >	m_instance;
	static std::once_flag			m_once;

}; // class singleton

template < typename T > std::unique_ptr< T >	singleton < T >::m_instance;
template < typename T > std::once_flag			singleton < T >::m_once;

} // namespace inex

template < typename Type, u32 max_count >
class fixed_array
{
public:
					fixed_array		( )
	{
						//m_data[ max_count ] = -1; 
	}

	Type&			operator [ ]	( int i )
	{
		return	m_data[ i ];
	}
	// why don't use Type const& operator [ ] ( int i ) const?
	Type const&		elem			( int i ) const
	{
		return	m_data[ i ];
	}

	void			set_elem		( int i, Type const& other )
	{
		m_data[ i ]         = other;
	}

	explicit    	operator int * ( )
	{
		return &m_data[ 0 ];
	}

	u32				size			( ) const { return max_count; }

private:
	Type	m_data	[ max_count + 1 ];
}; // class fixed_array

template < typename Type, int max_count >
class fixed_vector : public fixed_array< Type, max_count >
{
public:
	typedef Type * iterator;
public:
			fixed_vector	( ) :
				m_count		( 0u ),
				m_available	( max_count ),
				m_max_count	( max_count )
	{
	}

	void	push_back		( Type value )
	{
		set_elem				( m_count, value );
		increment_counters		( );
	}

	Type &	begin			( )
	{
		return					fixed_array<Type, max_count>::operator[ ]( 0 );
	}

	Type const &begin			( ) const
	{
		return					fixed_array<Type, max_count>::operator[ ]( 0 );
	}

	Type const &end			( ) const
	{
		return					fixed_array<Type, max_count>::operator[ ]( max_count );
	}

	Type &	end				( )
	{
		return					fixed_array<Type, max_count>::operator[ ]( max_count );
	}


private:
	// todo: use intrusive pointer instead
	void 	increment_counters	( )
	{
		++m_count;
		--m_available;
	}

	void 	decrement_counters	( )
	{
		--m_count;
		++m_available;
	}
	
private:
	u32 		m_count;
	u32			m_available;
	u32			m_max_count;
}; // class fixed_vector

template < typename T >
constexpr
std::underlying_type_t< T >	to_underlying ( T value ) noexcept
{
    return				static_cast< std::underlying_type_t< T > >( value );
}

#include "utils_inline.h"

#endif // #ifndef UTILS_H_INCLUDED
