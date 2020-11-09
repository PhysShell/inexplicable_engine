////////////////////////////////////////////////////////////////////////////
//	Created 	: 23.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef GL4_EXTERNAL_H_INCLUDED
#   define GL4_EXTERNAL_H_INCLUDED

#	define GLX_GLXEXT_LEGACY

#	if INEX_PLATFORM_LINUX
#	   include "../../3rd_patry/include/GL/glx.h"
#	endif // #if INEX_PLATFORM_LINUX

#	include <inex/3rd_patry/include/GL/gl.h>
#	include <inex/3rd_patry/include/GL/glext.h>

#	if INEX_PLATFORM_WINDOWS
#	   include <inex/3rd_patry/include/GL/wglext.h>
#	endif // #if INEX_PLATFORM_WINDOWS


		/**************************************		Global extension	/**************************************/
// Context
struct GLFWwindow;
extern GLFWwindow		*		g_gl4_context;

// Texture
extern PFNGLACTIVETEXTUREPROC	glActiveTexture;
// VAO
extern PFNGLGENVERTEXARRAYSPROC   	glGenVertexArrays;
extern PFNGLDELETEVERTEXARRAYSPROC 	glDeleteVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC    	glBindVertexArray;
// VBO
extern PFNGLGENBUFFERSPROC    	glGenBuffers;
extern PFNGLDELETEBUFFERSPROC 	glDeleteBuffers;
extern PFNGLBINDBUFFERPROC		glBindBuffer;
extern PFNGLBUFFERDATAPROC    	glBufferData;
extern PFNGLBUFFERSUBDATAPROC 	glBufferSubData;
extern PFNGLMAPBUFFERPROC     	glMapBuffer;
extern PFNGLUNMAPBUFFERPROC   	glUnmapBuffer;
// Shaders
extern PFNGLCREATEPROGRAMPROC     	glCreateProgram;
extern PFNGLDELETEPROGRAMPROC     	glDeleteProgram;
extern PFNGLLINKPROGRAMPROC       	glLinkProgram;
extern PFNGLVALIDATEPROGRAMPROC   	glValidateProgram;
extern PFNGLUSEPROGRAMPROC        	glUseProgram;
extern PFNGLGETPROGRAMIVPROC      	glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC 	glGetProgramInfoLog;
extern PFNGLCREATESHADERPROC      	glCreateShader;
extern PFNGLDELETESHADERPROC      	glDeleteShader;
extern PFNGLSHADERSOURCEPROC      	glShaderSource;
extern PFNGLCOMPILESHADERPROC     	glCompileShader;
extern PFNGLATTACHSHADERPROC      	glAttachShader;
extern PFNGLDETACHSHADERPROC      	glDetachShader;
extern PFNGLGETSHADERIVPROC       	glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC  	glGetShaderInfoLog;
// Attributes
extern PFNGLGETATTRIBLOCATIONPROC        glGetAttribLocation;
extern PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
// Uniforms
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORMMATRIX3FVPROC   	glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC   	glUniformMatrix4fv;
extern PFNGLUNIFORM1FPROC          	glUniform1f;
extern PFNGLUNIFORM1IPROC          	glUniform1i;
extern PFNGLUNIFORM1FVPROC         	glUniform1fv;
extern PFNGLUNIFORM2FPROC			glUniform2f;
extern PFNGLUNIFORM3FVPROC         	glUniform3fv;
extern PFNGLUNIFORM3FPROC          	glUniform3f;
extern PFNGLUNIFORM4FVPROC         	glUniform4fv;

#endif // GL4_EXTERNAL_H_INCLUDED