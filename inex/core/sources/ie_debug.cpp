#include "pch.h"
#include "ie_debug.h"
#include "ie_memory.h"


namespace inex {
namespace debug {

using inex::logging::Msg;

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
    static	threading::critical_section	crit_section	;
			threading::scope_locker		lock			{ crit_section };

    Msg( "\nAssertion failed!\n"
		"File:\t\t\t%s", file );
    Msg( "Line:\t\t\t%d", line );
    Msg( "Method:\t\t\t%s", func );
    Msg( "Expression:\t\t%s", expr );

    if ( format )
	{
        va_list	mark;
        string2048 buf;
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
	dump_call_stack_trace	( );
	memory::dump_memory_contents( );
	exit            		( 1 );
}

} // namespace debug
} // namespace inex
