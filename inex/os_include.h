#ifndef OS_INCLUDE_H_INCLUDED
#	define OS_INCLUDE_H_INCLUDED

#   if	IE_PLATFORM_WINDOWS
#   	include	<inex/os_windows.h>
#   elif IE_PLATFORM_LINUX // #if IE_PLATFORM_WINDOWS
#       include <inex/os_linux.h>
#   else // #if IE_PLATFORM_WINDOWS
#   	error include your os_PLATFORMNAME.h here
#   endif // #if IE_PLATFORM_WINDOWS

#   pragma message( "Here are all platform-independent stuff here" )
// thus, the file below contains cross-platform API
// ( the non-portable code and data are in corresponding files )
#   include <inex/core/sources/fs_read_write.h>

#endif // #ifdef OS_INCLUDE_H_INCLUDED
