#pragma once
namespace inex {
namespace math {
	inline u32	color_rgba	(u32 r, u32 g, u32 b, u32 a)	{	return ((a&0xff)<<24)|((r&0xff)<<16)|((g&0xff)<<8)|(b&0xff);	}
	inline u32	color_xrgb	(u32 r, u32 g, u32 b)			{	return color_rgba(r, g, b, 255);	}

	inline u32	color_rgba	(float r, float g, float b, float a) 
	{ return color_rgba( u32(math::floor(r*255) & 0xff), u32(math::floor(g*255) & 0xff), u32(math::floor(b*255) & 0xff), u32(math::floor(a*255) & 0xff) ); }

	inline u32	color_get_A		( u32 c )	{ return (((c) >> 24) & 0xff);	}
	inline u32	color_get_R		( u32 c )	{ return (((c) >> 16) & 0xff);	}
	inline u32	color_get_G		( u32 c )	{ return (((c) >> 8)  & 0xff);	}
	inline u32	color_get_B		( u32 c )	{ return ((c) & 0xff); }

	class INEX_CORE_API color
	{
	public:
		inline		color		( ):m_value(0xffffffff){}
		
		inline	explicit color	( u32 value ):m_value(value){} 
		inline			 color	( u32 r, u32 g, u32 b, u32 a ){ set(r,g,b,a); } 
		inline			 color	( u32 r, u32 g, u32 b ){ set(r,g,b,255); } 
		inline			 color	( int r, int g, int b, int a ){ set(r,g,b,a); } 
		inline			 color	( float3 const& value ){ m_value = color_rgba(value.x,value.y,value.z,1.f); } 
		inline			 color	( float r, float g, float b, float a ){ m_value = color_rgba(r,g,b,a); } 

		inline void	set			( u32 r, u32 g, u32 b, u32 a )	{ m_value = color_rgba(r,g,b,a); }
		inline color operator *	( float const intensity ) const { return color( math::floor(r*intensity), math::floor(g*intensity), math::floor(b*intensity), math::floor(a*intensity)); }

		inline u32	get_A		( )	const { return color_get_A(m_value);	}
		inline u32	get_R		( )	const { return color_get_R(m_value);	}
		inline u32	get_G		( )	const { return color_get_G(m_value);	}
		inline u32	get_B		( )	const { return color_get_B(m_value);	}

		inline float	get_Af		( )	const { return color_get_A(m_value)/255.0f;	}
		inline float	get_Rf		( )	const { return color_get_R(m_value)/255.0f;	}
		inline float	get_Gf		( )	const { return color_get_G(m_value)/255.0f;	}
		inline float	get_Bf		( )	const { return color_get_B(m_value)/255.0f;	}

		inline void get_RGBA	( u32& r, u32& g, u32& b, u32& a){ r=get_R(); g=get_G(); b=get_B(); a=get_A(); }
		inline void get_RGBA	( float& r, float& g, float& b, float& a){ r=get_R()/255.0f; g=get_G()/255.0f; b=get_B()/255.0f; a=get_A()/255.0f; }

		inline void set_A		( u32 val ) { a=val&0xff;}
		inline void set_R		( u32 val ) { r=val&0xff;}
		inline void set_G		( u32 val ) { g=val&0xff;}
		inline void set_B		( u32 val ) { b=val&0xff;}

	#if defined(_MSC_VER)
	#	pragma warning(push)
	#	pragma warning(disable:4201)
	#endif // #if defined(_MSC_VER)
		union{
			struct{
				u8	b;
				u8	g;
				u8	r;
				u8	a;
			};
			u32				m_value;
		};
	#if defined(_MSC_VER)
	#	pragma warning(pop)
	#endif // #if defined(_MSC_VER)
	};// class color
} // namespace math
} // namespace inex