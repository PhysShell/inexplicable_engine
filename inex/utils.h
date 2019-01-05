#ifndef UTILS_H_INCLUDED
#	define UTILS_H_INCLUDED

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
