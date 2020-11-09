#include "pch.h"
#include "hw_wrapper.h"
#include <inex/render/base/engine_wrapper.h>
#include <inex/render/gl4/gl4_extensions.h>

#define GLFW_INCLUDE_NONE
#include <inex/3rd_patry/include/GLFW/glfw3.h>

#pragma comment( lib, "glfw3.lib" )
#pragma comment( lib, "opengl32.lib" )

bool	initialize_extensions ( )
{
	GLenum params[] = {
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

	const char* names[] = {
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

	LOGGER("GL Context Params:\n");
	string256 msg;
	// integers - only works if the order is 0-10 integer return types
	for (int i = 0; i < 10; i++) {
		int v = 0;
		glGetIntegerv (params[i], &v);
		LOGGER ("%s %i", names[i], v);
	}

	return				inex::render::initialize	( );
}

void windowSizeCallback(GLFWwindow *, int width, int height) {
  glViewport(0, 0, width, height);
    /* update any perspective matrices used here */
}

GLFWwindow			*           g_gl4_context;

void	error_callback ( int error, const char * description )
{
   LOGGER	( " [hw_wrapper:gl4][error]: %s\n", description );
}

//static
//void	key_callback ( GLFWwindow* window, int key, int scancode, int action, int mods )
//{
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, GLFW_TRUE);
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

void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
        if(key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* initWindow(const int resX, const int resY)
{
	glfwSetErrorCallback( error_callback );
	glfwWindowHint		( GLFW_SAMPLES, 4 );

    if(!glfwInit())
         ASSERT_D( 0, "Failed to initialize GLFW\n");
#if INEX_PLATFORM_MAC
	glfwWindowHint	(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint	(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint	(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint	(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif // #if INEX_PLATFORM_MAC
	//GLFWmonitor* mon = glfwGetPrimaryMonitor ();
	//const GLFWvidmode* vmode = glfwGetVideoMode (mon);
	g_gl4_context = glfwCreateWindow ( resX, resY, "Extended GLInit", 0, NULL);

    if(g_gl4_context == NULL)
        ASSERT_D( 0, "Failed to open GLFW window.\n");

    glfwMakeContextCurrent(g_gl4_context);
    glfwSetKeyCallback(g_gl4_context, controls);
	glfwSetWindowSizeCallback (g_gl4_context, windowSizeCallback);

	VERIFY			( initialize_extensions( ) );
    // Get info of GPU and supported OpenGL version
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	glEnable					( GL_DEPTH_TEST ); // enable depth-testing
	glDepthFunc					( GL_LESS );
    return g_gl4_context;
}

void hw_wrapper::create_device(HWND hwnd, bool move_window)
{
	m_move_window	= move_window;

	// for dll
	create_d3d();

	bool  windowed	= true;


	if (windowed)
	{

	} else 
	{
	}

	constexpr u32 size_x	= 480;
	constexpr u32 size_y	= 320;

	g_gl4_context  = initWindow(1024, 620);
	VERIFY ( g_gl4_context );

	/*
		glfwSetErrorCallback( error_callback );
	// glfwSetKeyCallback( window, key_callback );
	VERIFY				( glfwInit( ) );

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	//glfwDefaultWindowHints( );

	glfwWindowHint		( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint		( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint		( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint		( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

	// Create the device
	g_gl4_context		= glfwCreateWindow( size_x, size_y, "__INEX__", nullptr, nullptr );
	LOGGER          ( "* '%s' window: initial config: [%d x %d]", "__INEX__", size_x, size_y );
	ASSERT_D        ( g_gl4_context, "Couldn't create window and its OpenGL context." );
	glfwMakeContextCurrent( g_gl4_context );

	VERIFY			( initialize_extensions( ) );
	// Display the name of video board
	s32 gl_major	= -1;
	s32 gl_minor	= -1;
    glGetIntegerv	( GL_MAJOR_VERSION, &gl_major );
    glGetIntegerv	( GL_MINOR_VERSION, &gl_minor );
	ASSERT_D		( ( gl_major != -1 ) || ( gl_minor != -1 ), "opengl fcked up" );

    LOGGER			(
		"* [hw_wrapper]\t: GPU [vendor:%s]: %s\n\t"
        "* [OpenGL] version : [%d.%d]",
        ( pcstr ) glGetString( GL_VENDOR ),
        ( pcstr ) glGetString( GL_RENDERER ), gl_major, gl_minor
            // , glewGetString( GLEW_VERSION )
    );

	glfwSwapInterval( 1 );

	glfwSetFramebufferSizeCallback          ( g_gl4_context, framebuffer_size_callback );
	glfwSetWindowSizeCallback				( g_gl4_context, windowSizeCallback );

	glfwShowWindow	( g_gl4_context);
	*/
		// Fatal error! Cannot create rendering device AT STARTUP !!!
		//LOG_ERROR("Failed to initialize graphics hardware.\nPlease try to restart the game.");


	//log_ref_count("* CREATE: Device", m_device);
		//LOG_INFO("* Vertex Processor: SOFTWARE");

	// Capture misc data
	//LOG_INFO("*     Texture memory: %d M",	memory/(1024*1024));
	//LOG_INFO("*          DDI-level: %2.1f",	float(D3DXGetDriverLevel(m_device))/100.f);

}

void hw_wrapper::destroy_device()
{
	//log_ref_count("* DESTROY: Device", m_device);
	 LOGGER              ( "- [hw_wrapper]\t: destroying" );
    // glBindVertexArray   ( 0u );
    glfwTerminate		( );
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
