#include "stdafx.h"
#include <inex/engine/ie_engine.h>
#include <inex/core/ie_core.h>
#include <inex/render/core/device.h>

#include <type_traits>
#include <inex/command_line.h>

#include <inex/math_functions.h>
#include <inex/math_float2.h>
#include <inex/math_matrix2.h>

#include <atomic>

#pragma message( "doesn't seem to 'need these defines under linux" )
#define GLEW_STATIC
#define GLEW_STATIC
#define FREEGLUT_STATIC



#include <inex/render/ogl/render_include.h>
#include <inex/sound/sound.h>
#include <inex/sound/sources/sound_object.h>

// #include <GL/glx.h>

extern "C"
{
    void    hello_world_in_rust ( );
}

namespace inex {
namespace platform {

s32		engine_entry_point (	pcstr		command_line_string		);

// void    render_scene_callback ( )
// {

//     // clear framebuffer using color of glClearColor
//     glClear                 ( GL_COLOR_BUFFER_BIT );
//     // swap roles of of backbuffer and frontbuffer
//     glutSwapBuffers         ( );
// }

s32		engine_entry_point ( pcstr command_line_string )
{
    int i               ;
    i                   = command_line::initialize( command_line_string );

	core::initialize	( command_line_string );
    hello_world_in_rust ( );

    // inex::engine::device d; d.run( );

    math::MATH g_CM;
    g_CM.matrix_multiple = math::multiple_pure;

    // if ( command_line::( "-puremath", temp ) ) return;
    // if ( !"-nosse" & SSE_available )
    g_CM.matrix_multiple = math::multiple_sse;
    // call it like g_CM.matrix_multiple( f1, f2 );

	ASSERT_S            ( math::fdEPS != 0.f );
	logging::Msg        ( "Epsilon is: '%0.*f'", 8, math::fdEPS );

	sound::sound_device sound;
	sound.initialize    ( );
	sound::sound_object snd;
	snd.open            ( "gamedata/sound1.wav" );
	sound::sound_object snd2;
	snd2.open           ( "gamedata/motor_a8.wav", 1 );
	snd2.play           ( );
	snd.play            ( );

    ogl::device         device;
// init proc
    device.initialize   ( );
// startup proc
    device.create       ( );


// main cycle
    device.run          ( );

// destroying
    sound.finalize      ( );
    device.destroy      ( );
    core::finalize      ( );

	return				engine::engine{ }.get_exit_code( );
}
} // namespace platform
} // namespace inex

// there's some msvc bullshit which doesn't allow me to
// use wmain as entry point for win x86, so use linux version here
int main( int argc, pstr* argv )
{
	{
        // concat_command_line( argc, argv );
        string512               cmd_line_combined { };
        inex::command_line::concat_command_line( argc, argv, cmd_line_combined );
        inex::platform::engine_entry_point( cmd_line_combined );
	}

	// INEX_DEBUG_WAIT;
   	return 0;
}

/*** Just a mess

    // glXDestroyContext( ( Display* ) ( int * )1, GLXContext ( ) );
	// std::atomic< long > la;
	// printf				( "long is lockfree: %i", la.is_lock_free( ) );


    // printf( "%s\n", command_line_string );

    // int wheel               = 0;
	// glutInit( &wheel,  nullptr );                       // used to pass params to gl
	// glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA ); // enable double buffering and color buffer
	// glutInitWindowSize( 400, 1400 );                // these 3 lines specify window params
	// glutInitWindowPosition( 100, 200 );
	// glutCreateWindow( "Lesson 01" );
    // glutDisplayFunc( render_scene_callback );       // use main callback to render of 1 frame
    // glClearColor( 0.f, 0.f, 0.f, 0.f );

    // // glutMainLoop( );

    // ASSERT_S        ( glfwInit( ) );
    // glfwWindowHint  (GLFW_CONTEXT_VERSION_MAJOR, 3 );
    // glfwWindowHint  (GLFW_CONTEXT_VERSION_MINOR, 0 );
    // // access new features dropping the deprecated stuff
    // glfwWindowHint  ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    // // for MACOS glfwWindowHint  ( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

    // GLFWwindow* window  = glfwCreateWindow( 800u, 600u, "title", NULL, NULL );
    // if ( NULL == window )
    // {
    //     glfwTerminate   ( );
    //     ASSERT_D        ( window, "Failed to create OpenGL window" );
    // }

    // glfwMakeContextCurrent  ( window );
    // glViewport              ( 0, 0, 800, 600  );

    // while ( !glfwWindowShouldClose( window ) )
    // {
    //     glfwSwapBuffers     ( window );
    //     glfwPollEvents      ( );
    // }
    //    inex::core


    // engine::device  device;
    // device.run( );

	// GLFWwindow* window;
	// VERIFY( glfwInit( ) );

	// window				= glfwCreateWindow( 640, 480, "Inex", nullptr, nullptr );
    // ASSERT_D( window, "Couldn't create window and its OpenGL context." );

    // // Make the window's context current
    // glfwMakeContextCurrent( window );

    // glewExperimental	= 1;
    // GLenum err			= glewInit( );
	// ASSERT_D( err == GLEW_OK, "Glew Inititialization failed, something is seriously wrong." );

    // while ( !glfwWindowShouldClose( window ) )
    // {
    //     glClear			( GL_COLOR_BUFFER_BIT );

    //     glBegin			( GL_TRIANGLES );
    //     glColor3f		( 0.1, 0.2, 0.3 );
    //     glVertex3f		( 0, 0, 0 );
    //     glVertex3f		( -1, 0, 0 );
    //     glVertex3f		( 0, -1, 0 );
    //     glEnd			( );

    //     // Swap front and back buffers
    //     glfwSwapBuffers	( window );

    //     // Poll for and process events
    //     glfwPollEvents	( );
    // }

    // glfwTerminate		( );
***/
