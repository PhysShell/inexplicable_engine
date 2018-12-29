#include "stdafx.h"
#include <inex/engine/ie_engine.h>
#include <inex/core/ie_core.h>

namespace inex {
namespace platform {

s32		engine_entry_point (	pstr		command_line_string		);


s32		engine_entry_point ( pstr command_line_string )
{
	core::initialize	( 0, 0 );
	core::log::Msg		( "Initializing Engine...\n" );
	engine::engine		en;
	core::finalize		( );
	return				en.get_exit_code( );
}

} // namespace platform
} // namespace inex


// there's some msvc bullshit which doesn't allow me to
// use wmain as entry point for win x86, so use linux version here
int main( int argc, pstr* argv )
{
	{
		inex::platform::engine_entry_point( 0 );
	}

	IE_DEBUG_WAIT;
   	return 0;
}