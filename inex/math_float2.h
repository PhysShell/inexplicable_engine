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
    type const&     operator [ ]    ( size_t index ) const  {   return *( & x + index );    }
    type&           operator [ ]    ( size_t index )        {   return *( & x + index );    }

    //-----------------------------------------------------------------------------------
	// operations
	//-----------------------------------------------------------------------------------
    float2          operator -      ( )                     {   x =   -x; y =   -y; return  *this; }
}; // class float2



} // namespace math
} // namespace inex

#endif // #ifndef MATH_FLOAT2_H_INCLUDED
