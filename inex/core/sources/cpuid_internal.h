#ifndef CPUID_INTERNAL_H_INCLUDED
#	define CPUID_INTERNAL_H_INCLUDED

#   if IE_PLATFORM_WINDOWS
#       ifndef IE_PURE_GNUC
#           include <intrin.h>
#           define cpuid( info, x )    __cpuidex( info, x, 0 )
#       endif // #ifdef IE_PURE_GNUC
#   elif IE_PLATFORM_LINUX // #ifdef IE_PLATFORM_WINDOWS
//  GCC Intrinsics
#       include <cpuid.h>
void	cpuid ( int info[ 4 ], int InfoType )
{
    __cpuid_count( InfoType, 0, info[ 0 ], info[ 1 ], info[ 2 ], info[ 3 ] );
}
#   endif // #if IE_PLATFORM_WINDOWS

#endif // #ifndef CPUID_INTERNAL_H_INCLUDED
