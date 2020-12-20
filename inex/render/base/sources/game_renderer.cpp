#include "pch.h"
#include "game_renderer.h"
#include <inex/render/base/world.h>
#include <inex/render/base/world.h>
#include <inex/render/base/platform.h>
#include "command_processor.h"
//#include "command_add_static.h"
//#include "command_delegate.h"
//#include "command_add_visual.h"
//#include "command_update_visual.h"
//#include "command_remove_visual.h"
//#include "command_render_visuals.h"
//#include "command_change_visual_shader.h"
//#include "command_update_visual_vertex_buffer.h"
//#include "command_add_light.h"
//#include "command_update_light.h"
//#include "command_remove_light.h"
//#include "command_terrain_add_cell.h"
//#include "command_terrain_remove_cell.h"
//
//#include "debug_renderer.h"

using inex::render::game::game_renderer;
using inex::render::base_world;
using inex::render::buffer_fragment;
using inex::math::float4x4;
//using inex::resources::managed_resource_ptr;

game_renderer::game_renderer				( base_world& world, inex::render::platform& platform ) :
	m_world								( world ),
	m_platform							( platform )
{
	m_debug				= 0;//NEW ( debug::debug_renderer )	( world.commands(), *inex::render::logic::g_allocator, platform );
}

game_renderer::~game_renderer				( )
{
	//DELETE				( m_debug );
}

//void game_renderer::add_static		( u32 id, inex::render::visual_ptr v, float4x4 const& transform, bool selected = false, bool system_object )
//{
//	m_world.commands( ).push_command	( L_NEW( command_add_static ) ( m_world, collision, geometry, visuals ) );
//}

void game_renderer::draw_static		( )
{
	//m_world.commands( ).push_command	( L_NEW( command_delegate ) ( std::bind( &game_renderer::draw_static_impl, this ) ) );
}

void game_renderer::draw_static_impl	( )
{
	//m_world.draw_static					( );
}

void game_renderer::draw_frame		( )
{
	m_world.draw_frame_logic			( );
	// Sleep	( 1000 );
	//m_world.commands().push_command	( L_NEW( command_delegate ) ( std::bind( &inex::render::base_world::draw_frame_logic, &m_world ) ) );
}

void game_renderer::set_command_push_thread_id	( )
{
	m_world.commands( ).set_push_thread_id ( );
}

void game_renderer::set_command_processor_frame_id	( u32 frame_id )
{
	m_world.commands( ).set_frame_id( frame_id );
}
void game_renderer::add_visual				( u32 id, inex::render::visual_ptr v, float4x4 const& transform, bool selected, bool system_object )
{
	//m_world.commands( ).push_command	( L_NEW( command_add_visual ) ( m_world, id, v, transform, selected, system_object, false ) );
}

void game_renderer::remove_visual			( u32 id )
{
	//m_world.commands( ).push_command	( L_NEW( command_remove_visual ) ( m_world, id ) );
}

void game_renderer::update_visual			( u32 id, float4x4 const& transform, bool selected )
{
	//m_world.commands( ).push_command	( L_NEW( command_update_visual ) ( m_world, id, transform, selected  ) );
}

void game_renderer::render_visuals			(  )
{
	//m_world.commands( ).push_command	( L_NEW( command_render_visuals ) ( m_world ) );
}

//void game_renderer::update_visual_vertex_buffer	( inex::render::visual_ptr const& object, inex::vectora<buffer_fragment> const& fragments )
//{
//	m_world.commands( ).push_command	( L_NEW( command_update_visual_vertex_buffer ) ( m_world, object, fragments, *inex::render::editor::g_allocator ) );
//}

//void game_renderer::change_visual_shader		( inex::render::visual_ptr const& object, char const* shader, char const* texture )
//{
//	m_world.commands( ).push_command	( L_NEW( command_change_visual_shader ) ( m_world, object, shader, texture ) );
//}
namespace inex{ namespace render { namespace debug { struct renderer { }; } } }
inex::render::debug::renderer& game_renderer::debug	( )
{
	ASSERT_S	    ( m_debug );
	NOT_IMPLEMENTED ( );
//  return          *m_debug;
}

void game_renderer::initialize_command_queue	( inex::render::engine::command* null_command )
{
	m_world.commands().initialize_queue	( null_command );
}

//void game_renderer::add_light				( u32 id, inex::render::light_props const& props)
//{
//	m_world.commands( ).push_command	( L_NEW( command_add_light ) ( m_world, id, props, false) );
//}
//
//void game_renderer::update_light				( u32 id, inex::render::light_props const& props)
//{
//	m_world.commands( ).push_command	( L_NEW( command_update_light ) ( m_world, id, props, false) );
//}

void game_renderer::remove_light				( u32 id)
{
	//m_world.commands( ).push_command	( L_NEW( command_remove_light ) ( m_world, id, false) );
}

void game_renderer::terrain_add_cell			( inex::render::visual_ptr v )
{
	//m_world.commands( ).push_command	( L_NEW( command_terrain_add_cell ) ( m_world, v, false) );
}

void game_renderer::terrain_remove_cell		( inex::render::visual_ptr v)
{
	//m_world.commands( ).push_command	( L_NEW( command_terrain_remove_cell ) ( m_world, v, false) );
}
