#include "stdafx.h"
#include <inex/engine/ie_engine.h>
#include <inex/os_include.h>
#include <inex/core/ie_core.h>

namespace inex {
namespace platform {

s32		engine_entry_point (	HINSTANCE	hInst,
								HINSTANCE	hPreInst,
								pstr		lpCmdLine,
								s32			nCmdShow 
							);

s32		engine_entry_point ( HINSTANCE inst, HINSTANCE pinst, pstr cmdln, s32 cmdshow )
{
	core::initialize	( 0, 0 );
	logging::Msg		( "Initializing Engine...\n" );
	engine::engine		en;
	core::finalize		( );
	return				en.get_exit_code( );
}

} // namespace platform
} // namespace inex

s32 WINAPI	wmain (	HINSTANCE	hInst,
					HINSTANCE	hPreInst,
					pstr		lpCmdLine,
					s32			nCmdShow )
{
	inex::platform::engine_entry_point	( hInst, hPreInst, lpCmdLine, nCmdShow );

	IE_DEBUG_WAIT;
	return					0;
}


