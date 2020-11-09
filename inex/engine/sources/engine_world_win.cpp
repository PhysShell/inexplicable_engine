#include "pch.h"
#include "engine_world.h"
//#include "rpc.h"
// input world.h
#include <inex/render/base/engine_renderer.h>
#include <inex/core/core.h>
#include <inex/render/api.h>


#undef NOUSER
#undef NOMSG
#undef NOWINSTYLES
#undef NOWINMESSAGES
#undef NOSYSMETRICS
#undef NOSHOWWINDOW
#undef NOWINOFFSETS
#define _WIN32_WINNT				0x0500

#include <objbase.h>				// for COINIT_MULTITHREADED

//#pragma comment( lib, "delayimp.lib" )

using inex::engine::engine_world;

static pcstr s_window_id					=  "Renderer Window";
static pcstr s_window_class_id				=  "Renderer Window Class ID";

static WNDCLASSEX s_window_class;

static inex::engine::engine_world*			s_world	= 0;

static LRESULT APIENTRY message_processor	( HWND window_handle, UINT message_id, WPARAM w_param, LPARAM l_param )
{
	switch ( message_id ) {
		case WM_DESTROY: {
			PostQuitMessage	( 0 );

			return			( 0 );
		}
		case WM_ACTIVATE: {
			//u16 fActive						= LOWORD(w_param);
			//BOOL fMinimized					= (BOOL) HIWORD(w_param);
			//bool bActive					= ((fActive!=WA_INACTIVE) && (!fMinimized)) ? true : false;

			//if (bActive != s_world->app_is_active())
			//{
			//	if (bActive)
			//	{
			//		s_world->on_app_activate( );
			//		while (	ShowCursor( FALSE ) >= 0 );
			//	}else
			//	{
			//		s_world->on_app_deactivate( );
			//		while (	ShowCursor( TRUE ) < 0 );
			//	}
			//}
			//if ( (w_param == WA_ACTIVE) || (w_param == WA_CLICKACTIVE) ) {
			//	if ( !s_world->editor_world() )
			//		while (	ShowCursor( FALSE ) >= 0 );

			//	s_world->on_app_activate( );
			//	
			//	break;
			//}

			//ASSERT			( w_param == WA_INACTIVE );
			//if ( !s_world->editor_world() )
			//	while (	ShowCursor( TRUE ) < 0 );

			break;
		}
	}
	
	return					( DefWindowProc( window_handle, message_id, w_param, l_param ) );
}

static void create_window			( HWND& result )
{
	WNDCLASSEX const temp	=
	{
		sizeof( WNDCLASSEX ),
		CS_CLASSDC,
		&message_processor,
		0L,
		0L, 
		GetModuleHandle( 0 ),
		NULL,
		NULL,
		NULL,
		NULL,
		s_window_class_id,
		NULL
	};

	s_window_class			= temp;
	VERIFY					( RegisterClassEx			( &s_window_class ) );

	u32 const screen_size_x	= GetSystemMetrics( SM_CXSCREEN );
	u32 const screen_size_y	= GetSystemMetrics( SM_CYSCREEN );

	DWORD const	window_style = WS_OVERLAPPED;// | WS_CAPTION;

	u32 window_size_x		= 260;
	u32 window_size_y		= 640;


	//u32 const window_sizes_x []	= { 1024, 800, 640 };
	//u32 const window_sizes_y []	= { 768, 600, 480 };
	//for ( u32 i=0; i<3; ++i ) {
	//	if ( window_sizes_x[i] < screen_size_x && 
	//		 window_sizes_y[i] < screen_size_y )
	//	{
	//		window_size_x	= window_sizes_x[i];
	//		window_size_y	= window_sizes_y[i];
	//		break;
	//	}
	//}

	//ASSERT_S				(window_size_x);

	RECT		window_size = { 0, 0, window_size_x, window_size_y };
	AdjustWindowRect		(&window_size, window_style, false);

	result					= 
		CreateWindow (
			s_window_class_id,
			s_window_id,
			window_style,
			( screen_size_x - window_size.right ) / 2,
			( screen_size_y - window_size.bottom ) / 2,
			window_size.right - window_size.left,
			window_size.bottom - window_size.top,
			GetDesktopWindow( ),
			0,
			s_window_class.hInstance,
			0
		);

	VERIFY				( result );
}

void engine_world::initialize_core	( )
{
	//if ( true )//command_line_editor( ) )
	//	CoInitializeEx		( 0, COINIT_APARTMENTTHREADED );
	//else
	//	CoInitializeEx		( 0, COINIT_MULTITHREADED );
		
	pcstr debug_thread_id	= 0;

	if ( !command_line_editor() )
		core::initialize	( debug_thread_id, core::create_log, core::perform_debug_initialization );
	else
		core::initialize	( debug_thread_id, core::create_log, core::delay_debug_initialization );
}

void engine_world::create_render	( )
{
	s_world					= this;

	//if ( !m_editor ) {
		//create_window		( m_window_handle );
		//m_main_window_handle= m_window_handle;
	//}

	m_render_world		= render::create_world( *this, m_window_handle );

// 	if ( !s_dx10 )
// 		m_render_world		= render_gl4::create_world( *this, m_window_handle );
// 	else
// 		m_render_world		= render::dx10::create_world( *this, m_window_handle );

	ASSERT_S					( m_render_world );
}

void engine_world::destroy_render	( )
{
	render::destroy_world( m_render_world );

	ShowWindow				( m_window_handle, SW_HIDE );

	ASSERT_S					( s_world );
	s_world					= 0;
}

void engine_world::show_window		( )
{
//	if ( m_editor ) {
//		SetForegroundWindow	( m_editor->main_handle( ) );
//		return;
//	}

	ShowWindow				( m_window_handle, SW_SHOW );
	SetForegroundWindow		( m_window_handle );
//	on_activate				( );
}

bool engine_world::process_messages( )
{
	ASSERT_S				( !m_editor );

	MSG						message;
	while ( PeekMessage( &message, 0, 0, 0, PM_REMOVE ) ) {
		TranslateMessage	( &message );
		DispatchMessage		( &message );

		if ( message.message == WM_QUIT )
			return			( false );
	}

	return					( true );
}

void engine_world::run				( )
{
	//m_timer.start			( );
	m_destruction_started		= false;
	// engine loop
	for ( ;; )
	{
		//LOGGER( "loop reached " );
		
		
		//if (  getchar( ) == 'Q' )
		//	m_destruction_started	= true;

		if ( m_destruction_started )
			return;

		tick				( );
	}
}

pcstr engine_world::get_resource_path		( ) const
{
	return								"../../resources";
}

pcstr engine_world::get_mounts_path		( ) const
{
	return								"../../mounts";
}

pcstr engine_world::get_underscore_G_path	( ) const
{
	return								"../../resources/scripts";
}

void engine_world::enable_game						( bool value )
{
	bool bdraw_editor	= !value;
	bool bdraw_game		= value;
	//render_world().set_editor_render_mode(bdraw_editor, bdraw_game);
	enable_game_impl	( value );
}

void engine_world::post_initialize	( )
{
	//if ( command_line_editor() )
		//rpc::run			( rpc::editor, boost::bind( &engine_world::initialize_editor_thread_ids, this), rpc::continue_process_loop, rpc::wait_for_completion );
	show_window				( );
	//rpc::run				( rpc::editor, boost::bind( &engine_world::show_window, this), rpc::break_process_loop, rpc::wait_for_completion );
}