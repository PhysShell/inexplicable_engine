#include "pch.h"
#include <inex/render/common/sources/system_render.h>

namespace inex {
namespace render {

void system_renderer::draw_triangles	(
		vertex_colored const* const vertices_begin,
		vertex_colored const* const vertices_end,
		u16 const* const indices_begin,
		u16 const* const indices_end,
		bool covering_effect
	)
{
	//if (!is_effects_ready())
	//	return;
	
	ASSERT_S( vertices_begin < vertices_end );
	ASSERT_S( indices_begin  < indices_end );
	
	// Prepare ill vertex buffer.
	u32 voffset;
	u32 const vertices_size	= vertices_end - vertices_begin;
	//render::vertex_colored* vbuffer = (render::vertex_colored*) m_vertex_stream.lock( vertices_size, sizeof(render::vertex_colored), voffset);
	//memory::copy( vbuffer, vertices_size*sizeof(render::vertex_colored), vertices_begin, vertices_size*sizeof(render::vertex_colored));
	//m_vertex_stream.unlock();

	// Prepare index buffer
	u32 ioffset;
	u32 const indices_size	= indices_end - indices_begin;
	//u16* ibuffer = (u16*) m_index_stream.lock( indices_size, ioffset);
	//memory::copy( ibuffer, indices_size*sizeof(u16), indices_begin, indices_size*sizeof(u16));
	//m_index_stream.unlock();
	//
	//m_colored_geom->apply	();

	//if (covering_effect)
	//{
	//	m_sh_vcolor->apply		( effect_system_colored::cover);
	//}
	//else
	//{
	//	if (!m_color_write)
	//		m_sh_vcolor->apply		( effect_system_colored::voided);
	//	else 
	//	if( !m_grid_mode)
	//		m_sh_vcolor->apply		( effect_system_colored::solid);
	//	else
	//		m_sh_vcolor->apply		( effect_system_colored::stenciled);
	//}
	
	//backend::ref().set_ps_constant ( m_grid_density_constant, m_grid_density);
	// opengl DRAW calls go into the function below
	//backend::ref().render_indexed( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, indices_size, ioffset /* ? */, voffset );
}

} // namespace render
} // namespace inex