#pragma once
namespace inex {
namespace render {

class camera {
public:
	inline					camera						( );

	inline void				set_view_transform			( math::float4x4 const & matrix);
	inline void				set_view_transform_only		( math::float4x4 const & matrix);
	inline void				set_projection_transform	( math::float4x4 const & matrix);

	inline math::float4x4 const&	get_view_transform			( ) const	{ return m_view;}
	inline math::float4x4 const&	get_culling_view_transform	( ) const	{ return m_culling_view;}
	//inline math::float4x4 const&	get_view_inverted_transform	( ) const	{ return m_view_inverted;}
	inline math::float4x4 const&	get_projection_transform	( ) const	{ return m_projection;}

private:
	math::float4x4				m_view;
	//math::float4x4			m_view_inverted;
	math::float4x4				m_projection;
	math::float4x4				m_culling_view;
}; // class camera

inline camera::camera							( )
{
	m_view.identity			( );
	//m_view_inverted.identity( );
	m_culling_view.identity	( );
	m_projection.identity	( );
}

inline void camera::set_view_transform			( math::float4x4 const & matrix)
{
	m_view					= matrix;
	//m_view_inverted			= invert4x3( m_view );
	m_culling_view			= matrix;
}

inline void camera::set_view_transform_only		( math::float4x4 const & matrix)
{
	m_view					= matrix;
	//m_view_inverted			= invert4x3( m_view );
}

inline void camera::set_projection_transform	( math::float4x4 const & matrix)
{
	m_projection			= matrix;
}

} // namespace render
} // namespace inex