#include "stdafx.h"
#include "logger.h"
#include <inex/core/sources/ie_memory.h>

namespace inex {
namespace core {
namespace log {

static string_path          log_file_name	= "engine.log";
static fs::writer*         	fwriter      	= nullptr;
static critical_section		log_section;

void 	Msg ( pcstr format, ... )
{
    scope_locker crit_sect( log_section );
    if ( !fwriter )
	{
		return;
	}

	va_list mark;
	string2048 buf;
	va_start			( mark, format );
	s32 sz			=
#if IE_PLATFORM_WINDOWS
        _vsnprintf
#else
        vsnprintf
#endif // #if IE_PLATFORM_WINDOWS
	( buf,sizeof( buf ) - 1, format, mark );
	buf[ sizeof( buf ) - 1 ] = 0;
	va_end				( mark );
	strcat				( buf, "\n" );
	if ( sz )
	{
		if ( !put_string( buf ) )
		{
			printf( "Error occured while formating Msg (fwriter==0)\n" );
		}
	}
}

bool	put_string ( pcstr msg )
{
    scope_locker crit_sect	( log_section );
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

}// namespace log
}// namespace core
}// namespace inex
