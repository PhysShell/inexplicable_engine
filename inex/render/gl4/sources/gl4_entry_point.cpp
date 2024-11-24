#include "pch.h"
#include <inex/render/gl4/gl4_extensions.h>

// really temporary

#	ifdef CAST
#	   error please do not define CAST
#	endif  // #ifdef CAST

#	if INEX_PLATFORM_WINDOWS
#	   define CAST
#	    define GL_GET_PROCESS_ADDRESS	wglGetProcAddress
#	    define OPENGL_GET_PROC( type , function ) function = ( type )GL_GET_PROCESS_ADDRESS(  CAST #function ); \
                                                    ASSERT_D( function, "[opengl]\t: error getting '%s' address", #function ); \
                                                    inex::logging::put_string( "- [opengl][info]\t: loading \"" ); \
                                                    inex::logging::put_string( #type );		\
                                                    inex::logging::put_string( " ");		\
                                                    inex::logging::put_string( #function ); \
                                                    inex::logging::put_string("\"\n" )
#	elif INEX_PLATFORM_LINUX // #if INEX_PLATFORM_WINDOWS

#	  define OPENGL_GET_PROC( type , function ) function = ( type )glXGetProcAddress(  ( const GLubyte * ) #function ); \
                                                    ASSERT_D( function, "[opengl]\t: error getting '%s' address", #function ); \
                                                    inex::logging::put_string( "- [opengl][info]\t: loading \"" ); \
                                                    inex::logging::put_string( #type );		\
                                                    inex::logging::put_string( " ");		\
                                                    inex::logging::put_string( #function ); \
                                                    inex::logging::put_string("\"\n" )
#	endif // #if INEX_PLATFORM_WINDOWS


void	initialize_context_parameters ( )
{
# if INEX_PLATFORM_WINDOWS
	GLenum const params[ ] 	=
	{
		GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		GL_MAX_CUBE_MAP_TEXTURE_SIZE,
		GL_MAX_DRAW_BUFFERS,
		GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
		GL_MAX_TEXTURE_IMAGE_UNITS,
		GL_MAX_TEXTURE_SIZE,
		GL_MAX_VARYING_FLOATS,
		GL_MAX_VERTEX_ATTRIBS,
		GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		GL_MAX_VERTEX_UNIFORM_COMPONENTS,
		GL_MAX_VIEWPORT_DIMS,
		GL_STEREO
	};

	pcstr const names[ ] 	=
	{
		"GL_MAX_COMBINED_TE XTURE_IMAGE_UNITS",
		"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
		"GL_MAX_DRAW_BUFFERS",
		"GL_MAX_FRAGMENT_UNIFO RM_COMPONENTS",
		"GL_MAX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_TEXTURE_SIZE",
		"GL_MAX_VARYING_FLOATS ",
		"GL_MAX_VERTEX_ATTRIBS",
		"GL_MAX_VERTEX_TEXTURE_I MAGE_UNITS",
		"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
		"GL_MAX_VIEWPORT_DIMS",
		"GL_STEREO"
	};

	LOGGER				("* [render][info]\t: OpenGL context parameters:\n[\n");
	string256 msg;
	// integers - only works if the order is 0-10 integer return types
	for ( s32 i = 0; i < 10; ++i ) {
		s32 v 			= 0;
		glGetIntegerv 	( params[ i ], &v );
		LOGGER 			("\t%s %i", names[ i ], v );
	}

	inex::logging::put_string("]\n" );
#endif // # if INEX_PLATFORM_WINDOWS
}

void	inex::render::initialize	( )
{
    // Texture

#if !INEX_PLATFORM_LINUX
    OPENGL_GET_PROC( PFNGLACTIVETEXTUREPROC,        glActiveTexture );
#endif // #if !INEX_PLATFORM_LINUX
    
#if INEX_PLATFORM_WINDOWS
// VAO
    OPENGL_GET_PROC( PFNGLGENVERTEXARRAYSPROC,      glGenVertexArrays );
    OPENGL_GET_PROC( PFNGLGENVERTEXARRAYSPROC,      glGenVertexArrays );
    OPENGL_GET_PROC( PFNGLDELETEVERTEXARRAYSPROC,   glDeleteVertexArrays );
    OPENGL_GET_PROC( PFNGLBINDVERTEXARRAYPROC,      glBindVertexArray );

    // VBO
    OPENGL_GET_PROC( PFNGLGENBUFFERSPROC,     glGenBuffers );
    OPENGL_GET_PROC( PFNGLDELETEBUFFERSPROC,  glDeleteBuffers );
    OPENGL_GET_PROC( PFNGLBINDBUFFERPROC,     glBindBuffer );
    OPENGL_GET_PROC( PFNGLBUFFERDATAPROC,     glBufferData );
    OPENGL_GET_PROC( PFNGLBUFFERSUBDATAPROC,  glBufferSubData );
    OPENGL_GET_PROC( PFNGLMAPBUFFERPROC,      glMapBuffer );
    OPENGL_GET_PROC( PFNGLUNMAPBUFFERPROC,    glUnmapBuffer );

    // Shaders
    OPENGL_GET_PROC( PFNGLCREATEPROGRAMPROC,      glCreateProgram );
    OPENGL_GET_PROC( PFNGLDELETEPROGRAMPROC,      glDeleteProgram );
    OPENGL_GET_PROC( PFNGLLINKPROGRAMPROC,        glLinkProgram );
    OPENGL_GET_PROC( PFNGLVALIDATEPROGRAMPROC,    glValidateProgram );
    OPENGL_GET_PROC( PFNGLUSEPROGRAMPROC,         glUseProgram );
    OPENGL_GET_PROC( PFNGLGETPROGRAMIVPROC,       glGetProgramiv );
    OPENGL_GET_PROC( PFNGLGETPROGRAMINFOLOGPROC,  glGetProgramInfoLog );
    OPENGL_GET_PROC( PFNGLCREATESHADERPROC,       glCreateShader );
    OPENGL_GET_PROC( PFNGLDELETESHADERPROC,       glDeleteShader );
    OPENGL_GET_PROC( PFNGLSHADERSOURCEPROC,       glShaderSource );
    OPENGL_GET_PROC( PFNGLCOMPILESHADERPROC,      glCompileShader );
    OPENGL_GET_PROC( PFNGLATTACHSHADERPROC,       glAttachShader );
    OPENGL_GET_PROC( PFNGLDETACHSHADERPROC,       glDetachShader );
    OPENGL_GET_PROC( PFNGLGETSHADERIVPROC,        glGetShaderiv );
    OPENGL_GET_PROC( PFNGLGETSHADERINFOLOGPROC,   glGetShaderInfoLog );

    // Attributes
    OPENGL_GET_PROC( PFNGLGETATTRIBLOCATIONPROC,        glGetAttribLocation );
    OPENGL_GET_PROC( PFNGLVERTEXATTRIBPOINTERPROC,      glVertexAttribPointer );
    OPENGL_GET_PROC( PFNGLENABLEVERTEXATTRIBARRAYPROC,  glEnableVertexAttribArray );
    OPENGL_GET_PROC( PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray );

    // Uniforms
    OPENGL_GET_PROC( PFNGLGETUNIFORMLOCATIONPROC,   glGetUniformLocation );
    OPENGL_GET_PROC( PFNGLUNIFORMMATRIX3FVPROC,     glUniformMatrix3fv );
    OPENGL_GET_PROC( PFNGLUNIFORMMATRIX4FVPROC,     glUniformMatrix4fv );
    OPENGL_GET_PROC( PFNGLUNIFORM1FPROC,            glUniform1f );
    OPENGL_GET_PROC( PFNGLUNIFORM1IPROC,            glUniform1i );
    OPENGL_GET_PROC( PFNGLUNIFORM1FVPROC,           glUniform1fv );
    OPENGL_GET_PROC( PFNGLUNIFORM2FPROC,            glUniform2f );
    OPENGL_GET_PROC( PFNGLUNIFORM3FVPROC,           glUniform3fv );
    OPENGL_GET_PROC( PFNGLUNIFORM3FPROC,            glUniform3f );
    OPENGL_GET_PROC( PFNGLUNIFORM4FVPROC,           glUniform4fv );
#endif // INEX_PLATFORM_WINDOWS
	
    //OPENGL_GET_PROC( PFNGLDRAWARRAYSEXTPROC,        glDrawArraysExt );
    #undef											CAST

    initialize_context_parameters                   ( );
}

#ifndef _WIN32
typedef void* HMODULE ;
#endif /* not _WIN32 */

//HMODULE LibHandle = 0;
//bool isInit = false;
//
//void* glgGetProcAddress( char * procName )
//{
//#if INEX_PLATFORM_WINDOWS
//  return wglGetProcAddress(procName);
//#elif INEX_PLATFORM_LINUX
//  return ( void * )glXGetProcAddress( ( const GLubyte * ) procName );
//#endif
//}
//
//bool glgInit()
//{
//  if (isInit)
//    return false;
//#if INEX_PLATFORM_WINDOWS
//  // LibHandle = LoadLibrary("OpenGL32.dll");
//#elif INEX_PLATFORM_LINUX
//  //LibHandle = dlopen(NULL, RTLD_LAZY | RTLD_LOCAL);
//#endif
//
//  if (LibHandle)
//  {
//#ifndef _WIN32
//    //glXGetProcAddress = dlsym(LibHandle, "glXGetProcAddress");
//    if (!glXGetProcAddress)
//    {
//      //glXGetProcAddress = dlsym(LibHandle, "glXGetProcAddressARB");
//      if (!glXGetProcAddress)
//        return false;
//    }
//#endif /* not _WIN32 */
//    isInit = true;
//    return true;
//  }
//  else
//  {
//    ASSERT_D( 0, "NOT INIT" );
//  }
//}
//
//void glgDeinit()
//{
//  if (!isInit)
//    return;
//#ifndef _WIN32
//  dlclose(LibHandle);
//#endif /* not _WIN32 */
//}
