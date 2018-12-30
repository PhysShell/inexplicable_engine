#ifndef CPUID_INTERNAL_H_INCLUDED
#	define CPUID_INTERNAL_H_INCLUDED

#   if INEX_PLATFORM_WINDOWS
#       ifndef __GNUC__
#           include <intrin.h>
#           define cpuid( info, x )    __cpuidex( info, x, 0 )
#       endif // #ifdef INEX_PURE_GNUC
#   elif INEX_PLATFORM_LINUX // #ifdef INEX_PLATFORM_WINDOWS
//  GCC Intrinsics
#       include <cpuid.h>
void	cpuid ( int info[ 4 ], int InfoType )
{
    __cpuid_count( InfoType, 0, info[ 0 ], info[ 1 ], info[ 2 ], info[ 3 ] );
}
#   endif // #if INEX_PLATFORM_WINDOWS

#endif // #ifndef CPUID_INTERNAL_H_INCLUDED
