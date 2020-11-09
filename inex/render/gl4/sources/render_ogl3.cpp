// render_gl3.cpp : Defines the exported functions for the DLL application.
//

#include "pch.h"
#include <inex/render/common/sources/hw_wrapper.h>
namespace inex {
namespace render {
// need it till cause i otherwise linker gives a warning which I don't want
INEX_RENDER_OGL4_API void dummy( )	{ };
}
}