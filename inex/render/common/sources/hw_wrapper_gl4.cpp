#include "pch.h"
#include "hw_wrapper.h"
#include <inex/render/base/engine_wrapper.h>
#include <inex/core/sources/ie_memory.h>
#include <inex/render/gl4/gl4_extensions.h>

#if INEX_PLATFORM_WINDOWS

#	pragma comment( lib, "glfw3.lib" )
#	pragma comment( lib, "opengl32.lib" )
#endif // #if INEX_PLATFORM_WINDOWS

/* Global extension */
// Texture
#if !INEX_PLATFORM_LINUX
PFNGLACTIVETEXTUREPROC glActiveTexture  ;
#endif // #if !INEX_PLATFORM_LINUX
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

gl_context			*           g_gl4_context;

void 	make_context_current ( gl_context * context )
{
	glXMakeCurrent	( GLX.display, GLX.window, GLX.context );
}

void 	set_window_title ( gl_context * context, pcstr const window_name )
{
	XStoreName		( GLX.display, GLX.window, window_name );
}

bool	initialize_extensions ( )
{
	inex::render::initialize	( );

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

	return				true;
}

gl_context * 	gl_create_window ( u32 const x, u32 const y, pcstr window_name )
{
	LOGGER 				( "- [hw-wrapper][info]\t: requesting '%d' bytes to store context... " );
	g_gl4_context		= inex::memory::ie_new< gl_context >( );
	LOGGER 				( "\t\t\t\t... successfully allocated at '%p'", g_gl4_context );
	GLX.display 		= XOpenDisplay( NULL );
	ASSERT_D			( GLX.display, "Xlib error: Cannot connect to X server" );

	GLX.root			= DefaultRootWindow( GLX.display );
	GLX.visual_info		= glXChooseVisual( GLX.display, 0, GLX.attributes );
	ASSERT_D			( GLX.visual_info, "Xlib error: No appropriate visual found" );
	LOGGER				( "- [hw-wrapper][info]\t: glx visual '%p' selected", ( pvoid ) GLX.visual_info->visualid );

	GLX.color_map		=
		XCreateColormap (
			GLX.display,
			GLX.root,
			GLX.visual_info->visual,
			AllocNone
		);

	GLX.window_attributes.colormap	= GLX.color_map;
	GLX.window_attributes.event_mask = ExposureMask | KeyPressMask;

 	GLX.window 			=
		XCreateWindow (
			GLX.display,
			GLX.root,
			0,
			0,
			600,
			600,
			0,
			GLX.visual_info->depth,
			InputOutput,
			GLX.visual_info->visual,
			CWColormap | CWEventMask,
			&GLX.window_attributes
		 );

	XSelectInput	( GLX.display, GLX.window, KeyPressMask | KeyReleaseMask );

	XMapWindow		( GLX.display, GLX.window );
	XStoreName		( GLX.display, GLX.window, window_name );

 	GLX.context		= glXCreateContext( GLX.display, GLX.visual_info, NULL, GL_TRUE );
    make_context_current    ( g_gl4_context );
	VERIFY			( initialize_extensions( ) );
	return 			g_gl4_context;
}

void 	gl_terminate ( )
{
	// glfwTerminate
	glXMakeCurrent		( GLX.display, None, NULL );
	glXDestroyContext	( GLX.display, GLX.context );
	XDestroyWindow		( GLX.display, GLX.window);
	XCloseDisplay		( GLX.display );

	inex::memory::ie_delete	( &GLX );
}

void	error_callback ( int error, const char * description )
{
   LOGGER	( " [hw_wrapper:gl4][error]: %s\n", description );
}

namespace inex {
namespace render {

hw_wrapper::hw_wrapper( inex::render::engine::wrapper& wrapper, HWND hwnd ):
	m_wrapper		( wrapper ),
	m_hwnd			( hwnd )
{
	//m_wrapper.run_in_window_thread( std::bind( &hw_wrapper::create_device, this ) );
	create_device	( );
}

hw_wrapper::~hw_wrapper()
{
	//m_wrapper.run_in_window_thread( boost::bind( &hw_wrapper::destroy_device, this ) );
	destroy_device	( );
}

void hw_wrapper::create_d3d()
{
	// HANDLE DLL HERE //
}

void hw_wrapper::destroy_d3d()
{
}

void hw_wrapper::create_device( )
{
    // Texture
    // glActiveTexture = get_procedure_address<PFNGLACTIVETEXTUREARBPROC>( glActiveTexture, ( const GLubyte* )"glActiveTexturexARB" );
    // VERIFY( glActiveTexture );
    // glActiveTexture = ( PFNGLACTIVETEXTUREPROC )glXGetProcAddress( ( const GLubyte * )"glActiveTextureARB" );
    // glGenVertexArrays = ( PFNGLGENVERTEXARRAYSPROC )glXGetProcAddress( ( const GLubyte * )"glGenVertexArray" );
    // get_procedure_address< PFNGLGENVERTEXARRAYSPROC>( glGenVertexArrays, (const GLubyte*)"glGenVertexArrays" );


	create_device(m_hwnd, false);
}

gl_context * 	initialize_context ( u32 const x, u32 const y )
{
	g_gl4_context 		= gl_create_window ( x, y, "In-EX engine" );
    ASSERT_D			( g_gl4_context != nullptr, "Failed to open GLX window.\n");
    LOGGER	(
		"* [render][info]\t: %s\n* [render][info]\t: OpenGL version supported %s\n",
		glGetString( GL_RENDERER ),
		glGetString( GL_VERSION )
	);

	glEnable			( GL_DEPTH_TEST ); // enable depth-testing
	glDepthFunc			( GL_LESS );

    return 				g_gl4_context;
}

void hw_wrapper::create_device(HWND hwnd, bool move_window)
{
	m_move_window			= move_window;
	// for dll
	create_d3d				( );

	bool  windowed			= true;

	if (windowed)
	{

	} else
	{
	}

	constexpr u32 size_x	= 1024;
	constexpr u32 size_y	= 620;

	g_gl4_context  			= initialize_context( size_x, size_y );
	VERIFY 					( g_gl4_context );
}

void hw_wrapper::destroy_device()
{
	//log_ref_count("* DESTROY: Device", m_device);
	LOGGER              ( "- [hw_wrapper]\t: destroying" );
	gl_terminate		( );
    // glBindVertexArray   ( 0u );
	destroy_d3d();
}

void hw_wrapper::update_window_props(HWND hw) const
{
	INEX_UNREFERENCED_PARAMETERS	( hw );
}

u32 hw_wrapper::select_gpu() const
{
	return							0u;
}

void hw_wrapper::select_resolution(u32 &width, u32 &height, bool windowed) const
{
	if(windowed)
	{
		width = 0;
		height = 0;
	}
	else
	{
		ASSERT_S	(!"Not implemented for fullscreen.");
	}
}

void hw_wrapper::reset()
{
	bool windowed	= true;
}

} // namespace render
} // namespace inex
