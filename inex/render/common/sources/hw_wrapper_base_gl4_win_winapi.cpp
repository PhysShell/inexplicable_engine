#include <pch.h>
#include <inex/render/common/sources/hw_wrapper_base_gl4_win_winapi.h>
#include <inex/render/gl4/gl4_extensions.h>

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
PFNGLUNIFORM2FPROC			    glUniform2f     ;
PFNGLUNIFORM3FVPROC         glUniform3fv          ;
PFNGLUNIFORM3FPROC          glUniform3f           ;
PFNGLUNIFORM4FVPROC         glUniform4fv          ;

PFNGLDRAWARRAYSEXTPROC		glDrawArraysExt		;

void	inex::render::hw_wrapper_base::create (  u32 const x, u32 const y, pcstr const window_title, HINSTANCE handle_instance, int command_line_show )
{
	if (m_context->create(x, y, handle_instance, command_line_show, window_title) != 0) {
		PostQuitMessage(1);
	}
}