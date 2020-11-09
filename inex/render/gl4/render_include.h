////////////////////////////////////////////////////////////////////////////
//	Created 	: 31.12.2018
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////
#ifndef RENDER_INCLUDE_H_INCLUDED
#	define RENDER_INCLUDE_H_INCLUDED

#   include <inex/os_include.h>
#	include <inex/render/ogl/ogl_extensions.h>
#	define GLFW_STATIC
// #	define GLEW_STATIC
//  in freeglut_std.h, it says lib to be named "freeglut.lib" for static linkage, too
// #	define FREEGLUT_STATIC

// #	include <inex/3rd_patry/include/GL/glew.h>
#	include <inex/3rd_patry/include/GLFW/glfw3.h>
// #	include <inex/3rd_patry/include/GL/freeglut.h>

#   if _WIN32
// #	    pragma comment( lib, "freeglut.lib" )
// #	    pragma comment( lib, "glew32_static.lib" )
// link 4098 warning means the library has different runtime from msvcrt lib
// most of the time, this happens when using compiled middleware
#	    pragma comment( lib, "glfw3_static.lib" )
#   endif // #   if IE_PLATFORM_WINDOWS

#endif // #ifndef RENDER_INCLUDE_H_INCLUDED
