#include "stdafx.h"

#include "ie_debug.h"
#include "ie_memory.h"
#include <inex/threading_functions.h>

#if INEX_PLATFORM_LINUX

#   include <cxxabi.h>
#   include <signal.h>
#   include <execinfo.h>
#   include <chrono>

#elif  !defined (__MINGW32_VERSION ) && ( INEX_PLATFORM_WINDOWS_32 ) ^ ( INEX_PLATFORM_WINDOWS_64 )
#	pragma warning( push )
#	pragma warning( disable : 4820 )
#	pragma warning( disable : 4365 )
#	pragma warning( disable : 4191 )
#   include "RpcExStackTraceEngine.h"
#	pragma warning( pop )
#endif // #if INEX_PLATFORM_LINUX

namespace inex {
namespace debug {

using inex::logging::Msg;

#if INEX_PLATFORM_WINDOWS
float	benchmark ( void ( *function_pointer ( ) ) )
{
	LARGE_INTEGER			frequency, start, stop;
	s32						thread_priority;
	QueryPerformanceCounter	( &frequency );
	if ( 0 == frequency.QuadPart)
	{
		return				0.f;
	}

	thread_priority			= GetThreadPriority( GetCurrentThread( ) );
	if ( THREAD_PRIORITY_ERROR_RETURN == thread_priority )
	{
		return				0.f;
	}

	SetThreadPriority		( GetCurrentThread( ), THREAD_PRIORITY_TIME_CRITICAL );
	QueryPerformanceCounter	( &start );
	( *function_pointer )	( );
	QueryPerformanceCounter	( &stop );
	SetThreadPriority		( GetCurrentThread( ), thread_priority );

	return	( float )( stop.QuadPart - start.QuadPart ) / ( float )frequency.QuadPart;
}
#endif // #if INEX_PLATFORM_WINDOWS

void 	dump_call_stack_trace ( )
{

#if INEX_PLATFORM_LINUX
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
#elif !defined (__MINGW32_VERSION ) && ( INEX_PLATFORM_WINDOWS_32 ) ^ ( INEX_PLATFORM_WINDOWS_64 ) // #if INEX_PLATFORM_LINUX
		RpcExStackTraceEngine	call_stack;
		call_stack.Initialize	( );
		if ( RpcExStackTraceEngine::InitializationState::IS_Done == call_stack.GetInitializationState( ) )
			;//inex::core::logging::Msg ( "Call Stack Engine Initialized..." );
		string2048				buf;
		if ( S_OK == call_stack.WalkStack ( buf, sizeof( buf ), 8u ) )
			logging::Msg( "%s", buf );
		else
			logging::Msg( "!Unable to get current call stack trace." );
#else // #if INEX_PLATFORM_LINUX
        logging::Msg( "[Error]: callstack-aquiring mechanism not supported." );
#endif // #if INEX_PLATFORM_LINUX
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
#if INEX_PLATFORM_WINDOWS
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
#endif // #if INEX_PLATFORM_WINDOWS
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
        if( sz )
		{
			Msg 			( "Description:\t%s", buf );
		}
    }
	else
	{
        logging::put_string		( "Description:\t<no description>\n" );
    }
	// destroy stuff before ?
	logging::put_string			( "***\nStack Dump:\n***\n" );
	dump_call_stack_trace	( );
	memory::dump_memory_contents( );
	#pragma todo ( "should memory release all its contents or just leave it to os?")
	exit            		( 1 );
}

} // namespace debug
} // namespace inex
