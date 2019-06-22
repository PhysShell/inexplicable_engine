#include "stdafx.h"
#include <inex/engine/ie_engine.h>
#include <inex/os_include.h>
#include <inex/core/ie_core.h>
#include <inex/render/ogl/render_include.h>

namespace inex {
namespace platform {

s32		engine_entry_point (	HINSTANCE	hInst,
								HINSTANCE	hPreInst,
								pstr		lpCmdLine,
								s32			nCmdShow 
							);

s32		engine_entry_point ( HINSTANCE inst, HINSTANCE pinst, pstr cmdln, s32 cmdshow )
{
	string128			buffer;
	strcpy				( buffer, GetCommandLineA( ) );
	core::initialize	( buffer );
	logging::Msg		( "Initializing Engine...\n" );
	engine::engine		en;
	//glutInit( ( int * )0, nullptr );
	//glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	//glutInitWindowSize(400, 1400);
	//glutInitWindowPosition(100, 200);
	//glutCreateWindow("Lesson 01");
	
	GLFWwindow* window;
	VERIFY( glfwInit( ) );
	glfwWindowHint		( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint		( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint		( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	window				= glfwCreateWindow( 640, 480, "Inex", nullptr, nullptr );
    ASSERT_D( window, "Couldn't create window and its OpenGL context." );

    /* Make the window's context current */
    glfwMakeContextCurrent( window );

	ASSERT_D( ogl::init_extensions( ), "Failed to load OpenGL extensions..." );

//    glewExperimental	= 1;
  //  GLenum err			= glewInit( );
	//ASSERT_D( err == GLEW_OK, "Glew Inititialization failed, something is seriously wrong." );

	glViewport			( 0, 0, 640, 480 );
    while ( !glfwWindowShouldClose( window ) )
    {
			

        glfwSwapBuffers	( window );
        glfwPollEvents	( );
    }

    glfwTerminate		( );

	core::finalize		( );
	return				en.get_exit_code( );
}

} // namespace platform
} // namespace inex

int 	wmain (	HINSTANCE	hInst,
					HINSTANCE	hPreInst,
					LPSTR		lpCmdLine,
					int			nCmdShow )
{
	inex::platform::engine_entry_point	( hInst, hPreInst, lpCmdLine, nCmdShow );

	INEX_DEBUG_WAIT;
	return					0;
}

