////////////////////////////////////////////////////////////////////////////
//	Created 	: 20.03.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

namespace inex {
namespace math {

//-----------------------------------------------------------------------------------
// initializations
//-----------------------------------------------------------------------------------
inline
float2::float2 ( )
{
}

inline
float2::float2 ( type const x_value, type const y_value ) :
    x           { x_value },
    y           { y_value }
{
}

inline
float2::float2 ( float2 const& source ) :
    x           { source.x },
    y           { source.y }
{
}

inline
float2::float2 ( float2 && borrowed )
{
    ASSERT_S    ( 0 );
}

//-----------------------------------------------------------------------------------
// accessors
//-----------------------------------------------------------------------------------
inline
float2::type const&     float2::operator [ ] ( u8 index ) const
{
    // also handles signed (conversion form s to u)
    ASSERT_S    ( ( index < 2 ) );
    return      *( & x + index );
}

inline
float2::type&           float2::operator [ ] ( u8 index )
{
    ASSERT_S    ( ( index < 2 ) );
    return       *( & x + index );
}

//-----------------------------------------------------------------------------------
// operations
//-----------------------------------------------------------------------------------
inline
float2          float2::operator - ( )
{
    x            = -x;
    y            = -y;
    return       *this;
}

inline
float2          float2::operator += ( float2 const& other )
{
    x           += other.x;
    y           += other.y;
    return       * this;
}

inline
float2          float2::operator += ( float2::type const value )
{
    x           += value;
    y           += value;
    return      * this;
}

inline
float2          float2::operator -= ( float2 const& other )
{
    x           -= other.x;
    y           -= other.y;
    return      * this;
}

inline
float2          float2::operator -= ( float2::type const value )
{
    x           -= value;
    y           -= value;
    return      * this;
}

inline
float2          float2::operator *= ( float2::type const value )
{
    x           *= value;
    y           *= value;
    return      * this;
}

//inline
//float2          float2::operator *= ( float2 const& other )
//{
//    x                   *= other.x;
//    y                   *= other.y;
//    return              * this;
//}

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
float2          float2::set ( float2::type const x_value, float2::type const y_value )
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
float2::type    float2::square_magnitude ( ) const
{
    return              ( sqr( x ) + sqr( y ) );
}

inline
float2::type    float2::magnitude ( ) const
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
inline
float2          operator + ( float2 const& left, float2 const& right )
{
    return              float2( left.x + right.x, left.y + right.y );
}

inline
float2          operator + ( float2 const& left, float2::type const& right )
{
    return              float2( left.x + right, left.x + right );
}

inline
float2          operator - ( float2 const& left, float2 const& right )
{
    return              float2( left.x - right.x, left.y - right.y );
}

inline
float2          operator - ( float2 const& left, float2::type const& right )
{
    return              float2( left.x - right, left.y - right );
}



} // namespace math
} // namespace inex
