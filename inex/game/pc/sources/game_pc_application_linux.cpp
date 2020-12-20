#include "pch.h"

#include <inex/math_functions.h>
#include <inex/engine/api.h>
#include "game_pc_application.h"
#define ALLOCA	alloca


using game::application;

void	application::preinitialize				( )
{
	inex::engine::preinitialize		( g_command_line, "demo", __DATE__ );
}

void	application::postinitialize				( )
{
}
