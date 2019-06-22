#include "stdafx.h"
#include <inex/math_functions.h>


namespace inex {
namespace math {

void    multiple_sse ( float * const left, float * const right )
{
    logging::Msg( "!!!SSE MULTIPLE!!!");
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
}

void    multiple_pure ( float * const left, float * const right )
{
    logging::Msg( "!!!PURE MULTIPLE!!!");
}

} // namespace math
} // namespace inex
