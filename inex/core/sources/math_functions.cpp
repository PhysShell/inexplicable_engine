#include "pch.h"
#include <inex/math_functions.h>


namespace inex {
namespace math {

void    multiple_sse ( float * const left, float * const right )
{
    logging::Msg( "!!!SSE MULTIPLE!!!");
	# if defined ( __GNUC__ )
    __asm__ volatile
    (
        "movups %[a], %%xmm0\n\t"
        "movups %[b], %%xmm1\n\t"
        "mulps %%xmm1, %%xmm0\n\t"
        "movups %%xmm0, %[a]\n\t"
        :
        : [ a ] "m" ( * left ), [ b ] "m" ( * right )
        : "%xmm0", "%xmm1"
    );
	# elif defined ( _MSC_VER ) && ! defined INEX_PLATFORM_WINDOWS_64 // #if defined ( __GNUC__ )
	// memory must be aligned by 128
	INEX_FORCE_ALIGNMENT( 16 ) float l				= * left;
	INEX_FORCE_ALIGNMENT( 16 ) float r				= * right;

__asm  {
		
		movups			xmm0 , DWORD PTR [ l ]
		movups			xmm1 , DWORD PTR [ r ]
		mulps			xmm0 , xmm1
		movups			DWORD PTR [ l ] , xmm0
}
		* left			= l;
	# else // #if defined ( __GNUC__ )
	#		pragma todo( "sse intrinsics for x64 msvc" )
	# endif // #if defined ( __GNUC__ )
}

void    multiple_pure ( float * const left, float * const right )
{
    logging::Msg( "!!!PURE MULTIPLE!!!");
    *left               *= * right;
}

} // namespace math
} // namespace inex
