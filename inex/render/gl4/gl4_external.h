////////////////////////////////////////////////////////////////////////////
//	Created 	: 23.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef GL4_EXTERNAL_H_INCLUDED
#   define GL4_EXTERNAL_H_INCLUDED

# 	if INEX_PLATFORM_LINUX
#		include <X11/Xlib.h>
#		include <X11/Xutil.h>
#		include <EGL/egl.h>
#		include <EGL/eglplatform.h>
#		include <EGL/eglext.h>
#		include <GLES3/gl3.h> 
#	elif INEX_PLATFORM_WINDOWS
#		define GLX_GLXEXT_LEGACY
#		include <inex/3rd_patry/include/GL/gl.h>
#		include <inex/3rd_patry/include/GL/glext.h>
#	   	include <inex/3rd_patry/include/GL/wglext.h>
//#		include <inex/3rd_patry/include/GLFW/glfw3.h>
#	endif // #if INEX_PLATFORM_WINDOWS

#	if INEX_PLATFORM_LINUX
//#	error please use hw_wrapper_context instead of this
// Context
#	elif INEX_PLATFORM_WINDOWS // #	if INEX_PLATFORM_LINUX
//struct GLFWwindow;
//struct gl_context;
//typedef  gl_context GLFWwindow;
//extern GLFWwindow		*		g_gl4_context;
#	endif  // #	if INEX_PLATFORM_LINUX

		/**************************************		Global extension	**************************************/

// Texture
#	if !INEX_PLATFORM_LINUX
extern PFNGLACTIVETEXTUREPROC	glActiveTexture;
#	endif // #if !INEX_PLATFORM_LINUX

#	if INEX_PLATFORM_WINDOWS // linux already defines this
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
extern PFNGLDRAWARRAYSEXTPROC		glDrawArraysExt;
// Texture
extern PFNGLACTIVETEXTUREPROC	glActiveTexture;
#	endif

#endif // GL4_EXTERNAL_H_INCLUDED
