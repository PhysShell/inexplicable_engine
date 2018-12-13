#include "stdafx.h"

#include <inex/engine/ie_engine.h>
#include "build_id_computer.h"
#include <inex/core/ie_core.h>
  
namespace inex {
namespace engine {

engine::engine (s32 argc, pstr* argv ) :
	m_exit_code		{ 0 }
    {
        inex::core::initialize( argc, argv );
        //if(strstr(inex::core::get_params(), "-engine"))
       inex::core::log::Msg( "Initializing Engine...\n" );
    }

engine::~engine ( )
{
    inex::core::finalize( );
}

} // namespace inex
} // namespace engine
