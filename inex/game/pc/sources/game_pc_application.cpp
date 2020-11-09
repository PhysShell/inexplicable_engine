#include "pch.h"
#include "game_pc_application.h"
#include <inex/engine/api.h>

using game::application;

void application::initialize( )
{
	m_exit_code						= 0;
	preinitialize					( );
	inex::engine::initialize		( &m_game_proxy );
	postinitialize					( );
}

void application::finalize	( )
{
	inex::engine::finalize			( );
}

void application::execute	( )
{
	inex::engine::execute			( );
	m_exit_code						= inex::engine::get_exit_code();
}