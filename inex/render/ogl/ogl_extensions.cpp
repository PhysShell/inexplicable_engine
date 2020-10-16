#include "pch.h"
#include "ogl_extensions.h"

namespace inex {
namespace ogl {

bool	init_extensions ( )
{
    // Texture
    // glActiveTexture = get_procedure_address<PFNGLACTIVETEXTUREARBPROC>( glActiveTexture, ( const GLubyte* )"glActiveTexturexARB" );
    // VERIFY( glActiveTexture );
    // glActiveTexture = ( PFNGLACTIVETEXTUREPROC )glXGetProcAddress( ( const GLubyte * )"glActiveTextureARB" );
    // glGenVertexArrays = ( PFNGLGENVERTEXARRAYSPROC )glXGetProcAddress( ( const GLubyte * )"glGenVertexArray" );
    // get_procedure_address< PFNGLGENVERTEXARRAYSPROC>( glGenVertexArrays, (const GLubyte*)"glGenVertexArrays" );

    // VAO
    OPENGL_GET_PROC( PFNGLACTIVETEXTUREPROC,        glActiveTexture );
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
    #undef                                      CAST
  return										1;
}

void    dump_user_specifications ( )
{
    s32 gl_major, gl_minor;
    glGetIntegerv( GL_MAJOR_VERSION, &gl_major );
    glGetIntegerv( GL_MINOR_VERSION, &gl_minor );
    LOGGER( "* [render]\t: GPU [vendor:%s]: %s",
            // "* [GLEW] version : [%s]"
            ( pcstr )glGetString( GL_VENDOR ),
            ( pcstr )glGetString( GL_RENDERER )
            // , glewGetString( GLEW_VERSION )
    );
}

}// namespace ogl
}// namespace inex

/* Global extension */
// Texture
PFNGLACTIVETEXTUREPROC glActiveTexture  ;
// VAO
PFNGLGENVERTEXARRAYSPROC    glGenVertexArrays    ;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays ;
PFNGLBINDVERTEXARRAYPROC    glBindVertexArray    ;
// VBO
PFNGLGENBUFFERSPROC    glGenBuffers    ;
PFNGLDELETEBUFFERSPROC glDeleteBuffers ;
PFNGLBINDBUFFERPROC    glBindBuffer    ;
PFNGLBUFFERDATAPROC    glBufferData    ;
PFNGLBUFFERSUBDATAPROC glBufferSubData ;
PFNGLMAPBUFFERPROC     glMapBuffer     ;
PFNGLUNMAPBUFFERPROC   glUnmapBuffer   ;
// Shaders
PFNGLCREATEPROGRAMPROC     glCreateProgram     ;
PFNGLDELETEPROGRAMPROC     glDeleteProgram     ;
PFNGLLINKPROGRAMPROC       glLinkProgram       ;
PFNGLVALIDATEPROGRAMPROC   glValidateProgram   ;
PFNGLUSEPROGRAMPROC        glUseProgram        ;
PFNGLGETPROGRAMIVPROC      glGetProgramiv      ;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog ;
PFNGLCREATESHADERPROC      glCreateShader      ;
PFNGLDELETESHADERPROC      glDeleteShader      ;
PFNGLSHADERSOURCEPROC      glShaderSource      ;
PFNGLCOMPILESHADERPROC     glCompileShader     ;
PFNGLATTACHSHADERPROC      glAttachShader      ;
PFNGLDETACHSHADERPROC      glDetachShader      ;
PFNGLGETSHADERIVPROC       glGetShaderiv       ;
PFNGLGETSHADERINFOLOGPROC  glGetShaderInfoLog  ;
// Attributes
PFNGLGETATTRIBLOCATIONPROC        glGetAttribLocation        ;
PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer      ;
PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray  ;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray ;
// Uniforms
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation  ;
PFNGLUNIFORMMATRIX3FVPROC   glUniformMatrix3fv    ;
PFNGLUNIFORMMATRIX4FVPROC   glUniformMatrix4fv    ;
PFNGLUNIFORM1FPROC          glUniform1f           ;
PFNGLUNIFORM1IPROC          glUniform1i           ;
PFNGLUNIFORM1FVPROC         glUniform1fv          ;
PFNGLUNIFORM2FPROC			    glUniform2f           ;
PFNGLUNIFORM3FVPROC         glUniform3fv          ;
PFNGLUNIFORM3FPROC          glUniform3f           ;
PFNGLUNIFORM4FVPROC         glUniform4fv          ;
