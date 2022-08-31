// game_pc.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "game_pc_application.h"
#include <inex/core/core.h>
#include <inex/core/sources/ie_debug.h>
#pragma comment( lib, "delayimp.lib" )

static game::application	*	s_application;
string512 g_command_line;
static int s_exit_code					= 0;

struct guard {
	inline	guard						( )
	{
		// INEX_CONSTRUCT_REFERENCE		( s_application, game_title::application );
		s_application					= new game::application( );
		s_application->initialize		( );
	}

	inline	~guard						( )
	{
		s_exit_code						= s_application->get_exit_code();
		s_application->finalize			( );
		delete							s_application;
		// INEX_DESTROY_REFERENCE		( s_application );
	}
}; // struct guard

static void	main_protected				( pvoid )
{
	guard								guard;

	if ( s_application->get_exit_code() )
		return;

	s_application->execute				( );
	if ( s_application->get_exit_code() )
		return;

}

struct HINSTANCE__;
typedef HINSTANCE__* HINSTANCE;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	INEX_UNREFERENCED_PARAMETERS		( hInstance, hPrevInstance, nCmdShow, lpCmdLine );
	strcpy 								( g_command_line, GetCommandLine( ) );
	inex::debug::protected_call			( &main_protected, 0 );
	return								( s_exit_code );
}