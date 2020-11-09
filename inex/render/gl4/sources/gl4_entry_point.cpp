#include "pch.h"
#include <inex/render/gl4/gl4_extensions.h>

// really temporary

#	ifdef CAST
#	   error please do not define CAST
#	endif  // #ifdef CAST

#	if INEX_PLATFORM_WINDOWS
#	   define CAST                            
#		define GL_GET_PROCESS_ADDRESS	wglGetProcAddress
#	elif INEX_PLATFORM_LINUX // #if INEX_PLATFORM_WINDOWS
// can this be replaced by #define GL_GLEXT_PROTOTYPES>]?
#	   define CAST                     ( const GLubyte * )
#		define GL_GET_PROCESS_ADDRESS	glXGetProcAddress
// #elif define glfwGetProcAddress // #if INEX_PLATFORM_WINDOWS
#	endif // #if INEX_PLATFORM_WINDOWS

#	define OPENGL_GET_PROC( type , function ) function = ( type )GL_GET_PROCESS_ADDRESS(  CAST #function ); \
												ASSERT_D( function, "[opengl]\t: error getting '%s' address", #function ); \
												inex::logging::put_string( "- [opengl][info]\t: loading \"" ); \
												inex::logging::put_string( #type );		\
												inex::logging::put_string( " ");		\
												inex::logging::put_string( #function ); \
												inex::logging::put_string("\"\n" )

bool	inex::render::initialize	( )
{
     // Texture
	OPENGL_GET_PROC( PFNGLACTIVETEXTUREPROC,        glActiveTexture );

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
	//OPENGL_CHECK_FOR_ERRORS();
    #undef											CAST
	return											true;
}