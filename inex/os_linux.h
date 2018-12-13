#ifndef OS_LINUX_H_INCLUDED
#	define OS_LINUX_H_INCLUDED

#   if IE_PLATFORM_LINUX
#       include <sys/mman.h>
#       include <fcntl.h>
#       include <sys/stat.h>
#       include <unistd.h>
#       pragma message ( " os_linux.h included" )
#	endif // #if IE_PLATFORM_LINUX

#endif // #ifdef OS_LINUX_H_INCLUDED
