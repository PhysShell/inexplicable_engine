#ifndef OS_EXTENSIONS_H_INCLUDED
#	define OS_EXTENSIONS_H_INCLUDED

#	include <inex/macro_platform.h>
#	include <inex/types.h>

#   if ! INEX_PLATFORM_WINDOWS
#       define HWND     pvoid
#   endif // #if ! INEX_PLATFORM_WINDOWS

#endif // #ifdef OS_EXTENSIONS_H_INCLUDED
