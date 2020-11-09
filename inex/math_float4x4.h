////////////////////////////////////////////////////////////////////////////
//	Created 	: 07.11.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_FLOAT4X4_H_INCLUDED
#   define MATH_FLOAT4X4_H_INCLUDED



namespace inex {
namespace math {

class float4_pod
{
public:
    typedef float           type;

public:
	union {
		struct {
			type		x;
			type		y;
			type		z;
			type		w;
		};
			struct {
			type		r;
			type		g;
			type		b;
			type		a;
		};

		type			elements[4];
	};

public:

}; // class float4_pod

class float4 : public float4_pod {
public:
	inline				float4			( )										{ x = y = z = w = 0; } 
	inline				float4			( type x_, type y_, type z_, type w_ )	{ x = x_; y = y_; z = z_; w = w_; }
	//inline				float4			( float3 const& xyz, type w );
	inline				float4			( float4_pod const& other )				{ x = other.x; y = other.y; z = other.z; w =other.w; }
	inline	type&		operator [ ]	( unsigned index )						{ return elements[ index ]; }
	inline	type const&	operator [ ]	( unsigned index ) const				{ return elements[ index ]; }

}; // struct float4

class INEX_CORE_API float4x4
{
public:
    typedef float           type;

public:
	union {
		struct {
			float4_pod	i,j,k,c;
		};

		type			elements[ 16 ];
		struct {
			type		e00, e01, e02, e03;
			type		e10, e11, e12, e13;
			type		e20, e21, e22, e23;
			type		e30, e31, e32, e33;
		};
		float4_pod		lines[ 4 ];
	};

public:
	inline					float4x4	( )	: i( float4( ) ),  j( float4( ) ), k( float4( ) ), c( float4( ) )	{ }
	inline					float4x4	( float const raw_array [ 16 ] )
	{
		for ( u16 i = 0; i < 16; ++i )
			elements[ i ]	= raw_array[ i ];
	}

	inline					float4x4	( float4 const& other_i, float4 const& other_j, float4 const& other_k, float4 const& other_c ) : i( other_i ), j( other_j ), k( other_k ), c( other_c ) { }
	inline	float4x4&		operator =	( float4x4 const& other )
	{
		u16 index			= 0;

		for ( auto const& i : other.elements )
			elements[ index ++ ]	= i;

		return				( *this );
	}

	inline	type&		operator [ ]	( unsigned index )						{ return elements[ index ]; }
	inline	type const&	operator [ ]	( unsigned index ) const				{ return elements[ index ]; }

	inline	float4			transform	( float4 const& v ) const
	{
		float4		result;

		result[ 0 ]	= elements[ 0 ]*v[ 0 ] + elements[ 4 ]*v[ 1 ] + elements[ 8 ]*v[ 2 ] + elements[ 12 ]*v[ 3 ];
		result[ 1 ]	= elements[ 1 ]*v[ 0 ] + elements[ 5 ]*v[ 1 ] + elements[ 9 ]*v[ 2 ] + elements[ 13 ]*v[ 3 ];
		result[ 2 ]	= elements[ 2 ]*v[ 0 ] + elements[ 6 ]*v[ 1 ] + elements[ 10 ]*v[ 2 ]+ elements[ 14 ]*v[ 3 ];
		result[ 3 ]	= elements[ 3 ]*v[ 0 ] + elements[ 7 ]*v[ 1 ] + elements[ 11 ]*v[ 2 ]+ elements[ 15 ]*v[ 3 ];

		return		( result );
	}

	inline	void	print				( ) const
	{
		LOGGER( "\n" );
		LOGGER( "[%.2f][%.2f][%.2f][%.2f]\n", elements[0], elements[4], elements[8], elements[12] );
		LOGGER( "[%.2f][%.2f][%.2f][%.2f]\n", elements[1], elements[5], elements[9], elements[13] );
		LOGGER( "[%.2f][%.2f][%.2f][%.2f]\n", elements[2], elements[6], elements[10], elements[14] );
		LOGGER( "[%.2f][%.2f][%.2f][%.2f]\n", elements[3], elements[7], elements[11], elements[15] );
	}

}; // class float4x4

// 4x4 operations
INEX_CORE_API inline
math::float4x4	identity4x4				( )
{
	return		math::float4x4( float4 ( 1.f, 0.f, 0.f, 0.f ), float4 ( 0.f, 1.f, 0.f, 0.f ), float4 ( 0.f, 0.f, 1.f, 0.f ), float4 ( 0.f, 0.f, 0.f, 1.f ) );
}

INEX_CORE_API inline
math::float4x4	zero4x4					( )
{
	return		math::float4x4( float4 ( 0.f, 0.f, 0.f, 0.f ), float4 ( 0.f, 0.f, 0.f, 0.f ), float4 ( 0.f, 0.f, 0.f, 0.f ), float4 ( 0.f, 0.f, 0.f, 0.f ) );
}

INEX_CORE_API inline
math::float4x4	operator *				( math::float4x4 const& left, math::float4x4 const& right )
{
	math::float4x4	result		= zero4x4( );
	s32			index		= 0;
	
	for ( int col = 0; col < 4; ++col ) {
		for ( int row = 0; row < 4; ++row ) {
			float sum		= 0.f;

			for ( int i = 0; i < 4; ++i ) {
				sum			+= right[ i + col * 4 ] * left[ i + row * 4 ];
			}

			result[ index ]= sum;
			++index;
		}
	}

	return					( result );

}

INEX_CORE_API inline
math::float4x4	mul4x4					( math::float4x4 const& left, math::float4x4 const& right )
{
	__assume( 0 );
	return							math::float4x4( );
}

INEX_CORE_API inline
math::float4x4	translate4x4				( math::float4x4 const& other_matrix, math::float3 const& vector )
{
	math::float4x4	result;
	result			= identity4x4( );

	result[ 12 ]	= vector[ 0 ];
	result[ 13 ]	= vector[ 1 ];
	result[ 14 ]	= vector[ 2 ];

	return			( result );

}

INEX_CORE_API inline
math::float4x4	rotate_yaw					( math::float4x4 const& other, math::float4x4::type const angle )
{
	float radians			= math::degrees_to_radians( angle );
	math::float4x4 result	= identity4x4( );

	result[ 0 ]				= cosf	( radians );
	result[ 8 ]				= sinf	( radians );
	result[ 2 ]				=-sinf	( radians );
	result[ 10 ]			= cosf	( radians );

	return					( result * other );

}


} // namespace math
} // namespace inex

#endif // #ifndef MATH_FLOAT4X4_H_INCLUDED
