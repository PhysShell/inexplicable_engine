#ifndef OS_INCLUDE_H_INCLUDED
#	define OS_INCLUDE_H_INCLUDED

#   if	INEX_PLATFORM_WINDOWS
#   	include	<inex/os_windows.h>
#   elif INEX_PLATFORM_LINUX // #if INEX_PLATFORM_WINDOWS
#       include <inex/os_linux.h>
#   else // #if INEX_PLATFORM_WINDOWS
#   	error include your os_PLATFORMNAME.h here
#   endif // #if INEX_PLATFORM_WINDOWS

#endif // #ifdef OS_INCLUDE_H_INCLUDED
