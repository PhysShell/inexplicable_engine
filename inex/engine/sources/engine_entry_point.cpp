#include "pch.h"
#include <inex/engine/api.h>
#include "engine_memory.h"
#include "engine_world.h"
#include <inex/core/sources/memory_general_allocator.h>
//#include <inex/linkage_helper.h>

//#ifndef STATIC_LIBRARIES
//	DECLARE_LINKAGE_ID(engine_entry_point)
//#endif // #ifndef STATIC_LIBRARIES

typedef inex::memory::general_allocator	doug_lea_allocator_type;
doug_lea_allocator_type							inex::engine::g_allocator;

//static inex::uninitialized_reference<inex::engine::engine_world>	s_world;
static inex::engine::engine_world		*		s_world;
void inex::engine::preinitialize				( pcstr command_line, pcstr application, pcstr build_date )
{
	//INEX_CONSTRUCT_REFERENCE		( s_world, engine_world )	( command_line, application, build_date );
	s_world							= new inex::engine::engine_world( command_line, application, build_date );
}

void inex::engine::initialize		( inex::engine_user::module_proxy* module_proxy )
{
	s_world->setup_engine_user		( module_proxy );
	s_world->initialize				( );
}

void inex::engine::finalize						( )
{
	//INEX_DESTROY_REFERENCE			( s_world );
	delete								s_world;
}

void inex::engine::execute						( )
{
	s_world->run					( );
}

bool inex::engine::command_line_editor			( )
{
	return							0;//s_world->command_line_editor( );
}

bool inex::engine::command_line_no_splash_screen( )
{
	return							s_world->command_line_no_splash_screen( );
}

int inex::engine::get_exit_code					( )
{
	return s_world->get_exit_code	( );
}
