////////////////////////////////////////////////////////////////////////////
//	Created 	: 18.10.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_FLOAT3_H_INCLUDED
#   define MATH_FLOAT3_H_INCLUDED

namespace inex {
namespace math {

class INEX_CORE_API float3
{
public:
    typedef float       type;

	union
    {
		struct
        {
            type        x;
            type        y;
            type        z;
		};
		
		type			elements[ 3 ];
	};


public:
    //-----------------------------------------------------------------------------------
	// initializations
	//-----------------------------------------------------------------------------------
                    float3          ( );
                    float3          ( type const x, type const y, type const z );
                    float3          ( float3 const& source );
                    float3          ( float3 && borrowed );

	//-----------------------------------------------------------------------------------
	// accessors
	//-----------------------------------------------------------------------------------
    type const&     operator [ ]    ( u8 index ) const;
    type&           operator [ ]    ( u8 index );

    //-----------------------------------------------------------------------------------
	// operations
	//-----------------------------------------------------------------------------------
    // todo: return a reference
    float3          operator -      ( );

    float3&         operator =      ( float3 const& other )         {   x = other.x; y = other.y; z = other.z; return * this;    }
    float3&         operator +      ( );

    float3          operator +=     ( float3 const& other );
    float3          operator +=     ( type const value );

    float3          operator -=     ( float3 const& other );
    float3          operator -=     ( type  const value );  

    // cross product
    float3          operator ^=     ( float3 const& other );
    float3          operator *=     ( type const value );
    float3          operator *=     ( float3 const& other );
    float3          operator /=     ( type const value );

    float3          set             ( type const x_value, type const y_value, type const z_value );

    type            dot_product     ( float3 const& other ) const;
    type            square_magnitude( ) const;
    type            magnitude       ( ) const;
    float3          normalize       ( ); // todo :: *_safe
    float3          orthogonal      ( ) const;
    type            distance_to_sqr ( float3 const& other ) const;
    type            distance_to     ( float3 const& other ) const;

    type *          raw_vector      ( ) { return elements; }

}; // class float3



} // namespace math
} // namespace inex

#   include <inex/math_float3_inline.h>

#endif // #ifndef MATH_float3_H_INCLUDED
