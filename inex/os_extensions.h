#ifndef OS_EXTENSIONS_H_INCLUDED
#	define OS_EXTENSIONS_H_INCLUDED

#include <inex/macro_platform.h>

#include <inex/os_include.h>

#if IE_PLATFORM_WINDOWS
#	include <inex/types_win.h>
#	define IE_MAX_PATH	MAX_PATH
#else // #if IE_PLATFORM_WINDOWS
#	pragma message( "Default MAX_PATH used!!" )
#	define IE_MAX_PATH	260
//#	error ( "no max path detected" )
#endif // #if IE_PLATFORM_WINDOWS

#include <inex/types.h>



#endif // #ifdef OS_EXTENSIONS_H_INCLUDED
