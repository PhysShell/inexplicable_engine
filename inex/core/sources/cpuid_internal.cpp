#include "pch.h"
#include "cpuid_internal.h"



#if defined ( _MSC_VER )
#   include <intrin.h>
#elif defined ( __MINGW32_VERSION ) || defined ( __GNUC__ ) // if defined ( _MSC_VER )
#   include <cpuid.h>
#else // if defined ( _MSC_VER )
#    error please specify your compiler intrinsics here
#endif // #if defined ( _MSC_VER )

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
	__cpuidex( registers, eax_contents, 0 );
}
#elif defined ( __MINGW32_VERSION ) || defined ( __GNUC__ ) // #if defined ( _MSC_VER )
void	cpuid_platform ( s32 registers[ 4 ], s32 eax_contents )
{
    __cpuid_count( eax_contents, 0, registers[ 0 ], registers[ 1 ], registers[ 2 ], registers[ 3 ] );
}

void    cpuid_fill     ( s32 registers[ 4 ], s32 eax_contents )
{
    //__cpuid_count( eax_contents, 0, registers[ 0 ], registers[ 1 ], registers[ 2 ], registers[ 3 ] );

   u32 eax, ebx, ecx, edx;
   asm volatile
   (
        "movl %[current_register], %%eax\n\t"
        "cpuid\n\t"
        : [ current_register ]  "+r" ( eax_contents ),
                                "=a"( eax ),
                                "=b"( ebx ),
                                "=c"( ecx ),
                                "=d"( edx )
   );

   * registers         = eax;
   * ( registers + 1 ) = ebx;
   * ( registers + 2 ) = ecx;
   * ( registers + 3 ) = edx;
}
#else
#	error please specify your compiler intrinsics
#endif // #if defined ( _MSC_VER )
} // namespace detail
} // namespace threading
} // namespace inex
