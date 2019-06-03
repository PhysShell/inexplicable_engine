////////////////////////////////////////////////////////////////////////////
//	Created 	: 08.04.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_FUNCTIONS_H_INCLUDED
#   define MATH_FUNCTIONS_H_INCLUDED

namespace inex {
namespace math {

#define PI              3.1415926535897932384626433832795f

template < typename T > constexpr inline
T   abs_universal ( T value )
{
    return              value > ( T )0 ? value : -value;
}

#define fdEPS           machine_epsilon( )
constexpr inline
float   machine_epsilon ( )
{
	float e             = 1.0f;
	while ( 1.0f + e / 2.0f > 1.0f ) 		e       /= 2.0f;
	return              e;
}

template < typename T > constexpr inline
T   sqr ( T const& value )   {   return ( value * value );  }

template < typename T > constexpr inline
T   max ( T const& left, T const& right )   
{  
    return              left > right ? left : right;
}

constexpr inline
float   degrees_to_radians ( float const value )
{
    return              value / 180.f * PI;
}

constexpr inline
float   radians_to_degree ( float const value )
{
    return              value / PI * 180.f;
}

constexpr inline
float   sin ( float const angle )
{
    return              sinf( angle );
}

constexpr inline
float   cos ( float const angle )
{
    return              cosf( angle );
}

} // namespace math
} // namespace inex

#   include <inex/math_functions_inline.h>

#endif // #ifndef MATH_FUNCTIONS_H_INCLUDED
