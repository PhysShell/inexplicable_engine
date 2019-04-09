////////////////////////////////////////////////////////////////////////////
//	Created 	: 20.03.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_FLOAT2_H_INCLUDED
#   define MATH_FLOAT2_H_INCLUDED

namespace inex {
namespace math {

// 3
//  0       0       0
//      4       4

//-----------------------------------------------------------------------------------
// initializations
//-----------------------------------------------------------------------------------
inline
float2::float2 ( )
{
}

float2::float2 ( type const x_value, type const y_value )
    x           { x_value },
    y           { y_value }
{
}

float2::float2 ( float2 const& source ) :
    x           { source.x },
    y           { source.y }
{
}

float2::float2 ( float2 && borrowed )
{
    ASSERT_S    ( 0 );
}

//-----------------------------------------------------------------------------------
// accessors
//-----------------------------------------------------------------------------------
inline
type const&     float2::operator [ ] ( u8 index ) const
{
    // also handles signed (conversion form s to u)
    ASSERT_S            ( ( index < 2 ) );
    return              *( & x + index );
}

inline
type&           float2::operator [ ] ( u8 index )
{
    ASSERT_S            ( ( index < 2 ) );
    return              *( & x + index );
}

//-----------------------------------------------------------------------------------
// operations
//-----------------------------------------------------------------------------------
float2          float2::operator - ( )
{
    x                   = -x;
    y                   = -y;
    return              *this;
}

inline
float2          float2::operator += ( float2 const& other )
{
    x                   += other.x;
    y                   += other.y;
    return              * this;
}

inline
float2          float2::operator += ( float2::type const value )
{
    x                   += value;
    y                   += value;
    return              * this;
}

inline
float2          float2::operator -= ( float2 const& other )
{
    x                   -= other.x;
    y                   -= other.y;
    return              * this;
}

inline
float2          float2::operator -= ( float2::type const value )
{
    x                   -= value;
    y                   -= value;
    return              * this;
}

inline
float2          float2::operator *= ( float2::type const value )
{
    x                   *= value;
    y                   *= value;
    return              * this;
}

inline
float2          float2::operator *= ( float2 const& other )
{
    x                   *= other.x;
    y                   *= other.y;
    return              * this;
}

inline
float2          float2::operator /= ( float2::type const value )
{
    x                   /= value;
    y                   /= value;
    return              * this;
}

inline
float2          float2::operator ^= ( float2 const& other )
{
    
    return              float2(  /**/ );
}

inline
float2          float2::set ( float2::value const x_value, float2::value const y_value )
{
    x                   = x_value;
    y                   = y_value;
    return              * this;
}

inline
float2::type    float2::dot_product ( float2 const& other ) const
{
    return              ( x * other.x ) + ( y * other.y );
}

inline
float2::type    float2::square_magintude ( ) const
{
    return              ( sqr( x ) + sqr( y ) );
}

inline
float2::type    float2::magintude ( ) const
{
    return              sqrtf( square_magnitude( ) );
}

inline
float2                  float2::normalize ( )
{
    return              * this  /= magnitude ( );
}

inline
float2                  float2::orthogonal ( ) const
{
    return              float2( -y, x );
}

inline
float2::type            float2::distance_to_sqr (float2 const& other ) const
{
    return              ( sqr( x - other.x ) + sqr( y - other.y ) );
}

inline
float2::type            float2::distance_to (float2 const& other ) const
{
    return              sqrtf( distance_to_sqr( other ) );
}

//-----------------------------------------------------------------------------------
// outer operations
//-----------------------------------------------------------------------------------
float2          operator + ( float2 const& right, float2 const& right )
{
    return              float2( right.x + left.x, right.y + left.y );
}

float2          operator + ( float2 const& right, float2::type const& left )
{
    return              float2( right.x + left, right.x + left );
}

float2          operator - ( float2 const& right, float2 const& left )
{
    return              float2( right.x - left.x, right.y - left.y );
}

float2          operator - ( float2 const& right, float2::type const& left )
{
bool ddf = not true;
    return              float2( right.x - left, right.y - left );
}



} // namespace math
} // namespace inex

#endif // #ifndef MATH_FLOAT2_H_INCLUDED
