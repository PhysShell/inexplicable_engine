#include "pch.h"
#include <inex/math_float4x4.h>

static inex::math::float4x4 invert_impl								( inex::math::float4x4 const& other, float const determinant )
{
	//bool const is_similar_determinant	= xray::math::is_similar( determinant, other.determinant( ), xray::math::epsilon_5 );
	//if ( !is_similar_determinant )
	//{
	//	float const d0 = other.determinant( );
	//	float const d1 = other.determinant( );
	//	float const d2 = other.determinant( );
	//	float const d3 = other.determinant( );
	//	LOG_ERROR("dets: %f\n %f\n %f\n %f\n %f", determinant, d0, d1, d2, d3);
	//	LOG_ERROR("i: %f %f %f %f", other.e00, other.e01, other.e02, other.e03);
	//	LOG_ERROR("j: %f %f %f %f", other.e10, other.e11, other.e12, other.e13);
	//	LOG_ERROR("k: %f %f %f %f", other.e20, other.e21, other.e22, other.e23);
	//	LOG_ERROR("c: %f %f %f %f", other.e30, other.e31, other.e32, other.e33);
	//	R_ASSERT		( 0 );
	//}
	//R_ASSERT		( inex::math::is_relatively_similar( determinant, other.determinant4x3( ), inex::math::epsilon_5 ) );


	float const	inverted_determinant = 1.f / determinant;

	inex::math::float4x4	result;
	result.e00 	=  inverted_determinant * ( other.e11*other.e22 - other.e12*other.e21 );
	result.e01 	= -inverted_determinant * ( other.e01*other.e22 - other.e02*other.e21 );
	result.e02 	=  inverted_determinant * ( other.e01*other.e12 - other.e02*other.e11 );
	result.e03 	=  0.f;
	
	result.e10 	= -inverted_determinant * ( other.e10*other.e22 - other.e12*other.e20 );
	result.e11 	=  inverted_determinant * ( other.e00*other.e22 - other.e02*other.e20 );
	result.e12 	= -inverted_determinant * ( other.e00*other.e12 - other.e02*other.e10 );
	result.e13 	=  0.f;
	
	result.e20 	=  inverted_determinant * ( other.e10*other.e21 - other.e11*other.e20 );
	result.e21 	= -inverted_determinant * ( other.e00*other.e21 - other.e01*other.e20 );
	result.e22 	=  inverted_determinant * ( other.e00*other.e11 - other.e01*other.e10 );
	result.e23 	=  0.f;
	
	result.e30 	= -( other.e30*result.e00 + other.e31*result.e10 + other.e32*result.e20 );
	result.e31 	= -( other.e30*result.e01 + other.e31*result.e11 + other.e32*result.e21 );
	result.e32 	= -( other.e30*result.e02 + other.e31*result.e12 + other.e32*result.e22 );
	result.e33 	=  1.f;

	ASSERT_S	( result.valid( ) );

	return		( result );
}

inex::math::float4x4 inex::math::invert4x3							( float4x4 const& other )
{
	ASSERT_S	( other.valid( ) );
	return		invert_impl( other, other.determinant4x3() );
}

inex::math::float4x4 inex::math::invert4x4			( float4x4 const& matrix_to_invert )
{
	float4x4 out_result;
	bool const inverted					=	try_invert4x4(matrix_to_invert, out_result);
	ASSERT_S								(inverted);
	return									out_result;
}

bool inex::math::try_invert4x4			( float4x4 const& matrix_to_invert, float4x4& out_result )
{
	float const* const m				=	& matrix_to_invert.e00;
	float* const inv					=	&out_result.e00;

	inv[0] 	=   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15]
					+ m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
	inv[4] 	=  -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15]
					- m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
	inv[8] 	=   m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15]
					+ m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
	inv[12]	 = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14]
				- m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];

	float const determinant				=	(m[0] * inv[0]) + (m[1] * inv[4]) + 
											(m[2] * inv[8]) + (m[3] * inv[12]);
	if ( determinant == 0 )
		return								false;

	inv[1] =  -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15]
				- m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
	inv[5] =   m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15]
				+ m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
	inv[9] =  -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15]
				- m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
	inv[13] =  m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14]
				+ m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
	inv[2] =   m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15]
				+ m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
	inv[6] =  -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15]
				- m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
	inv[10] =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15]
				+ m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
	inv[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14]
				- m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
	inv[3] =  -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11]
				- m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
	inv[7] =   m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11]
				+ m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
	inv[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11]
				- m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
	inv[15] =  m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10]
				+ m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];

	out_result							*=	1.0f / determinant;
	return								true;
}

bool inex::math::float4x4::try_invert								( float4x4 const& other )
{
	float const determinant = other.determinant4x3();
	if ( inex::math::is_zero( determinant, epsilon_7) )
	{
		float const epsilon = math::epsilon_7;
		if (
				math::is_relatively_zero( other.e11*other.e22 - other.e12*other.e21, determinant, epsilon ) ||
				math::is_relatively_zero( other.e01*other.e22 - other.e02*other.e21, determinant, epsilon ) ||
				math::is_relatively_zero( other.e01*other.e12 - other.e02*other.e11, determinant, epsilon ) ||
				math::is_relatively_zero( other.e10*other.e22 - other.e12*other.e20, determinant, epsilon ) ||
				math::is_relatively_zero( other.e00*other.e22 - other.e02*other.e20, determinant, epsilon ) ||
				math::is_relatively_zero( other.e00*other.e12 - other.e02*other.e10, determinant, epsilon ) ||
				math::is_relatively_zero( other.e10*other.e21 - other.e11*other.e20, determinant, epsilon ) ||
				math::is_relatively_zero( other.e00*other.e21 - other.e01*other.e20, determinant, epsilon ) ||
				math::is_relatively_zero( other.e00*other.e11 - other.e01*other.e10, determinant, epsilon )
			)
			return false;
	}
	*this		= invert_impl ( other, determinant );
	return		( true );
}