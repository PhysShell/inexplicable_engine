#include "stdafx.h"
#include <inex/engine/ie_engine.h>

namespace inex {
namespace platform {

s32		engine_entry_point (	pstr		command_line_string		);


s32		engine_entry_point ( pstr command_line_string )
{
	core::initialize	( 0, command_line_string );
	core::log::Msg		( "Initializing Engine...\n" );
	engine::engine		en;
	core::finalize		( );
	return				en.get_exit_code( );
}

} // namespace platform
} // namespace inex

int main( int argc, pstr* argv )
{
	{
		inex::platform::engine_entry_point( 0 );
	}

	IE_DEBUG_WAIT;
   	return 0;
}