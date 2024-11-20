#include "pch.h"
#include "ie_debug.h"
#include "ie_memory.h"
#include <inex/core/engine.h>
#include <inex/threading_functions.h>
#include <inex/core/sources/log_callback.h>
#include <stdlib.h>

static inex::core::debug::engine *      s_core_engine	            = NULL;
static inex::debug::log_callback		s_log_callback              = NULL;
static inex::threading::atomic32_value_type s_log_disable_counter   = 0;

inex::debug::log_callback	inex::debug::get_log_callback	( )
{
	return									s_log_disable_counter ? nullptr : s_log_callback;
}

inex::debug::log_callback	inex::debug::set_log_callback	( log_callback const & callback )
{
	log_callback const previous_callback	=	s_log_callback;
	s_log_callback							=	callback;
	return									previous_callback;
}

void	inex::debug::disable_log_callback	( )
{
	inex::threading::interlocked_increment					( &s_log_disable_counter );
}

void	inex::debug::enable_log_callback	( )
{
    inex::threading::interlocked_decrement					( &s_log_disable_counter );
}

namespace inex {
namespace core {
namespace debug {

void    initialize ( inex::core::debug::engine * engine  )
{
}

void    postinitialize ( )
{
}

void    finalize ( )
{

}

using logging::Msg;

void    set_primary_clipboard_contents ( pcstr text )
{

}

void	aquire_macros ( pcstr 	file,
						u32 	line,
						pcstr 	func,
						pcstr 	expr )
{
	Msg( "File: %s", file );
    Msg( "Line: %d", line );
    Msg( "Method: %s", func );
}

void	fatal ( pcstr 	file,
				u32 	line,
				pcstr 	func,
				pcstr 	expr,
				pcstr 	format,
				...
			)
{
    //static	threading::critical_section	crit_section	;
	//		threading::scope_locker		lock			{ crit_section };

    Msg( "\nAssertion failed!\n"
		"File:\t\t\t%s", file );
    Msg( "Line:\t\t\t%d", line );
    Msg( "Method:\t\t\t%s", func );
    Msg( "Expression:\t\t%s", expr );

    if ( format )
	{
        string2048 buf;
        va_list	mark;

        va_start			( mark, format );
        int sz			=
#if INEX_PLATFORM_WINDOWS
        _vsnprintf
#else
        vsnprintf
#endif // #if INEX_PLATFORM_WINDOWS
        ( buf, sizeof( buf ) - 1,format, mark ); buf[ sizeof( buf ) - 1] = 0;
        //strcat			( buf,"\n" );
        va_end				( mark );
        if( sz ) {
			Msg 			( "Description:\t%s", buf );
		}
    } else
	{
        logging::put_string		( "Description:\t<no description>\n" );
    }

	logging::put_string			( "***\nStack Dump:\n***\n" );
	dump_call_stack_trace	    ( );
	memory::dump_memory_contents( );

	exit            		( 1 );
}

} // namespace debug
} // namespace core
} // namespace inex
