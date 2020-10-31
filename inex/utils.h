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
		std::call_once( m_once, [ ]( ){ m_insance.reset( new T ); } );
		return					m_instance.get( );
	}

	template < typename ... Args >
	static	T*	get_instance	( Args && ... args )
	{
		std::call_once( m_once, [ & ]( ) { m_insance.reset( new T( std::forward< Args >( args ... ) ) ); } );
		return					m_instance.get( );
	}


private:
	static	std::unique_ptr< T >	m_instance;
	static std::once_flag			m_once;

}; // class singleton

template < typename T > std::unique_ptr< T >	singleton < T >::m_instance;
template < typename T > std::once_flag			singleton < T >::m_once;

} // namespace inex

template < typename Type, int max_count >
class fixed_array
{
public:
					fixed_array		( )
					{
					}

	Type&			operator [ ]( int i )
					{
						return	m_data[ i ];
					}
	// why don't use Type const& operator [ ] ( int i ) const?
	Type const&		elem		( int i ) const
					{
						return	m_data[ i ];
					}

	void			set_elem	( int i, Type const& other )
                    {
                        m_data[ i ]         = other;
                    }

	explicit    	operator int*( ) { return &m_data[ 0 ]; }

private:
	Type	m_data	[ max_count ];
}; // class fixed_array

#include "utils_inline.h"

#endif // #ifndef UTILS_H_INCLUDED
