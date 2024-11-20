#include "pch.h"
#include "logger.h"
#include <inex/core/sources/ie_memory.h>
#include <inex/command_line.h>

namespace inex {
namespace logging {

static string_path					log_file_name	= "engine.log";
static memory::writer*         		fwriter			;
static threading::critical_section	log_section		;

void	preinitialize ( )
{
}

void	initialize ( bool no_log )
{
    if ( no_log )
	{
		printf		( "nolog\n" );
		return;
	}

    fwriter			= memory::ie_new< memory::file_writer >( log_file_name );
}

void 	finalize ( )
{
	if ( fwriter )
		memory::ie_delete( fwriter  );
}

void 	Msg ( pcstr format, ... )
{
    threading::scope_locker crit_sect( log_section );

    if ( !fwriter )
		return;

	va_list mark;
	string2048 buf;
	va_start			( mark, format );
	s32 sz			=
#if INEX_PLATFORM_WINDOWS
        _vsnprintf
#else
        vsnprintf
#endif // #if INEX_PLATFORM_WINDOWS
	( buf,sizeof( buf ) - 1, format, mark );
	buf[ sizeof( buf ) - 1 ] = 0;
	va_end				( mark );
	strcat				( buf, "\n" );
	if ( sz )
	{
		ASSERT_D( put_string( buf ), "Error occured while formating Msg (fwriter==0)\n" );
	}
}

bool	put_string ( pcstr msg )
{
    //threading::scope_locker crit_sect	( log_section );
	if ( fwriter )
	{
		fwriter->w 			( msg );
	}

    return      			fwriter;
}

bool 	check_verbosity ( pcstr initiator, verbosity verbosity )
{
	debug_log_disable_raii					debug_log_disable;
	
	return true;
}

}// namespace logging
}// namespace inex
