#include "stdafx.h"
#include <inex/engine/ie_engine.h>
#include <inex/os_include.h>
#include <inex/core/ie_core.h>
#include <inex/render/ogl/render_include.h>
#include <inex/render/ogl/render_include.h>
#include <inex/sound/sound.h>
#include <inex/sound/sources/sound_object.h>
#include <inex/render/core/device.h>

namespace inex {
namespace platform {

s32		engine_entry_point (	HINSTANCE	hInst,
								HINSTANCE	hPreInst,
								pstr		lpCmdLine,
								s32			nCmdShow 
							);

s32		engine_entry_point ( HINSTANCE inst, HINSTANCE pinst, pstr cmdln, s32 cmdshow )
{
	string128			buffer;
	strcpy				( buffer, GetCommandLineA( ) );
	core::initialize	( buffer );
	


	ASSERT_S            ( math::fdEPS != 0.f );
	logging::Msg        ( "Epsilon is: '%0.*f'", 8, math::fdEPS );

	sound::sound_device sound;
	sound.initialize    ( );
	sound::sound_object snd{ 1.0f, 1.0f, 1.0f };
	snd.open            ( "gamedata/sound1.wav" );
	
	sound::sound_object snd2;
	snd2.open           ( "gamedata/motor_a8.wav", 1 );
	snd2.play           ( );
	snd.play            ( );

    ogl::device         device;
// init proc
    device.initialize   ( );
// startup proc
    device.create       ( );


// main cycle
    device.run          ( );

// destroying
    sound.finalize      ( );
    device.destroy      ( );
    core::finalize      ( );

	core::finalize		( );
	return				0;
}

} // namespace platform
} // namespace inex

int 	wmain (	HINSTANCE	hInst,
					HINSTANCE	hPreInst,
					LPSTR		lpCmdLine,
					int			nCmdShow )
{
	inex::platform::engine_entry_point	( hInst, hPreInst, lpCmdLine, nCmdShow );

	INEX_DEBUG_WAIT;
	return					0;
}

