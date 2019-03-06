#include "stdafx.h"
#include <inex/engine/ie_engine.h>
#include <inex/core/ie_core.h>

#define GLEW_STATIC
#define GLEW_STATIC
#define FREEGLUT_STATIC

#include <inex/render/core/sources/render_include.h>

namespace inex {
namespace platform {

s32		engine_entry_point (	pstr		command_line_string		);


s32		engine_entry_point ( pstr command_line_string )
{
 //   int i               = 0;
	core::initialize	( 0, 0 );
	logging::Msg		( "Initializing Engine...\n" );
	engine::engine		en;
//	glutInit( &i,  nullptr );
//	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
//	glutInitWindowSize(400, 1400);
//	glutInitWindowPosition(100, 200);
//	glutCreateWindow("Lesson 01");

	// GLFWwindow* window;
	// VERIFY( glfwInit( ) );

	// window				= glfwCreateWindow( 640, 480, "Inex", nullptr, nullptr );
    // ASSERT_D( window, "Couldn't create window and its OpenGL context." );

    // /* Make the window's context current */
    // glfwMakeContextCurrent( window );

    // glewExperimental	= 1;
    // GLenum err			= glewInit( );
	// ASSERT_D( err == GLEW_OK, "Glew Inititialization failed, something is seriously wrong." );

//     while ( !glfwWindowShouldClose( window ) )
//     {
//         glClear			( GL_COLOR_BUFFER_BIT );

//         glBegin			( GL_TRIANGLES );
//         glColor3f		( 0.1, 0.2, 0.3 );
//         glVertex3f		( 0, 0, 0 );
//         glVertex3f		( -1, 0, 0 );
//         glVertex3f		( 0, -1, 0 );
//         glEnd			( );

//         /* Swap front and back buffers */
//         glfwSwapBuffers	( window );

//         /* Poll for and process events */
//         glfwPollEvents	( );
//     }

//     glfwTerminate		( );

	return				en.get_exit_code( );
}

} // namespace platform
} // namespace inex


// there's some msvc bullshit which doesn't allow me to
// use wmain as entry point for win x86, so use linux version here
int main( int argc, pstr* argv )
{
	{
		inex::platform::engine_entry_point( 0 );
	}

	INEX_DEBUG_WAIT;
   	return 0;
}
