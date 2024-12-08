#include <inex/render/gl4/sources/pch.h>
#include "hw_wrapper.h"
#include <inex/render/base/engine_wrapper.h>
#include <inex/core/sources/ie_memory.h>
#include <inex/render/gl4/gl4_extensions.h>

#if INEX_PLATFORM_WINDOWS
#	include <inex/render/common/sources/hw_wrapper_base_gl4_win_winapi.h>
//#	pragma comment( lib, "glfw3.lib" )
#	pragma comment( lib, "opengl32.lib" )
#elif INEX_PLATFORM_LINUX
#	include <inex/render/common/sources/hw_wrapper_base_gl4_linux_xlib.h>
#endif // #if INEX_PLATFORM_WINDOWS

/* Global extension */
// Texture


//inex::render::hw_wrapper_context			*           g_gl4_context;



//gl_context * 	gl_create_window ( u32 const x, u32 const y, pcstr window_name )
//{
//	VERIFY			( initialize_extensions( ) );
//	return 			g_gl4_context;
//}

void 	gl_terminate ( )
{
#if INEX_PLATFORM_WINDOWS
	
#elif INEX_PLATFORM_LINUX // #if INEX_PLATFORM_WINDOWS
	//glXMakeCurrent		( GLX.display, None, NULL );
	//glXDestroyContext	( GLX.display, GLX.context );
	//XDestroyWindow		( GLX.display, GLX.window);
	//XCloseDisplay		( GLX.display );
	//inex::memory::ie_delete	( &GLX );
#endif // #if INEX_PLATFORM_WINDOWS
}

//void	error_callback ( int error, const char * description )
//{
//   LOGGER	( " [hw_wrapper:gl4][error]: %s\n", description );
//}

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
//#if INEX_PLATFORM_WINDOWS
//void windowSizeCallback(GLFWwindow *, int width, int height) {
//  glViewport(0, 0, width, height);
//    /* update any perspective matrices used here */
//}
//
//void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//    if(action == GLFW_PRESS)
//        if(key == GLFW_KEY_ESCAPE)
//            glfwSetWindowShouldClose(window, GL_TRUE);
//}
//
//void	error_callback ( int error, const char * description )
//{
//   LOGGER	( " [hw_wrapper:gl4][error]: %s\n", description );
//}
//#endif // #if INEX_PLATFORM_WINDOWS

//gl_context * 	initialize_context ( u32 const x, u32 const y )
//{
//
//#if INEX_PLATFORM_MAC
//	glfwWindowHint	(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint	(GLFW_CONTEXT_VERSION_MINOR, 2);
//	glfwWindowHint	(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	glfwWindowHint	(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//# elif INEX_PLATFORM_LINUX
//    // glfwWindowHint(GLFW_SAMPLES, 4);
//    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	g_gl4_context 		= gl_create_window ( x, y, "In-EX engine" );
//#else
//		glfwSetErrorCallback( error_callback );
//	if( !glfwInit( ) )
//         ASSERT_D( 0, "Failed to initialize GLFW\n");
//		glfwWindowHint		( GLFW_SAMPLES, 4 );
//
//	//GLFWmonitor* mon = glfwGetPrimaryMonitor ();
//	//const GLFWvidmode* vmode = glfwGetVideoMode (mon);
//	g_gl4_context = ( GLFWwindow * )glfwCreateWindow ( x, y, "Extended GLInit", 0, NULL);
//
//    if(g_gl4_context == NULL)
//        ASSERT_S( !"Failed to open GLFW window.\n");
//
//    glfwMakeContextCurrent		( g_gl4_context );
//    glfwSetKeyCallback			( g_gl4_context, ( GLFWkeyfun ) controls);
//	glfwSetWindowSizeCallback	( g_gl4_context, ( GLFWwindowsizefun  ) windowSizeCallback);
//
//	gl_create_window			( x, y, "In-EX engine" );
//
//#endif // #if INEX_PLATFORM_MAC
//
//
//
//    ASSERT_D			( g_gl4_context != nullptr, "Failed to open GLX window.\n");
//    s32 gl_major		= -1;
//    s32 gl_minor		= -1;
//    glGetIntegerv		( GL_MAJOR_VERSION, &gl_major );
//    glGetIntegerv		( GL_MINOR_VERSION, &gl_minor );
//    ASSERT_D			( ( gl_major != -1 ) || ( gl_minor != -1 ), "Failed to execute low-level OpenGL functionality. Problem with -lGL-like libs." );
//	
//    LOGGER	(
//		"* [render][info]\t: %s\n* [render][info]\t: OpenGL version supported %s\n",
//		glGetString( GL_RENDERER ),
//		glGetString( GL_VERSION )
//	);
//
//	//glEnable			( GL_DEPTH_TEST ); // enable depth-testing
//	//glDepthFunc			( GL_LESS );
//
//    return 				g_gl4_context;
//}

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

#if INEX_PLATFORM_WINDOWS
	hw_wrapper_base::create(size_x, size_y, "inexplicable_engine_winapi_wgl_renderer", GetModuleHandleW( NULL ), 0); // #if INEX_PLATFORM_WINDOWS
#elif INEX_PLATFORM_LINUX
	hw_wrapper_base::create(size_x, size_y, "inexplicable_engine_x11_egl_renderer"); // #if INEX_PLATFORM_WINDOWS
#else // #if INEX_PLATFORM_WINDOWS
#	error please define your platform call
#endif // #if INEX_PLATFORM_WINDOWS
	//VERIFY 					( g_gl4_context );
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
