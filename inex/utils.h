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

#include "utils_inline.h"

#endif // #ifndef UTILS_H_INCLUDED
