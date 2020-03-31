////////////////////////////////////////////////////////////////////////////
//	Created 	: 18.10.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_FLOAT3_H_INCLUDED
#   define MATH_FLOAT3_H_INCLUDED

#   include <inex/macro_string.h>

namespace inex {
namespace math {

//-----------------------------------------------------------------------------------
// initializations
//-----------------------------------------------------------------------------------
inline
float3::float3 ( )
{
}

float3::float3 ( type const x_value, type const y_value, type const z_value )
    x           { x_value },
    y           { y_value },
    z           { z_value }
{
}

float3::float3 ( float3 const& source ) :
    x           { source.x },
    y           { source.y },
    z           { source.z }
{
}

float3::float3 ( float3 && borrowed )
{
    ASSERT_S    ( 0 );
}

//-----------------------------------------------------------------------------------
// accessors
//-----------------------------------------------------------------------------------
inline
type const&     float3::operator [ ] ( u8 index ) const
{
    // also handles signed (conversion form s to u)
    ASSERT_S            ( ( index < 3 ) );
    return              *( elements + index );
}

inline
type&           float3::operator [ ] ( u8 index )
{
    ASSERT_S            ( ( index < 3 ) );
    return              *( elements + index );
}

//-----------------------------------------------------------------------------------
// operations
//-----------------------------------------------------------------------------------
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
float3          float3::set (   float3::value const     x_value,
                                float3::value const     y_value
                                float3::value const     z_value )
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
float3::type    float3::square_magintude ( ) const
{
    return              ( sqr( x ) + sqr( y ) + sqr( z ) );
}

inline
float3::type    float3::magintude ( ) const
{
    return              sqrtf( square_magnitude( ) );
}

inline
float3                  float3::normalize ( )
{
    todo                ( "impl" );
    return              * this  /= magnitude ( );
}

inline
float3                  float3::orthogonal ( ) const
{
    todo                ( "impl" );
    return              float3( -y, x );
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
float3          operator + ( float3 const& right, float3 const& right )
{
    return              float3( right.x + left.x, right.y + left.y );
}

float3          operator + ( float3 const& right, float3::type const& left )
{
    return              float3( right.x + left, right.x + left );
}

float3          operator - ( float3 const& right, float3 const& left )
{
    return              float3( right.x - left.x, right.y - left.y );
}

float3          operator - ( float3 const& right, float3::type const& left )
{
bool ddf = not true;
    return              float3( right.x - left, right.y - left );
}



} // namespace math
} // namespace inex

#endif // #ifndef MATH_float3_H_INCLUDED
