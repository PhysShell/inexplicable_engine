////////////////////////////////////////////////////////////////////////////
//	Created 	: 08.04.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_FUNCTIONS_H_INCLUDED
#   define MATH_FUNCTIONS_H_INCLUDED

namespace inex {
namespace math {

template < typename T > inline
T   sqr ( T const& value )   {   return ( value * value );  }

template < typename T > inline
T   max2 ( T const& left, T const& right )   
{  
    return              left > right ? left : right;
}

} // namespace math
} // namespace inex

#   include <inex/math_functions_inline.h>

#endif // #ifndef MATH_FUNCTIONS_H_INCLUDED
