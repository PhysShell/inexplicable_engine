////////////////////////////////////////////////////////////////////////////
//	Created 	: 08.04.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_MATRIX2_H_INCLUDED
#   define MATH_MATRIX2_H_INCLUDED

namespace inex {
namespace math {

class matrix2
{
public:
    typedef float           type;

public:
    type                    x [ 2 ] [ 2 ];

                            matrix2 ( );
                            matrix2 ( type const value );
                            matrix2 ( matrix2 const& other );

            matrix2&        operator =  ( matrix2   const&  other );
            matrix2&        operator =  ( type      const   value );
            matrix2&        operator += ( matrix2   const&  other );
            matrix2&        operator += ( type      const   value );
            matrix2&        operator *= ( matrix2   const&  other );
            matrix2&        operator *= ( type      const   value );
            matrix2&        operator /= ( type      const   value );

            type const*     operator [ ]( u8 ) const;
            type*           operator [ ]( u8 );

            matrix2&        invert      ( );
            matrix2&        transpose   ( );

    inline
            type            determinant ( ) const
                            {
                                //return **( x ) *  ;

                                return ( *( x )[ 0 ] * * ( ( x + 1 )[ 1 ] ) ) -
                                            ( *( x )[ 1 ] * *( x + 1 )[ 0 ] );
                            }

    inline
            matrix2         inverse_m   ( ) const
                            {
                                // matrix2 temp        = * this;
                                // temp.invert         ( );
                                // return              temp;
                                return matrix2 ( * this ).invert( );
                            }

    // make the outer functions?
    static  matrix2         identity_m  ( );
    class   float2          ;
    static  matrix2         scale_m     ( float2 const& );
    static  matrix2         rotate_m    ( type const );
    static  matrix2         mirror_y_m  ( );
    static  matrix2         mirror_x_m  ( );

    // ... operators as for float2

}; // class matrix2

float2  operator *          ( matrix2 const& left, float2 const& right );

class transform2
{
public:
                            transform2  ( );
                            transform2  ( transform2 const& other );
                            transform2  ( matrix2 const&, float2 const& );
                            transform2  ( matrix2 const& value );

    inline  transform2&     invert      ( )
                            {
                                m_matrix.invert ( );
                                m_vector        = m_matrix * m_vector;
                                return          * this;
                            }

    inline  transform2      inverse_t   ( ) const
                            {
                                return transform2 ( * this ).invert( );
                            }

    inline  float2          transform_point ( float2 const& value ) const
                            {
                                return float2(
                                            m_vector.x + **m_matrix.x * value.x
                                            + *( *( m_matrix.x + 2 ) ) * value.y,
                                             m_vector.y + **m_matrix.x * value.x
                                            + *( * ( m_matrix.x + 2 ) ) * value.y

                                        );
                            }

    inline  float2          transform_direction ( float2 const& value ) const
                            {
                                return float2(
                                            **m_matrix.x            * value.x + *( *( m_matrix.x + 1 ) )     * value.y,
                                            *( *( m_matrix.x ) + 1 )* value.x + *( *( m_matrix.x + 1 ) + 1 ) * value.y
                                        );
                            }

            void            homogenous_m    ( matrix2::type const matrix [ 16 ] ) const;
    inline  float2 const&   translation     ( ) const
                            {
                                return m_vector;
                            }

    inline  matrix2 const&  linear          ( ) const
                            {
                                return m_matrix;
                            }

    static  transform2      identity        ( );
    static  transform2      translate       ( float2 const& value );
    static  transform2      scale           ( float2 const& value );
    static  transform2      scale           ( matrix2::type const value );
    static  transform2      rotate          ( matrix2::type const value );

public:
    matrix2                 m_matrix;
    float2                  m_vector;
}; // class transform2

} // namespace math
} // namespace inex

#   include <inex/math_matrix2_inline.h>

#endif // #ifndef MATH_MATRIX2_H_INCLUDED
