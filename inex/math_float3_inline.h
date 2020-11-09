////////////////////////////////////////////////////////////////////////////
//	Created 	: 18.10.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_FLOAT3_INLINE_H_INCLUDED
#   define MATH_FLOAT3_INLINE_H_INCLUDED

#   include <math.h>
#	include <inex/math_functions.h>
#	if defined LOG_FLOAT3
#		undef LOG_FLOAT3
#		define LOG_FLOAT3( x )
#	endif // #if defined LOG_FLOAT3

namespace inex {
namespace math {

//-----------------------------------------------------------------------------------
// initializations
//-----------------------------------------------------------------------------------
inline
float3::float3 ( ) :
    x           { .0f },
    y           { .0f },
    z           { .0f }
{
    LOG_FLOAT3( ( * this ) );
}

inline
float3::float3 ( type const x_value, type const y_value, type const z_value ) :
    x           { x_value },
    y           { y_value },
    z           { z_value }
{    LOG_FLOAT3( ( * this ) );
}

inline
float3::float3 ( float3 const& source ) :
    x           { source.x },
    y           { source.y },
    z           { source.z }
{    LOG_FLOAT3( ( * this ) );
}

inline
float3::float3 ( float3 && borrowed )
{
    ASSERT_S    ( 0 );
}

//-----------------------------------------------------------------------------------
// accessors
//-----------------------------------------------------------------------------------
inline
float3::type const&     float3::operator [ ] ( u8 index ) const
{
    // also handles signed (conversion form s to u)
    ASSERT_S            ( ( index < 3 ) );
    return              *( elements + index );
}

inline
float3::type&           float3::operator [ ] ( u8 index )
{
    ASSERT_S            ( ( index < 3 ) );
    return              *( elements + index );
}

//-----------------------------------------------------------------------------------
// operations
//-----------------------------------------------------------------------------------
inline
float3          float3::operator - ( )
{
    x                   = -x;
    y                   = -y;
    z                   = -z;
    return              *this;
}

inline
float3          float3::operator += ( float3 const& other )
{
    x                   += other.x;
    y                   += other.y;
    z                   += other.z;
    return              * this;
}

inline
float3          float3::operator += ( float3::type const value )
{
    x                   += value;
    y                   += value;
    z                   += value;
    return              * this;
}

inline
float3          float3::operator -= ( float3 const& other )
{
    x                   -= other.x;
    y                   -= other.y;
    z                   -= other.z;
    return              * this;
}

inline
float3          float3::operator -= ( float3::type const value )
{
    x                   -= value;
    y                   -= value;
    z                   -= value;
    return              * this;
}

inline
float3          float3::operator *= ( float3::type const value )
{
    x                   *= value;
    y                   *= value;
    z                   *= value;
    return              * this;
}

inline
float3          float3::operator *= ( float3 const& other )
{
    x                   *= other.x;
    y                   *= other.y;
    z                   *= other.z;
    return              * this;
}

inline
float3          float3::operator /= ( float3::type const value )
{
    x                   /= value;
    y                   /= value;
    z                   /= value;
    return              * this;
}

inline
float3          float3::operator ^= ( float3 const& other )
{

    return              float3(  /**/ );
}

inline
float3          float3::set (   float3::type const     x_value,
                                float3::type const     y_value,
                                float3::type const     z_value )
{
    x                   = x_value;
    y                   = y_value;
    z                   = z_value;
    return              * this;
}

inline
float3::type    float3::dot_product ( float3 const& other ) const
{
    return              ( x * other.x ) + ( y * other.y ) + ( z * other.z );
}

inline
float3::type    float3::square_magnitude ( ) const
{
    return              ( sqr( x ) + sqr( y ) + sqr( z ) );
}

inline
float3::type    float3::magnitude ( ) const
{
    return              sqrtf( square_magnitude( ) );
}

inline
float3                  float3::normalize ( )
{
    #pragma todo        ( "impl" )
    return              * this  /= magnitude ( );
}

inline
float3                  float3::orthogonal ( ) const
{
    #pragma todo        ( "impl" )
    return              float3( );//float3( -y, x );
}

inline
float3::type            float3::distance_to_sqr (float3 const& other ) const
{
    return              ( sqr( x - other.x ) + sqr( y - other.y ) );
}

inline
float3::type            float3::distance_to (float3 const& other ) const
{
    return              sqrtf( distance_to_sqr( other ) );
}

//-----------------------------------------------------------------------------------
// outer operations
//-----------------------------------------------------------------------------------
inline
float3          operator + ( float3 const& left, float3 const& right )
{
    return              float3( left.x + right.x, left.y + right.y, left.z + right.z );
}

inline
float3          operator + ( float3 const& left, float3::type const& right )
{
    return              float3( left.x + right, left.y + right, left.z + right );
}

inline
float3          operator - ( float3 const& left, float3 const& right )
{
    return              float3( left.x + right.x, left.y + right.y, left.z + right.z );
}

inline
float3          operator - ( float3 const& left, float3::type const& right )
{
    // bool ddf = not true;
    return              float3( left.x + right, left.y + right, left.z + right );
}



} // namespace math
} // namespace inex

#endif // #ifndef MATH_FLOAT3_INLINE_H_INCLUDED
