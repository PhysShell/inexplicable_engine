#include "stdafx.h"
#include <inex/engine/ie_engine.h>
#include <inex/core/ie_core.h>
#include <inex/engine/sources/engine_device.h>

#include <type_traits>

#include <inex/math_functions.h>
#include <inex/math_float2.h>
#include <inex/math_matrix2.h>

#include <atomic>

#pragma message( "doesn't seem to 'need these defines under linux" )
#define GLEW_STATIC
#define GLEW_STATIC
#define FREEGLUT_STATIC

#include <inex/render/ogl/render_include.h>

extern "C"
{
    void    hello_world_in_rust ( );
}

namespace inex {
namespace platform {

s32		engine_entry_point (	pstr		command_line_string		);

s32		engine_entry_point ( pstr command_line_string )
{
    //static_assert( std::is_signed< size_t >( ), "adada" );

    hello_world_in_rust ( );
	core::initialize	( 0, 0 );
	logging::Msg		( "Initializing Engine...\n" );

    math::MATH g_CM;
    g_CM.matrix_multiple = math::multiple_pure;

    // if ( command_line::( "-puremath", temp ) ) return;
    // if ( !"-nosse" & SSE_available )
    g_CM.matrix_multiple = math::multiple_sse;
    // call it like g_CM.matrix_multiple( f1, f2 );



    engine::device  device;
    device.run( );


    // for ( float const x : a ) printf ( "a='%d';\n", x );

    // for ( float const x : b ) printf ( "b='%d';\n", x );
    // float a[ 4 ]        = { 1.f, 2.f, 3.f, 4.f };
    // float b[ 4 ]        = { 1.f, 2.f, 3.f, 4.f };
    // // a[ 0 ] = a[ 1 ] = a[ 2 ] = a[ 3 ]           = 1.5f;
    // for ( u8 i = 0; i < 1; ++ i )
    // {
    //     printf ( "a='%f';\n", a[ i ] );
    //     printf ( "b='%f';\n", b[ i ] );
    //     printf ( "a='%f';\n", a[ 1 + i ] );
    //     printf ( "b='%f';\n", b[ 1 + i ] );
    //     printf ( "a='%f';\n", a[ 2 + i ] );
    //     printf ( "b='%f';\n", b[ 2 + i ] );
    //     printf ( "a='%f';\n", a[ 3 + i ] );
    //     printf ( "b='%f';\n", b[ 3 + i ] );
    // }
    // math::multiple_sse  ( a, b );
    //     printf ( "\nSSE\n" );
    // for ( u8 i = 0; i < 1; ++ i )
    // {
    //     printf ( "a='%f';\n", a[ i ] );
    //     printf ( "b='%f';\n", b[ i ] );
    //     printf ( "a='%f';\n", a[ 1 + i ] );
    //     printf ( "b='%f';\n", b[ 1 + i ] );
    //     printf ( "a='%f';\n", a[ 2 + i ] );
    //     printf ( "b='%f';\n", b[ 2 + i ] );
    //     printf ( "a='%f';\n", a[ 3 + i ] );
    //     printf ( "b='%f';\n", b[ 3 + i ] );
    // }
	ASSERT_S            ( math::fdEPS != 0.f );
	logging::Msg        ( "Epsilon is: '%0.*f'", 8, math::fdEPS );
	engine::engine		en;

	// std::atomic< long > la;
	// printf				( "long is lockfree: %i", la.is_lock_free( ) );


    // int i               = 0;
	// glutInit( &i,  nullptr );
	// glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	// glutInitWindowSize(400, 1400);
	// glutInitWindowPosition(100, 200);
	// glutCreateWindow("Lesson 01");

	GLFWwindow* window;
	VERIFY( glfwInit( ) );

	window				= glfwCreateWindow( 640, 480, "Inex", nullptr, nullptr );
    ASSERT_D( window, "Couldn't create window and its OpenGL context." );

    /* Make the window's context current */
    glfwMakeContextCurrent( window );

    glewExperimental	= 1;
    GLenum err			= glewInit( );
	ASSERT_D( err == GLEW_OK, "Glew Inititialization failed, something is seriously wrong." );

    while ( !glfwWindowShouldClose( window ) )
    {
        glClear			( GL_COLOR_BUFFER_BIT );

        glBegin			( GL_TRIANGLES );
        glColor3f		( 0.1, 0.2, 0.3 );
        glVertex3f		( 0, 0, 0 );
        glVertex3f		( -1, 0, 0 );
        glVertex3f		( 0, -1, 0 );
        glEnd			( );

        /* Swap front and back buffers */
        glfwSwapBuffers	( window );

        /* Poll for and process events */
        glfwPollEvents	( );
    }

    glfwTerminate		( );

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
