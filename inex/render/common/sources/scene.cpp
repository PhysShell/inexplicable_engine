#include "pch.h"
#include "../scene.h"
#include "system_render.h"

static const u32 s_max_vertex_count	= 64*1024;

namespace inex {

namespace render {

void scene::update_triangles	( u32 const add_count )
{
	ASSERT_S				( add_count <= s_max_vertex_count );
	ASSERT_S				( m_triangle_vertices.size() <= s_max_vertex_count );
	if ( m_triangle_vertices.size( ) + add_count >= s_max_vertex_count )
		render_triangles		( );

	ASSERT_S						( m_triangle_vertices.size( ) + add_count < s_max_vertex_count );
}

void scene::render_triangles	( bool covering_effect )
{
	if ( m_triangle_vertices.empty( ) )
		return;

	ASSERT_D					( ( m_triangle_indices.size( ) % 3 ) == 0, "triangle indices count isn't divisible by 3" );

	system_renderer::reference().draw_triangles	(
		&*m_triangle_vertices.begin(),
		&*m_triangle_vertices.end(),
		&*m_triangle_indices.begin(),
		&*m_triangle_indices.end(),
		covering_effect
	);
	m_triangle_vertices.resize	( 0 );
	m_triangle_indices.resize	( 0 );
}

void scene::draw_triangles( debug_vertices_type const& vertices, debug_indices_type const& indices )
{
	update_triangles			( indices.size( ) );

	u16	const n					= ( u16 ) m_triangle_vertices.size( );
	m_triangle_vertices.insert	( m_triangle_vertices.end(), vertices.begin( ), vertices.end( ) );

	debug_indices_type::const_iterator	i = indices.begin( ); 
	debug_indices_type::const_iterator	e = indices.end( );
	for ( ; i != e; ++i )
		m_triangle_indices.push_back( n + *i );

	ASSERT_D					( ( m_triangle_indices.size( ) % 3 ) == 0, "triangle indices count isn't divisible by 3" );
}

void scene::flush( std::function< void ( bool ) > const& on_draw_scene )
{
	//backend::ref().reset_depth_stencil_target();

	on_draw_scene				( true );
	//render_lines				( );
	render_triangles			( );

	//backend::ref().reset_depth_stencil_target	( );
	//backend::ref().clear_depth_stencil			( D3D_CLEAR_DEPTH|D3D_CLEAR_STENCIL, 1.0f, 0);

	// render selected models
	//render_model_instances::const_iterator it			= m_selected_models.begin( );
	//render_model_instances::const_iterator const it_e	= m_selected_models.end( );
	//
	//render_surface_instances list;
	//for ( ;it != it_e; ++it ) 
	//{
	//	render_model_instance_impl_ptr const model		= ( *it );
	//	model->get_surfaces								( list, true );
	//}
	//
	//system_renderer::ref().draw_render_models_selection				( list );
	//system_renderer::ref().draw_particle_system_instance_selections	( m_particle_system_instances );
	//system_renderer::ref().draw_speedtree_instance_selections		( m_speedtree_instances );
	
	on_draw_scene				( false );
	//render_lines				( true );
	//render_triangles			( true );
}

} // namespace render
} // namespace inex