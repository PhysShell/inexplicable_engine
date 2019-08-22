#include "pch.h"

#include <inex/core/sources/ie_memory.h>
#include <inex/render/core/device.h>
#include <inex/render/common/sources/render_device.h>
#include <inex/render/ogl/ogl_extensions.h>
#include <inex/3rd_patry/include/GLFW/glfw3.h>
#include <inex/render/core/shaders.h>

#include <time.h>

static
void    framebuffer_size_callback ( GLFWwindow* window, int width, int height )
{
    glViewport          ( 0, 0, width, height );
}

namespace inex {
namespace ogl {

void    device::initialize ( )
{
    LOGGER( "Initializing Engine...");
    VERIFY( glfwInit( ) );
    m_render_device     = memory::ie_new< render::render_device >( );
    glfwWindowHint		( GLFW_CONTEXT_VERSION_MAJOR, 3 ); 
    glfwWindowHint		( GLFW_CONTEXT_VERSION_MINOR, 3 ); 
    glfwWindowHint		( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); 
    
    m_width             = 480;
    m_height            = 640;
    m_render_device->   create_helper      ( m_context, m_width, m_height );
    
    u32 vertex_array_object     ;
    glGenVertexArrays           ( 1, &vertex_array_object );
    glBindVertexArray(          vertex_array_object         );

    float vertices[ ] =
    {
    //    X      Y       Z
        -.5f,   -.5f,   .0f,
        .5f,    -.5f,   .0f,
        .0f,    .5f,    .0f
    };

    u32 vertex_buffer_object;
    // store data in GPU memory
    glGenBuffers        ( 1, &vertex_buffer_object );
    // set vertex_buffer_object to be modified any GL_ARRAY_BUFFER calls occur
    glBindBuffer        ( GL_ARRAY_BUFFER, vertex_buffer_object );
    // buffer the 'vertices' data into allocated buffer memory
    glBufferData        ( GL_ARRAY_BUFFER, sizeof ( vertices ), vertices, GL_STATIC_DRAW );

    // // vertex shader
    // u32 vertex_shader   = glCreateShader( GL_VERTEX_SHADER );
    // GLchar* vertex_shader_source = ( GLchar* )"#version 330 core\n"
    // "layout (location=0) in vec3 aPos;"
    // // we're setting position through gl_position var for next step
    // "void main() {gl_Position         = vec4(aPos.x,aPos.y,aPos.z,1.0); }";
    // glShaderSource      ( vertex_shader, 1, &vertex_shader_source, nullptr );
    // glCompileShader     ( vertex_shader );

    // s32 compiled        ;
    // glGetShaderiv       ( vertex_shader, GL_COMPILE_STATUS, &compiled );
    // if ( !compiled )
    // {
    //     string512 buffer;
    //     glGetShaderInfoLog  ( vertex_shader, sizeof ( buffer ), nullptr, buffer );
    //     LOGGER( "! Shader compilation error [vertex_shader.glsl]: %s", buffer );
    // }

    // // fragment shader
    // u32 fragment_shader;
    // GLchar* fragment_shader_source = ( GLchar* )"#version 330 core\nout vec4 Color;void main() {Color= vec4(1.0f,.5f,.9f,1.0f);}";
    // fragment_shader     = glCreateShader( GL_FRAGMENT_SHADER );
    // glShaderSource      ( fragment_shader, 1, &fragment_shader_source, NULL );
    // glCompileShader     ( fragment_shader );

    // glGetShaderiv       ( fragment_shader, GL_COMPILE_STATUS, &compiled );
    // if ( !compiled )
    // {
    //     string512 buffer;
    //     glGetShaderInfoLog  ( fragment_shader, sizeof ( buffer ), nullptr, buffer );
    //     LOGGER( "! Shader compilation error [fragment_shader]: %s", buffer );
    // }

    using namespace inex::render_ogl;
    shader v( enum_shader_type_vertex, "vertex_shader.glsl" ),
    f( enum_shader_type_fragment, "fragment_shader" );
    v.compile( );
    f.compile( );
    // v.create    ( );

    // shader fragment_shader ( enum_shader_type_fragment, "fragment_shader" );
    // fragment_shader.compile( );  

    // // shader program
    // u32 shader_program  = glCreateProgram( );
    // glAttachShader      ( shader_program, vertex_shader.m_object );
    // glAttachShader      ( shader_program, fragment_shader.m_object );
    // glLinkProgram       ( shader_program );

    // s32 compiled        ;
    // glGetShaderiv       ( shader_program, GL_LINK_STATUS, &compiled );
    // if ( !compiled )
    // {
    //     string512 buffer;
    //     glGetShaderInfoLog  ( shader_program, sizeof ( buffer ), nullptr, buffer );
    //     LOGGER( "! Shader linking error: %s", buffer );
    // }


    // glDeleteShader      ( vertex_shader );
    // glDeleteShader      ( fragment_shader );

    glVertexAttribPointer       
    (
                                0, // layout (location  = 0 )
                                3,
                                GL_FLOAT,
                                GL_FALSE,
                                3 * sizeof ( float ),
                                ( pvoid ) 0
    );
    glEnableVertexAttribArray   ( 0 );

    glfwSetFramebufferSizeCallback  ( m_context, framebuffer_size_callback );
    glViewport			( 0, 0, m_width, m_height );
    // glUseProgram        ( shader_program );
        s32 compiled;
   // shader program
    u32 m_shader_program  = glCreateProgram( );
    glAttachShader      ( m_shader_program, v.m_object );
    glAttachShader      ( m_shader_program, f.m_object );
    glLinkProgram       ( m_shader_program );
    glDeleteShader      ( v.m_object );
    glDeleteShader      ( f.m_object );

    glGetShaderiv       ( m_shader_program, GL_LINK_STATUS, &compiled );
    if ( !compiled )
    {
        string512 buffer    = { };
        glGetShaderInfoLog  ( m_shader_program, sizeof ( buffer ), nullptr, buffer );
        if ( *buffer != 0 ) 
        {
            LOGGER( "! Shader linking error: %s", buffer );
        }
    }

    glUseProgram        ( m_shader_program );

}

void    device::create ( )
{
}

void    device::destroy ( )
{
    memory::ie_delete   ( m_render_device );
    glfwTerminate		( );
}

void    device::process_input ( )
{
    if ( glfwGetKey( m_context, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
    {
        glfwSetWindowShouldClose( m_context, 1 );
    }
}

void    device::render ( )
{
    // drawcalls
    glClearColor(               .2f, .3f, .3f, 1.0f     );
    glClear(                    GL_COLOR_BUFFER_BIT     );

    glDrawArrays(               GL_TRIANGLES, 0, 3      );

    // call events and swap buffers
    glfwPollEvents	( );
    glfwSwapBuffers	( m_context );
}

void    update_world ( )
{
    printf( "update_world\n" );
                                    // 5 px for 1 frame // (~1 second)
    // float some_movement             = 5 * m_delta;
}

float round(float f) {
    double t = (double)f + 6755399441055744.0;
    return (float)*((int *)(&t));
}

float   get_time   ( )
{
    // these returns epoch time
    // timespec            spec;
    // clock_gettime       ( CLOCK_PROCESS_CPUTIME_ID, &spec );
    // return              spec.tv_sec + ( spec.tv_nsec / 1.0e6 );

    // tms tm;
    // clock_t time            = times(&tm);
    // long res                = sysconf(_SC_CLK_TCK);
    // double f                = ( (float)time/(float)res );
    return                  ( float )clock( ) / ( float )CLOCKS_PER_SEC;
}

/***
*
* void engine_device::run ( )
*
* m_delta makes the changing of game time for game logic, rendering etc
* regardless of the frame rate. if game's on 30 fps, some_movement
* will be 150 per sec. if it's 60, some_movement will move 2 times slower
* (2.5 per frame)
*
****************************************************/

void    device::run ( )
{
    while ( !glfwWindowShouldClose( m_context ) )
    {
        process_input   ( );
        render          ( );
    }

    // float last_frame_time               = get_time( );
    // for ( ; ; )
    // {
    //     float current                   = get_time( );
    //     float delta                     = current - last_frame_time;
    //     printf (    "last frame: %f; current: %f; delta: %f",
    //     last_frame_time, current, delta );
    //     // process input;
    //     // update ( delta )
    //     // render ( )
    //     // sleep ( 10 );
    //     last_frame_time                 = current;
    // }









// #   define NS_IN_S                  1E9
//     s32 const frames_per_second     = 25,
//         skip_ticks                  = 1000 / frames_per_second;
//     u32 application_active          = 1;
//     timespec delta_pack             ;
//     ASSERT_S( !clock_gettime                   ( CLOCK_PROCESS_CPUTIME_ID, &delta_pack ) );
//     u64 next_game_tick              = delta_pack.tv_sec + delta_pack.tv_nsec / NS_IN_S;
//     s32 sleep_time                  = 0;
//     printf( "next_game_tick:\t%d\n", next_game_tick );

//     while ( application_active )
//     {
//         update_world                ( );
//         // render_wordl                ( );

//         next_game_tick              += skip_ticks ;
//         printf( "next_game_tick:\t%d; ", next_game_tick );
//                                                     // clock_monotonic
//         ASSERT_S( !clock_gettime                   ( CLOCK_PROCESS_CPUTIME_ID, &delta_pack ) );
//         sleep_time                  = next_game_tick - ( delta_pack.tv_sec + delta_pack.tv_nsec / NS_IN_S );
//         printf( "sleepTime:\t%d\n", sleep_time );
//         if ( sleep_time >= 0 )
//         {
//             sleep                   ( sleep_time / 1000 /* / 1000 */ );
//         }

//         if ( sleep_time > 300 ) exit( 1 );

    //}
}

} // namespace ogl
} // namespace engine
