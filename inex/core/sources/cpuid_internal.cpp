#include "stdafx.h"
#include "cpuid_internal.h"


#   if defined ( _MSC_VER )
#       include <intrin.h>
//#     define cpuid( info, x )    __cpuidex( info, x, 0 )
#   elif defined ( __MINGW32_VERSION ) || defined ( __GNUC__ ) // if defined ( _MSC_VER )
//  GCC Intrinsics
#       include <cpuid.h>
#   else
#       error please specify your compiler here
#   endif // #if defined ( _MSC_VER )

namespace inex {
namespace threading {
namespace detail {
#if defined ( _MSC_VER )
void	cpuid_fill ( s32 registers[ 4 ], s32 eax_contents )
{
	__cpuidex( registers, eax_contents, 0 );
}
void	cpuid_platform ( s32 registers[ 4 ], s32 eax_contents )
{
#pragma message lsfsfslfl
	__cpuidex( registers, eax_contents, 0 );
}
#elif defined ( __MINGW32_VERSION ) || defined ( __GNUC__ ) // #if defined ( _MSC_VER )
void	cpuid_platform ( s32 registers[ 4 ], s32 eax_contents )
{
    __cpuid_count( eax_contents, 0, registers[ 0 ], registers[ 1 ], registers[ 2 ], registers[ 3 ] );
}
void    cpuid_fill     ( s32 registers[ 4 ], s32 eax_contents )
{
    __cpuid_count( eax_contents, 0, registers[ 0 ], registers[ 1 ], registers[ 2 ], registers[ 3 ] );

//    u32 eax, ebx, ecx, edx;
//    asm volatile
//    (
//        "movl current_register, %%eax\n\t"
//        "cpuid\n\t"
//        : "=a"( eax ),"=b"( ebx ),"=c"( ecx ),"=d"( edx )
//    );
//
//    * registers         = eax;
//    * ( registers + 1 ) = ebx;
//    * ( registers + 2 ) = ecx;
//    * ( registers + 3 ) = edx;
}
#else
#	error please specify your compiler name here
#endif // #if defined ( _MSC_VER )
} // namespace detail
} // namespace threading
} // namespace inex
