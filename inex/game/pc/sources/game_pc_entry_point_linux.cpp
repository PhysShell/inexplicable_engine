// game_pc.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "game_pc_application.h"
#include <inex/core/core.h>
#include <inex/command_line.h>
#include <signal.h>

static game::application	*	s_application;

static int s_exit_code					= 0;
string512 g_command_line;


struct guard {
	inline	guard						( )
	{
		// INEX_CONSTRUCT_REFERENCE		( s_application, stalker2::application );
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



// in debug

static long	unhandled_exception_handler					(  )
{
	if ( !inex::core::initialized( ) )
	{
		//inex::core::debug::platform::prologue_dump_call_stack	( exception_information );
		//inex::debug::terminate	( "" );
	}

	return						( 0 );
}


void   unhandled_exception_filter	( s32 sig, siginfo_t *info, pvoid xxx )
{
	__builtin_unreachable( );
}

typedef void protected_function_type				( pvoid );

typedef struct sigaction sigaction_type;

void protected_call							( protected_function_type* function_to_call, pvoid argument )
{
	// core::debug::set_thread_stack_guarantee	( );
	//sigaction_type sa 					= { 0 };

	//sa.sa_sigaction 					= unhandled_exception_filter;
    //sa.sa_flags 						= SA_NODEFER; // To ensure SIGALRM doesn't remain blocked
	//sigaction							( SIGALRM, &sa, 0 );
	try {
		( *function_to_call	)	( argument );
	}
	catch ( ... ) {
		exit							( 1 );
	}
}

int		main ( s32 argc, pstr * argv )
{
	inex::command_line::concat_command_line( argc, argv, g_command_line );
	protected_call						( &main_protected, 0 );
	return								( s_exit_code );
}
