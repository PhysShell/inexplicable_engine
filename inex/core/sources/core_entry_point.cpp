#include "pch.h"

#include <inex/core/core.h>
#include <inex/command_line.h>
#include "build_extensions.h"
#include <inex/threading_functions.h>
#include <inex/math_functions.h>
#include <inex/strings_functions.h>
#include "processor_info.h"
#include "ie_trims.h"
#include "ie_memory.h"
#include "memory_general_allocator.h"
#include "encryption.h"

namespace inex {
	namespace console {
		void	initialize ( )
		{
#if INEX_PLATFORM_WINDOWS
			AllocConsole						( );
			freopen_s							( ( FILE ** )	stdout, "CONOUT$",	"w", stdout );
			freopen_s							( ( FILE ** )	stdin,	"CONIN$",	"r", stdin );
#endif // INEX_PLATFORM_WINDOWS
		}
	} // namespace console
	namespace fpu {
		void    initialize  ( );
	} // namespace fpu

namespace core {

static bool	s_initialized				= false;
static inex::core::engine * s_engine	= nullptr;

static u32		s_processor_features        { };

void inex::core::preinitialize		( core::engine *								engine, 
									  pcstr const									command_line, 
									  bool const									command_line_contains_application, 
									  pcstr	const									application,
									  pcstr	const									build_date
									)
{
	s_engine				= engine;
	ASSERT_D				( !s_initialized, "you cannot preinitialize core when it has been initialized already" );

	using namespace			debug;
	console::initialize		( );
	command_line::initialize( command_line );

	//debug::initialize		( s_engine );

	//set_application_name	( application );

	//platform::preinitialize	( );
	//threading::preinitialize( );
	memory::preinitialize	( );
	logging::preinitialize	( );
	build::preinitialize	( build_date );
}


void	bench ( u32* value_1, u32  size )
{
	Sleep( 1000 );
	for ( u32 i = 0; i < size; ++i )
	{
		value_1[ i ]			+= i;
	}

	return ;
}

bool inex::core::initialized ( )
{
	return					s_initialized;
}

static void   initialize_logging ( flags8 const log_file_usage )
{
	using namespace inex;
	// calculate verbosity from command line
}

void inex::core::initialize			(
		pcstr const debug_thread_id,
		log_file_usage const log_file_usage,
		debug_initialization const debug_initialization
	)
{
	ASSERT_D				( !s_initialized, "you cannot initialize core when it has been initialized already" );
	// for language-dependent strings
	setlocale				( LC_CTYPE, "" );

	logging::initialize		( );

	build::initialize		( s_engine );
    fpu::initialize         ( );
    encryption::initialize	( );

    string128       temp	{ };
    if ( command_line::get_value_by_key( "-data", temp ) )	fs::initialize	( temp );
	else													fs::initialize	( "gamedata/" );

    logging::Msg( "* [cpu][info]\t: cycle per second %ld hz", threading::clock_cycle_per_second( ) );
	logging::Msg( "* [cpu][info]\t: L1 Cache line size %d bits\n", threading::cache_line_size( ) );

	s_initialized			= true;
}

void	finalize ( )
{
	ASSERT_D				( s_initialized, "core library hasn't been initialized" );

    logging::Msg			( "- [core]\t: destroying" );
    fs::finalize			( );
    memory::finalize		( );
    logging::finalize		( );

	s_initialized			= false;
}

} // names core

namespace fpu {

/***
*
* void initialize ( )
*
* Entry:
*
*
*
* Exit:
*
*
*
****************************************************/
void    initialize ( )
{
    math::MATH g_CM;
    g_CM.matrix_multiple    = math::multiple_pure;

	core::s_processor_features    = threading::aquire_processor_information		( );

	LOGGER( "initializing fpu..." );
    // if ( command_line::check_key( "-pure_math" ) )
    if ( !command_line::check_key( "-no_sse" ) && core::s_processor_features & 1 )
    {
        g_CM.matrix_multiple = math::multiple_sse;
    }

    float	f1              = 1.0f,
            f2              = 0.1f;

    float* pf1              = memory::ie_allocate< float >( sizeof ( float ) );
    float* pf2              = memory::ie_allocate< float >( sizeof ( float ) );
    *pf1    = *pf2          = .1f;
    g_CM.matrix_multiple( pf1, pf2 );


    LOGGER ( "pf1=%f, pf2=%f", *pf1, *pf2 );
	memory::ie_delete       ( pf1 );
    memory::ie_delete       ( pf2 );

	ASSERT_S            ( math::fdEPS != 0.f );
	logging::Msg        ( "Epsilon is: '%0.*f'", 8, math::fdEPS );
}
} // namespace fpu

} // namespace inex
