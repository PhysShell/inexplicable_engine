#include "pch.h"
#include "logger.h"
#include <inex/core/sources/ie_memory.h>
#include <inex/command_line.h>

namespace inex {
namespace logging {

static logging_to_enum				dest = logging_to_enum::file;
static string_path					log_file_name	= "engine.log";
static memory::writer*         		fwriter			;
//static threading::critical_section	log_section		;

// logging/sources/helper.cpp: static void fill_log_string

void	preinitialize ( )
{
	if ( command_line::check_key( "-log_to_stdout" ) )
        dest		= logging_to_enum::terminal;
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

void	set_output_destination	( logging_to_enum destination )
{
	dest			= destination;
}

void 	Msg ( pcstr format, ... )
{
	debug_log_disable_raii	debug_log_disable;
    //threading::scope_locker crit_sect( log_section );

	if ( dest == logging_to_enum::suspend_logging )
		return;

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
	switch ( dest )
	{
		case logging_to_enum::file :			if ( fwriter ) fwriter->w ( msg ); break;
		case logging_to_enum::terminal:			printf( "%s", msg ); break;
		case logging_to_enum::std_error_out: 
		default:								UNREACHABLE_CODE( );
	}

    return      			fwriter;
}

bool 	check_verbosity ( pcstr initiator, verbosity verbosity )
{
	debug_log_disable_raii					debug_log_disable;
	
	/*
	path_parts								path(initiator);
	
	int const allowed_verbosity			=	get_tree_verbosity( &path );
	if ( verbosity > allowed_verbosity )
		return								false;
	*/
	
	return true;
}

}// namespace logging
}// namespace inex
