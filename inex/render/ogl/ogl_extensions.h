////////////////////////////////////////////////////////////////////////////
//	Created 	: 23.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////
#ifndef OGL_EXTENSIONS_H_INCLUDED
#   define OGL_EXTENSIONS_H_INCLUDED
#include <inex/render/api.h>

#	include <inex/3rd_patry/include/GL/glew.h>

// #define GL_GLEXT_PROTOTYPES
// #define GLX_GLXEXT_PROTOTYPES
// for GLintptr
#define GLX_GLXEXT_LEGACY
#include "../../3rd_patry/include/GL/glx.h"
#include "../../3rd_patry/include/GL/gl.h"
#include "../../3rd_patry/include/GL/glext.h"
//#include <GL/glext.h>
#if INEX_PLATFORM_WINDOWS
#   include <inex/3rd_patry/include/GL/wglext.h>
#endif // #if INEX_PLATFORM_WINDOWS

#include <inex/extensions.h>
#if INEX_PLATFORM_WINDOWS
#	define GL_GET_PROCESS_ADDRESS	wglGetProcAddress
#elif INEX_PLATFORM_LINUX // #if INEX_PLATFORM_WINDOWS
// can this be replaced by #define GL_GLEXT_PROTOTYPES>]?
#	define GL_GET_PROCESS_ADDRESS	glXGetProcAddress
// #elif define glfwGetProcAddress // #if INEX_PLATFORM_WINDOWS
#endif // #if INEX_PLATFORM_WINDOWS

#define OPENGL_GET_PROC( type , function ) function = ( type )GL_GET_PROCESS_ADDRESS((const GLubyte* ) #function ); \
											if ( NULL == function )			return 0; \
											inex::logging::put_string( "* [OPENGL] : loading " ); \
											inex::logging::put_string( #type );		\
											inex::logging::put_string( " ");		\
											inex::logging::put_string( #function ); \
											inex::logging::put_string("\n" );



namespace inex {
namespace ogl {
inline                  template < typename Type >
INEX_RENDER_API Type   get_procedure_address ( Type & , const GLubyte * name )
{
    printf ( "* [OPENGL] : loading (%s)%s", typeid(Type).name( ), name );
    return
#if INEX_PLATFORM_WINDOWS
            reinterpret_cast < Type> ( wglGetProcAddress( name ) );
#elif INEX_PLATFORM_LINUX
#   ifdef GLX_VERSION_1_4
            reinterpret_cast < Type > ( glXGetProcAddress( name ) );
#   else
            reinterpret_cast < Type > ( glXGetProcAddressARB( name ) );
#   endif
#endif
}
INEX_RENDER_API bool	init_extensions ( );
INEX_RENDER_API void    dump_user_specifications ( );

INEX_RENDER_API void    get_c ( );
}// namespace ogl
}// namespace inex

typedef void ( * PFNGLACTIVETEXTUREPROC ) ( GLenum texture );






/* Global extension */
// Texture
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
// VAO
extern PFNGLGENVERTEXARRAYSPROC    glGenVertexArrays;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC    glBindVertexArray;
// VBO
extern PFNGLGENBUFFERSPROC    glGenBuffers;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLBINDBUFFERPROC    glBindBuffer;
extern PFNGLBUFFERDATAPROC    glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
extern PFNGLMAPBUFFERPROC     glMapBuffer;
extern PFNGLUNMAPBUFFERPROC   glUnmapBuffer;
// Shaders
extern PFNGLCREATEPROGRAMPROC     glCreateProgram;
extern PFNGLDELETEPROGRAMPROC     glDeleteProgram;
extern PFNGLLINKPROGRAMPROC       glLinkProgram;
extern PFNGLVALIDATEPROGRAMPROC   glValidateProgram;
extern PFNGLUSEPROGRAMPROC        glUseProgram;
extern PFNGLGETPROGRAMIVPROC      glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLCREATESHADERPROC      glCreateShader;
extern PFNGLDELETESHADERPROC      glDeleteShader;
extern PFNGLSHADERSOURCEPROC      glShaderSource;
extern PFNGLCOMPILESHADERPROC     glCompileShader;
extern PFNGLATTACHSHADERPROC      glAttachShader;
extern PFNGLDETACHSHADERPROC      glDetachShader;
extern PFNGLGETSHADERIVPROC       glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC  glGetShaderInfoLog;
// Attributes
extern PFNGLGETATTRIBLOCATIONPROC        glGetAttribLocation;
extern PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
// Uniforms
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORMMATRIX3FVPROC   glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC   glUniformMatrix4fv;
extern PFNGLUNIFORM1IPROC          glUniform1i;
extern PFNGLUNIFORM1FVPROC         glUniform1fv;
extern PFNGLUNIFORM3FVPROC         glUniform3fv;
extern PFNGLUNIFORM4FVPROC         glUniform4fv;
#endif // #ifndef OGL_EXTENSIONS_H_INCLUDED
