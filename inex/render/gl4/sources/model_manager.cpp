#include "pch.h"
#include "model_manager.h"
#include <inex/render/common/render_model.h>

namespace inex		{
namespace render	{

void	model_manager::render_static ( )
{
	if( m_visuals.empty( ) )
		return;

	u16 type = 999;
	Visuals::const_iterator		i = m_visuals.begin( );
	Visuals::const_iterator		e = m_visuals.end( );
	for ( ; i != e; ++i )
		if( *i )
			( *i )->render		( );
}



void	model_manager::load_vertex_buffers ( resources::managed_resource_ptr const& geometry )
{
	// this actually need to load from file
	
	render_mesh* mesh		= memory::ie_new< render_mesh >( );

	//VERIFY(!"Need to replace geometry with new render_model (commened lines)");

	glGenBuffers			( 1 , &mesh->vertex_buffer_id );
	glBindBuffer			( GL_ARRAY_BUFFER, mesh->vertex_buffer_id );
	//glBufferData			( GL_ARRAY_BUFFER, sizeof ( geometry.m_vertices.elements ), geometry.m_vertices.elements, GL_STATIC_DRAW );
	glBindBuffer			( GL_ARRAY_BUFFER, 0 );

	//LOGGER					( "* [Loading VB] %d verts, %d KiB", 
	//						sizeof( geometry.m_vertices.elements ) / sizeof ( float ), 
	//						sizeof ( geometry.m_vertices.elements ) / 1024 );

	glGenVertexArrays		( 1, &mesh->index_buffer_id );
	glBindVertexArray		( mesh->index_buffer_id );
	glEnableVertexAttribArray ( 0 );
	glBindBuffer			( GL_ARRAY_BUFFER, mesh->vertex_buffer_id );
	glVertexAttribPointer	( 0, 4, GL_FLOAT, GL_FALSE, 0, nullptr );

	

	m_vertex_buffers		.push_back( mesh );
}

void	model_manager::load_shaders ( resources::managed_resource_ptr const& geometry )
{
	LOGGER						( " - [shader] loading shaders for geometry.. " );
	render_visual* temp			=	memory::ie_new< triangle_primitive_visual >( );
	
	//VERIFY(!"Need to replace geometry with new render_model (commened lines)");

	//temp->m_vshader.create			( render_ogl::enum_shader_type_vertex, geometry.vs );
	//temp->m_fshader.create			( render_ogl::enum_shader_type_fragment, geometry.fs );

	//temp->m_program.create			( );
	//temp->m_program.attach			( temp->m_vshader, temp->m_fshader );
	//temp->m_program.link			( );

	//temp->m_vshader.destroy			( );
	//temp->m_fshader.destroy			( );

	temp->set_shader				(geometry.vs, geometry.fs);

	auto it							= m_vertex_buffers.rbegin( );
	temp->mesh( )->vertex_buffer_id	= ( *it )->vertex_buffer_id;
	temp->mesh( )->index_buffer_id	= ( *it )->index_buffer_id;

	LOGGER( "[info]\t:\tused last VB id: %d, check for consistency in new obj: %d", ( *it )->vertex_buffer_id, temp->mesh( )->vertex_buffer_id );

	m_visuals						.push_back( temp );
}

void	model_manager::load_visuals ( memory::chunk_reader& reader )
{
	INEX_UNREFERENCED_PARAMETERS( reader );
	NOT_IMPLEMENTED( );
}

void	model_manager::add_static ( resources::managed_resource_ptr const& collision, resources::managed_resource_ptr const& geometry, resources::managed_resource_ptr const& visuals )
{
	INEX_UNREFERENCED_PARAMETERS( collision, visuals );

	typedef memory::chunk_reader	Reader;

	{
		load_vertex_buffers		( geometry );
		//load_index_buffers		( reader );
	}
	{
		load_shaders			( geometry );

		//load_visuals			( Reader( ) );
	}

	LOGGER( "static object loaded. overall : %d", m_visuals.size( ) );
}


} // namespace render
} // nemspace inex