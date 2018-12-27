#ifndef OS_INCLUDE_H_INCLUDED
#	define OS_INCLUDE_H_INCLUDED

#   if	IE_PLATFORM_WINDOWS
#   	include	<inex/os_windows.h>
#   elif IE_PLATFORM_LINUX // #if IE_PLATFORM_WINDOWS
#       include <inex/os_linux.h>
#   else // #if IE_PLATFORM_WINDOWS
#   	error include your os_PLATFORMNAME.h here
#   endif // #if IE_PLATFORM_WINDOWS

#endif // #ifdef OS_INCLUDE_H_INCLUDED
