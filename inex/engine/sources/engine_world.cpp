#include "pch.h"
#include "engine_world.h"
//#include <inex/input/api.h>
//#include <inex/input/world.h>
//#include <inex/animation/api.h>
#include <inex/render/base/engine_renderer.h>
#include <inex/render/base/world.h>
//#include <inex/resources_fs.h>
#include <inex/core/core.h>
//#include "rpc.h"
//#include <boost/function.hpp>
//#include <boost/bind.hpp>
//#include <inex/network/api.h>
//#include <inex/sound/api.h>
//#include <inex/fs_utils.h>

using inex::engine::engine_world;

engine_world::engine_world				( pcstr command_line, pcstr application, pcstr build_date ) :
	m_input_world						( NULL ),
	m_network_world						( NULL ),
	m_sound_world						( NULL ),
	m_render_world						( NULL ),
	m_window_handle						( NULL ),
	m_main_window_handle				( NULL ),
	m_last_frame_time					( 0 ),
	m_logic_frame_id					( 0 ),
	m_editor_frame_id					( 0 ),
	m_destruction_started				( 0 ),
	m_early_destruction_started			( false ),
	m_exit_code							( 0	),
	m_logic_frame_ended					( false ),
	m_editor_frame_ended				( false ),
	m_initialized						( false ),
	m_game_enabled						( true ),
	m_game_paused_last					( false ),
	m_engine_user_module_proxy			( NULL ),
	m_engine_user_world					( NULL ),
	m_app_active						( false )
{
	core::preinitialize					( this, 
										  command_line, 
										  0, 
										  application,
										  build_date
										);
	//g_allocator.do_register				(  64*KiB,	"engine"	);
	//m_input_allocator.do_register		(  64*Kb,	"input"		);
	//m_engine_user_allocator.do_register	(	1*Mb,	"game"		);
	//m_render_allocator.do_register		(	8*Mb,	"render"	);
	//m_ui_allocator.do_register			(  64*Kb,	"ui"		);
	//m_physics_allocator.do_register		(  64*Kb,	"physics"	);
	//m_network_allocator.do_register		(  64*Kb,	"network"	);
}

static bool s_resource_callbacks_dispatched	= false;

static void thread_dispatch_callbacks	( )
{

}

struct empty {
	static void function( ){}// we need this function for synchronization purposes
}; // struct empty

engine_world::~engine_world		( )
{
	if ( m_early_destruction_started )
	{
		core::finalize					( );
		return;
	}

	destroy_render						( );

	core::finalize						( );
}

void engine_world::initialize_render	( )
{
	ASSERT_S							( m_initialized );

	//render::memory_allocator			( m_render_allocator, m_engine_user_allocator, m_editor_allocator );

	ASSERT_S							( !m_render_world );
	create_render						( );
	ASSERT_S							( m_render_world );
}

static void on_mounted_disk				( bool const result )
{
	INEX_UNREFERENCED_PARAMETERS		( result );
	ASSERT_S							( result );
}

#ifdef DEBUG
static inex::timing::timer				s_debug_engine_timer;
#endif // #ifdef DEBUG


void engine_world::initialize		( )
{
	ASSERT_S							( !m_initialized );
	m_initialized						= true;

	initialize_core						( );

	if ( m_destruction_started )
	{
		m_early_destruction_started		= true;
		return;
	}


	// initialize_editor					( );
	initialize_render					( );
	// initialize_network					( );
	//initialize_sound					( );

	initialize_logic					( );

	post_initialize						( );

	enable_game							( !m_editor );

}

void engine_world::tick					( )
{
	bool result							= false;
	//if( !m_logic_frame_ended )
		//result							= !m_render_world->engine( ).run( m_game_enabled );
	logic_tick							( );

	//bool result_editor					= false;
	//if( (m_logic_frame_ended || !m_game_enabled || m_game_enabled == m_game_paused_last) && !m_editor_frame_ended )
		//result_editor					= !m_editor || !m_render_world->engine().run_editor_commands( true );
		 
	//if ( result || result_editor )
	//	m_last_frame_time				= m_timer.get_elapsed_sec ( );

}


namespace inex {
namespace testing {
	bool   run_tests_command_line ( );
} // namespace testing
} // namespace inex


void engine_world::load_level				( pcstr project_name )
{
	if ( command_line_editor_singlethread() ) {
		engine_user_world().load			( project_name );
		return;
	}

}

void engine_world::unload_level		( )
{
	if ( command_line_editor_singlethread() ) {
		engine_user_world().unload		( "" );
		return;
	}
}

bool engine_world::app_is_active( )
{
	return m_app_active;
}

void engine_world::on_app_activate( )
{
	m_app_active		= true;
	if ( m_input_world );
		//m_input_world->on_activate		( );

	//LOG_INFO("--app Activate--");
}

void engine_world::on_app_deactivate( )
{
	m_app_active		= false;
	if ( m_input_world );
		//m_input_world->on_deactivate	( );

	//LOG_INFO("--app DeActivate--");
}

void engine_world::enable_game_impl		( bool const value )
{
	if ( m_engine_user_world )
	{
		if ( command_line_editor_singlethread() ) 
		{
			engine_user_world().enable		( value );
		}
		else
		{

		}
	}

	m_game_enabled					= value;
}