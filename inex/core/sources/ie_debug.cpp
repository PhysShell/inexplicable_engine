#include "stdafx.h"

#include "ie_debug.h"

#include <cxxabi.h>
#include <signal.h>
#include <execinfo.h>

namespace inex {
namespace core {
namespace debug {

using inex::core::log::Msg;

void 	dump_call_stack_trace ( )
{
#if IE_PLATFORM_LINUX
	pvoid trace				[ 16 ];
	pstr* messages 			= nullptr;
	s32 i, trace_size 		= 0;
	trace_size 				= backtrace( trace, 16 );
	messages 				= backtrace_symbols( trace, trace_size );

	// i = 2 cuz message[ 1 ] is the debug::fatal( .. )
    for ( s32 i = 2; i < trace_size && messages != nullptr; ++i )
    {
        pstr mangled_name 	= nullptr,
		offset_begin 		= nullptr,
		offset_end 			= nullptr;

        for ( pstr p = messages[ i ]; *p; ++p )
        {
			switch ( *p )
			{
				case '(': 	mangled_name 	= p; break;
				case '+': 	offset_begin 	= p; break;
				case ')':	offset_end		= p; goto dump;
			}
        }

dump						:
        if ( mangled_name && offset_begin && offset_end &&
            mangled_name < offset_begin )
        {
            *mangled_name++ = 0;
            *offset_begin++ = 0;
            *offset_end++ 	= 0;

            s32 status;
           	pstr demangled_string = abi::__cxa_demangle( mangled_name, 0, 0, &status );
			/*
			* I don't want to output external calls
			* If needed, output messages[ i ] after each for-iteration
			*/
			if ( status == 0 )
			{
				Msg				( "%s", demangled_string );
				free			( demangled_string );
			}
		}
	}
#endif // #if IE_PLATFORM_LINUX
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

pcstr	error2string ( u32 code )
{
	pcstr result					= 0;
	static string1024 desc_storage;

	//if(0==result)
	//{
#if IE_PLATFORM_WINDOWS
		FormatMessage( 	FORMAT_MESSAGE_FROM_SYSTEM,
						0,
						code,
						0,
						desc_storage,
						sizeof( desc_storage ) - 1,
						0
					);
		result						=	desc_storage;
	//}
#endif // #if IE_PLATFORM_WINDOWS
	return				 				result;

}

void	fatal ( pcstr 	file,
				u32 	line,
				pcstr 	func,
				pcstr 	expr,
				pcstr 	format,
				...
			)
{
    static	critical_section	crit_section	;
			scope_locker		lock			{ crit_section };

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
#if IE_PLATFORM_WINDOWS
        _vsnprintf
#else
        vsnprintf
#endif // #if IE_PLATFORM_WINDOWS
        ( buf, sizeof( buf ) - 1,format, mark ); buf[ sizeof( buf ) - 1] = 0;
        //strcat			( buf,"\n" );
        va_end				( mark );
        if( sz )
		{
			Msg 			( "Description:\t%s", buf );
		}
    }
	else
	{
        log::put_string		( "Description:\t<no description>\n" );
    }
	// destroy stuff before ?

	log::put_string			( "***\nStack Dump:\n***\n" );
	dump_call_stack_trace	( );
	exit            		( 1 );
}

} // namespace debug
} // names core
} // namespace inex
