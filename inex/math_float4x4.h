////////////////////////////////////////////////////////////////////////////
//	Created 	: 07.11.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_FLOAT4X4_H_INCLUDED
#   define MATH_FLOAT4X4_H_INCLUDED



namespace inex {
namespace math {

class float4;
class float3;

class float4_pod
{
public:
    typedef float           type;

public:
	union
	{
		struct 
		{
			type		x;
			type		y;
			type		z;
			type		w;
		};
			struct
		{
			type		r;
			type		g;
			type		b;
			type		a;
		};

		type			elements[4];
	};

public:
	inline float3 const& xyz			( ) const
	{
		return		( ( float3& )( *this ) );
	}

	inline float3  xyz					( ) 
	{
		return		( ( float3& )( *this ) );
	}

	inline bool valid					( ) const
	{
		return		( math::valid( x ) && math::valid( y ) && math::valid( z ) && math::valid( w ) );
	}

	inline float4& operator *=			( type const value )
	{
		x			*= value;
		y			*= value;
		z			*= value;
		w			*= value;

		return		( ( float4& )( *this ) ); // was static casted
	}

	inline float4& operator /=			( type const value )
	{
		ASSERT_S	( !is_relatively_zero( math::max( math::abs(x), math::abs(y), math::abs(z), math::abs(w)), value ) );

		x			/= value;
		y			/= value;
		z			/= value;
		w			/= value;

		return		( ( float4& )( *this ) ); // was static casted
	}

}; // class float4_pod



class float4 : public float4_pod
{
public:
	inline				float4			( )										{ x = y = z = w = 0; }
	//inline				float4			( type x_, type y_, type z_, type w_ )	{ x = x_; y = y_; z = z_; w = w_; }
	//inline				float4			( float3 const& xyz, type w );
	inline				float4			( float4_pod const& other )				{ x = other.x; y = other.y; z = other.z; w = other.w; }
	inline				float4			( type const other_x, type const other_y, type const other_z, type const other_w )
	{
		x			= other_x;
		y			= other_y;
		z			= other_z;
		w			= other_w;
	}

	inline				float4			( float3 const& xyz, type const other_w )
	{
		x			= xyz.x;
		y			= xyz.y;
		z			= xyz.z;
		w			= other_w;
	}

	inline	type&		operator [ ]	( unsigned index )						{ return elements[ index ]; }
	inline	type const&	operator [ ]	( unsigned index ) const				{ return elements[ index ]; }

}; // struct float4

class INEX_CORE_API float4x4
{
public:
    typedef float           type;

public:
	union
	{
		struct
		{
			float4_pod	i,j,k,c;
		};

		type			elements[ 16 ];
		struct
		{
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

	inline float4			get_single	( u8 const index )						{ ASSERT_S( 0 < index < 4 ); return float4( lines[ index ] ); }

	inline float4x4&		identity	( )
	{
		i			= float4( 1.f, 0.f, 0.f, 0.f );
		j			= float4( 0.f, 1.f, 0.f, 0.f );
		k			= float4( 0.f, 0.f, 1.f, 0.f );
		c			= float4( 0.f, 0.f, 0.f, 1.f );

		return		( *this );
	}

	inline float		determinant4x3	( ) const
	{
		return		(
			e00 * ( e11*e22 - e12*e21 ) -
			e01 * ( e10*e22 - e12*e20 ) +
			e02 * ( e10*e21 - e11*e20 )
		);
	}

	bool		try_invert								( float4x4 const& other );							/// this is 4x3 invert

	inline	bool		valid							( ) const;

	inline	float4x4&	operator *=						( float4x4::type value );

	// inline	void	print				( ) const
	// {
	// 	LOGGER( "\n" );
	// 	LOGGER( "-- [float4x4][debug][i][%.2f][%.2f][%.2f][%.2f]\n", elements[0], elements[4], elements[8], elements[12] );
	// 	LOGGER( "-- [float4x4][debug][j][%.2f][%.2f][%.2f][%.2f]\n", elements[1], elements[5], elements[9], elements[13] );
	// 	LOGGER( "-- [float4x4][debug][k][%.2f][%.2f][%.2f][%.2f]\n", elements[2], elements[6], elements[10], elements[14] );
	// 	LOGGER( "-- [float4x4][debug][c][%.2f][%.2f][%.2f][%.2f]\n", elements[3], elements[7], elements[11], elements[15] );
	// }

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
float4x4	mul4x4					( math::float4x4 const& left, math::float4x4 const& right )
{
	NOT_IMPLEMENTED                 ( );
}

INEX_CORE_API inline
float4x4	translate4x4				( math::float4x4 const& other_matrix, math::float3 const& vector )
{
	math::float4x4	result;
	result			= identity4x4( );

	result[ 12 ]	= vector[ 0 ];
	result[ 13 ]	= vector[ 1 ];
	result[ 14 ]	= vector[ 2 ];

	return			( result );

}

INEX_CORE_API inline
float4x4	rotate_yaw					( math::float4x4 const& other, math::float4x4::type const angle )
{
	float radians			= math::degrees_to_radians( angle );
	math::float4x4 result	= identity4x4( );

	result[ 0 ]				= cosf	( radians );
	result[ 8 ]				= sinf	( radians );
	result[ 2 ]				=-sinf	( radians );
	result[ 10 ]			= cosf	( radians );

	return					( result * other );

}

INEX_CORE_API inline
float4x4	transpose					( float4x4 const& other )
{
	float4x4	result;

	result.i	= float4( other.e00, other.e10, other.e20, other.e30 );
	result.j	= float4( other.e01, other.e11, other.e21, other.e31 );
	result.k	= float4( other.e02, other.e12, other.e22, other.e32 );
	result.c	= float4( other.e03, other.e13, other.e23, other.e33 );

	return		( result );
}

inline bool float4x4::valid					( ) const
{
	return		( i.valid( ) && j.valid( ) && k.valid( ) && c.valid( ) );
}

inline float4x4& float4x4::operator *=		( float4x4::type value )
{
	i			*= value;
	j			*= value;
	k			*= value;
	c			*= value;

	return		( *this );
}

INEX_CORE_API float4x4	mul4x3			( float4x4 const& left, float4x4 const& right );	/// this is 4x3 multiplication
INEX_CORE_API float4x4	invert4x3		( float4x4 const& other );							/// this is 4x3 invert, for full one call invert4x4

INEX_CORE_API float4x4	invert4x4		( float4x4 const& matrix_to_invert );
INEX_CORE_API bool		try_invert4x4	( float4x4 const& matrix_to_invert, float4x4& out_result );

} // namespace math
} // namespace inex

#endif // #ifndef MATH_FLOAT4X4_H_INCLUDED
