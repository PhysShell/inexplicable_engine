////////////////////////////////////////////////////////////////////////////
//	Created 	: 08.04.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_FUNCTIONS_H_INCLUDED
#   define MATH_FUNCTIONS_H_INCLUDED

namespace inex {
namespace math {

#define PI              ( 3.1415926535897932384626433832795f )

/***
*
* void multiple_sse_pointer ( float* const, float* const )
*
* Entry:
*
*   dynamically allocated floats or array elements ONLY! UB when pass ESP vars
*
* Exit:
*
*   left float becomes the result of multiplication
*
****************************************************/
typedef void ( INEX_CDECL_CONVENTION *multiple_sse_pointer ) ( float* const, float* const );


void    multiple_pure   ( float* const , float* const );
void    multiple_sse    ( float* const left, float* const right );


// function returning float/double use fpu so might use declspec( naked )
// which means no prolog and epilog generated

typedef struct
{
    multiple_sse_pointer    matrix_multiple;
} /*typedef struct*/ MATH, *PMATH;

template < typename T > constexpr inline
T   abs_universal ( T value )
{
    return              value > ( T )0 ? value : -value;
}

#define fdEPS           machine_epsilon( )
inline
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

#if defined _MSC_VER
#	define os_sin( x )			( float ) std::sin( x )
#	define os_cos( x )			( float ) std::cos( x )
#elif defined __GNUC__
#	define os_sin( x )			__builtin_sin( x )
#	define os_cos( x )			__builtin_cos( x )
#endif // #if defined _MSC_VER

inline
float   sin ( float const angle )
{
// #   define sinf( x )    ( float ) std::sin(  ( double ) x ) ;
    return                  os_sin( angle );
}

INEX_CORE_API
inline
float   cos ( float const angle )
{
// #   define cosf( x )    ( float ) std::cos(  ( double ) x ) ;
    return              os_cos( angle );
}

} // namespace math
} // namespace inex

#   include <inex/math_functions_inline.h>

#endif // #ifndef MATH_FUNCTIONS_H_INCLUDED
