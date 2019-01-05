////////////////////////////////////////////////////////////////////////////
//	Created 	: 31.12.2018
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef RENDER_INCLUDE_H_INCLUDED
#	define RENDER_INCLUDE_H_INCLUDED

#	define GLFW_STATIC
#	define GLEW_STATIC
// in freeglut_std.h, it says lib to be named "freeglut.lib" for static linkage, too
#	define FREEGLUT_STATIC
#	pragma comment( lib, "freeglut.lib" )
#	pragma comment( lib, "glew32_static.lib" )
#	pragma comment( lib, "glfw3_static.lib" )

#	include <inex/3rd_patry/include/GL/glew.h>
#	include <inex/3rd_patry/include/GLFW/glfw3.h>
#	include <inex/3rd_patry/include/GL/freeglut.h>

#endif // #ifndef RENDER_INCLUDE_H_INCLUDED
