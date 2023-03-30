////////////////////////////////////////////////////////////////////////////
//	Created 	: 08.04.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_FUNCTIONS_H_INCLUDED
#   define MATH_FUNCTIONS_H_INCLUDED

namespace inex {
namespace math {

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

INEX_CORE_API inline bool	is_not_a_number	( float const value );
INEX_CORE_API inline bool	is_denormal		( float value );
template < typename T >
INEX_CORE_API inline bool	is_similar		( T const& left, T const& right, float const epsilon = epsilon_5 );

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

template < typename T > inline
 T	max	( T const& value1, T const& value2, T const& value3, T const& value4 )
{
	return		max(value1, max(value2, max(value3, value4)));
}

inline
bool valid		( float const& value )
{
	if( is_not_a_number( value ) )
		return false;

	//if( is_infinity( value ) )
	//	return false;

	if( is_denormal( value ) )
	{
		const_cast<float&>(value) = 0;
		return	true;
	}

	return		true;
}

inline float abs( float value )
{
	ASSERT_S	( valid( value ) );
	u32			bit_value = ( *( u32* ) &value ) & 0x7fffffff;
	return		( *( float* )&bit_value );
}

constexpr inline
float   degrees_to_radians ( float const value )
{
    return              value / 180.f * pi;
}

constexpr inline
float   radians_to_degree ( float const value )
{
    return              value / pi * 180.f;
}

template < typename T >
T	align_down ( T value, T align_to )
{
	ASSERT_S			( value > 0 );
	T temp				= align_to - 1;
	return				value + temp & ( ~align_to );
}

template < typename T >
T	align_up ( T value, T align_to )
{
	ASSERT_S			( value > 0 );
	return				( ( value - 1 ) | ( align_to - 1 ) ) + 1;
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

INEX_CORE_API
inline
bool	is_denormal	( float const value )
{
	int const	value_bits = horrible_cast<float,int>(value).second;

	// +denormal, -denormal
	if ( ( ( (value_bits & 0x7f800000) == 0 ) ) && ( ( value_bits & 0x007fffff ) != 0) )
		return	true;

	return		false;
}

INEX_CORE_API
inline
bool	is_quiet_not_a_number	( float const value )
{
	int const	value_bits = horrible_cast<float,int>(value).second;

	// +QNaN, -QNaN
	if ( ( ( (value_bits & 0x7f800000) == 0x7f800000 ) ) && ( ( value_bits & 0x00400000 ) != 0) )
		return	true;

	return		false;
}

INEX_CORE_API
inline
bool	is_signalling_not_a_number	( float const value )
{
	int const	value_bits = horrible_cast<float,int>(value).second;

	// +SNaN, -SNaN
	if ( ( ( (value_bits & 0x7f800000) == 0x7f800000 ) ) && ( ( value_bits & 0x00400000 ) == 0)  && ( ( value_bits & 0x003fffff ) != 0) )
		return	true;

	return		false;
}

INEX_CORE_API
inline
bool	is_not_a_number	( float const value )
{
	return		is_signalling_not_a_number( value ) || is_quiet_not_a_number( value );
}

inline
bool is_relatively_zero	( float bigger_value, float smaller_value, float const epsilon = epsilon_7 )
{
	bigger_value			= abs( bigger_value );
	smaller_value			= abs( smaller_value );
	if ( bigger_value < smaller_value )
		return				false;

	if ( bigger_value != 0.f )
		return				smaller_value/bigger_value < epsilon;

	return					true;
}

template < typename T > 
bool is_zero		( T const& value, T const& epsilon )
{
	return		( is_similar( value, T(0), epsilon ) );
}

template < typename T >
inline bool is_similar		( T const& left, T const& right, float const epsilon )
{
	return		( abs( left - right) < epsilon );
}

inline
int floor		( float const value )
{
	ASSERT_S		( valid( value ) );
	int value_raw	= *(int const * )( &value );
	value_raw		= value_raw ^ ((value_raw ^ (value_raw & (value_raw - 1))) & 0x80000000);
	int exponent	= ( 127 + 31 ) - ( ( value_raw >> 23 ) & 0xff );
	int result		= (((u32)(value_raw) << 8 ) | ( 1U << 31 ) ) >> exponent;
	exponent		+= 31 - 127;
	int imask		= (!(((( (1<<(exponent)))-1)>>8) & value_raw ) );
	exponent		-= (31 - 127) + 32;
	exponent		>>= 31;
	value_raw		>>=	31;
	result			-= imask & value_raw;
	result			&= exponent;
	result			^= value_raw;
	return			result;
}

} // namespace math
} // namespace inex

#   include <inex/math_functions_inline.h>

#endif // #ifndef MATH_FUNCTIONS_H_INCLUDED
