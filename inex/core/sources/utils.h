#ifndef UTILS_H_INCLUDED
#	define UTILS_H_INCLUDED

//#include <inex/types.h>

namespace inex {
namespace core {
namespace utils {

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

} // namespace utils
} // namespace core
} // namespace inex

#include "utils_inline.h"

#endif // #ifndef UTILS_H_INCLUDED
