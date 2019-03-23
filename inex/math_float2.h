////////////////////////////////////////////////////////////////////////////
//	Created 	: 19.03.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_FLOAT2_H_INCLUDED
#   define MATH_FLOAT2_H_INCLUDED

namespace inex {
namespace math {

class float2
{
public:
    typedef float   type;
    type            x;
    type            y;

public:
    //-----------------------------------------------------------------------------------
	// initializations
	//-----------------------------------------------------------------------------------
                    float2          ( );
                    float2          ( type const x, type const y );
                    float2          ( float2 const& source );
                    float2          ( float2 && borrowed );

	//-----------------------------------------------------------------------------------
	// accessors
	//-----------------------------------------------------------------------------------
    type const&     operator [ ]    ( u8 index ) const;
    type&           operator [ ]    ( u8 index );

    //-----------------------------------------------------------------------------------
	// operations
	//-----------------------------------------------------------------------------------
    float2          operator -      ( );

    float2          operator +=     ( float2 const& other );
    float2          operator +=     ( type const value );

    float2          operator -=     ( float2 const& other );
    float2          operator -=     ( type const value );  

    // cross product
    float2          operator ^=     ( float2 const& other );
    float2          operator *=     ( type const value );
    float2          operator /=     ( type const value );

    float2          set             ( type const x_value, type const y_value );

    type            dot_product     ( float2 const& other ) const;

}; // class float2

} // namespace math
} // namespace inex

#   include <inex/math_float2_inline.h>

#endif // #ifndef MATH_FLOAT2_H_INCLUDED
