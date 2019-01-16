#include "stdafx.h"
#include "logger.h"
#include <inex/core/sources/ie_memory.h>

namespace inex {
namespace logging {

static string_path					log_file_name	= "engine.log";
static fs::writer*         			fwriter      	= nullptr;
static threading::critical_section	log_section		;


void 	Msg ( pcstr format, ... )
{

    threading::scope_locker crit_sect( log_section );
    if ( !fwriter )
	{
		return;
	}

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
        fwriter->w( msg );
	}

    return      			fwriter;
}

void	initialize ( bool no_log )
{
    if ( no_log )
	{
		printf		( "nolog\n" );
		return;
	}

    fwriter			= memory::ie_new< fs::file_writer >( log_file_name );

    //Msg( "* Created writer in LOG.cpp. Address: %p!", fwriter );
}

void 	finalize ( )
{
	//Msg( "* Attempting to finalize writer in LOG.cpp. Address: %p!", fwriter );
	//Msg( "* casted to file_writer in LOG.cpp. Address: %p!", ( fs::file_writer* )fwriter );
	if ( fwriter )
	{
		//Msg( "*		Pass file_writer to ie_delete." );
		//memory::dump_memory_contents( );
		memory::ie_delete( fwriter  );
	}
}

}// namespace logging
}// namespace inex
