#include "pch.h"

#include <inex/core/sources/ie_memory.h>
#include <inex/render/core/device.h>
#include <inex/render/common/sources/render_device.h>
#include <inex/render/ogl/ogl_extensions.h>
#include <inex/3rd_patry/include/GLFW/glfw3.h>
#include <inex/render/core/shaders.h>

#include <time.h>
#include <math.h>
#include <vector>

static
void    framebuffer_size_callback ( window_impl* window, int width, int height )
{
    glViewport          ( 0, 0, width , height  ); // 1st and 2nd are bottom left coordinate system origin. 'w' and 'h' are the other point and they served for building rectangle
}

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace inex {
namespace ogl {

// namespace render            = inex::render_ogl;

constexpr const float           vertex_positions        [ ] =
{
	0.25f,  0.25f, 0.0f, 1.0f,
	0.25f, -0.25f, 0.0f, 1.0f,
   -0.25f, -0.25f, 0.0f, 1.0f,
};

u32                             vertex_array_object     ;
u32                             vertex_buffer_object    ;
render_ogl::shader_program      program                 ;
s32                             offset_uniform          ;
s32                             elapsed_time_uniform    ;
s32                             loop_duration_uniform   ;

void    compute_positions_offsets ( float& x_offset, float& y_offset )
{
    float const loop_duration   = 1.f;
                                // unit circle formula (r=1)
    float const scale           = 3.14159f * 2.f / loop_duration;

    float elapsed_time          = glfwGetTime( );
    float current_time_loop     = fmodf( elapsed_time, loop_duration );

    x_offset                    = cosf( current_time_loop * scale ) * .5f;
    y_offset                    = sinf( current_time_loop * scale ) * .5f;       
}

void    adjust_vertex_data ( float const x_offset, float const y_offset )
{
    std::vector< float > update ( vertex_positions, vertex_positions + ARRAY_COUNT( vertex_positions ) );
    // memcpy                      ( &update[ 0 ], vertex_positions, sizeof( vertex_positions ) );

    for( int vertex = 0; vertex < ARRAY_COUNT( vertex_positions ); vertex += 4 )
    {
        update[ vertex ]        += x_offset;
        update[ vertex + 1 ]    += y_offset;
    };

    glBindBuffer                ( GL_ARRAY_BUFFER, vertex_buffer_object );
    glBufferSubData             ( GL_ARRAY_BUFFER, 0, sizeof( vertex_positions ), &update[ 0 ] );
    glBindBuffer                ( GL_ARRAY_BUFFER, 0 );

}

void    initialize_shaders ( )
{
    LOGGER              ( "\tinitializing shaders" );           // TODO: make shader append gamedata/shaders!
    render_ogl::shader f( render_ogl::enum_shader_type_vertex, "gamedata/shaders/calc_offset.vs" ),
                       v( render_ogl::enum_shader_type_fragment, "gamedata/shaders/calc_color.fs" );
    program.create      ( );
    program.attach      ( v, f );
    program.link        ( );

    elapsed_time_uniform        = program.find_unifrom( "time" );
    loop_duration_uniform       = program.find_unifrom( "loopDuration" );
    s32 frag_loop_uniform       = program.find_unifrom( "fragLoopDuration" );

    program.use         ( );
    glUniform1f         ( loop_duration_uniform, 5.f );
    glUniform1f         ( frag_loop_uniform, 10.f );
    program.unbind      ( );

    v.destroy           ( );
    f.destroy           ( );
}

void    initialize_vertex_buffer_object ( )
{
    LOGGER              ( "\tinitializing vbo" );
    glGenBuffers        ( 1,                &vertex_buffer_object );                                          // create ptr on ogl
    glBindBuffer        ( GL_ARRAY_BUFFER,  vertex_buffer_object );                                           // say 'we'll affect target with 2nd arg
    glBufferData        ( GL_ARRAY_BUFFER,  sizeof ( vertex_positions ), vertex_positions, GL_STREAM_DRAW );  // finally allocate the mem of sizeof for 'vertex_positions'
    glBindBuffer        ( GL_ARRAY_BUFFER,  0u );                                                             // undo, unnecessary as next bind call will do it but it makes me comfortable
}

void    device::initialize ( )
{
    LOGGER( "initializing engine...");
    VERIFY( glfwInit( ) );
    m_render_device     = memory::ie_new< render::render_device >( );
    glfwWindowHint		( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint		( GLFW_CONTEXT_VERSION_MINOR, 0 );
    glfwWindowHint		( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    m_width             = 480;
    m_height            = 640;

    LOGGER              ( "starting render device..." );
    m_context		        = glfwCreateWindow( m_width, m_height, "__INEX__", nullptr, nullptr );
    LOGGER              ( "* '%s' window: initial config: [%d x %d]", "__INEX__",  m_width, m_height );
    ASSERT_D            ( m_context, "Couldn't create window and its OpenGL context." );
    glfwMakeContextCurrent( m_context );
    ogl::dump_user_specifications ( );
	bool success		= ogl::init_extensions( );
    ASSERT_D            ( success , "Failed to load OpenGL extensions\n") ;

    glfwSetFramebufferSizeCallback          ( m_context, framebuffer_size_callback );

    initialize_shaders                      ( );
    initialize_vertex_buffer_object         ( );

    glGenVertexArrays                       ( 1, &vertex_array_object );
    glBindVertexArray                       ( vertex_array_object );

    // glViewport			                    ( 0, 0, m_width, m_height );
}

void    device::render ( )
{
    float x_offset              = .0f;
    float y_offset              = .0f;
    compute_positions_offsets   ( x_offset, y_offset );

    glClearColor                ( .0f, .0f, .0f, .0f );
    glClear                     ( GL_COLOR_BUFFER_BIT );

    program.use                 ( );
    
    glUniform1f                 ( elapsed_time_uniform, glfwGetTime( ) );

    glBindBuffer                ( GL_ARRAY_BUFFER, vertex_buffer_object );
    glEnableVertexAttribArray   ( 0 );                             
    glVertexAttribPointer       ( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );

    glDrawArrays                ( GL_TRIANGLES, 0, 3 );

    glUniform1f                 ( loop_duration_uniform, 2.5f );

    glDrawArrays                ( GL_TRIANGLES, 0, 3 );

    glUniform1f                 ( loop_duration_uniform, 5.f );
    
    glDisableVertexAttribArray  ( 0 );
    program.unbind              ( );

    glfwSwapBuffers             ( m_context );
    glfwPollEvents              ( );
}

void    device::create ( )
{
}

void    device::destroy ( )
{
    LOGGER              ( "- [render]\t: destroying" );
    memory::ie_delete   ( m_render_device );
    // glBindVertexArray   ( 0u );
    glfwTerminate		( );
}

void    device::process_input ( )
{
    if ( glfwGetKey( m_context, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
    {
        glfwSetWindowShouldClose( m_context, 1 );
    }
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


    // glBindBuffer        ( GL_ELEMENT_ARRAY_BUFFER, element_buffer_object );

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


    // glBindVertexArray   ( vertex_array_object );

//     s32 compiled;
//     shader program

//     printf( "Code: %d %d\n", vs, fs  );
//     u32 m_shader_program  = glCreateProgram( );
//     glAttachShader      ( m_shader_program, vs );
//     glAttachShader      ( m_shader_program, fs );
//     glLinkProgram       ( m_shader_program );
//     glDeleteShader      ( vs );
//     glDeleteShader      ( fs );

//     glGetShaderiv       ( m_shader_program, GL_LINK_STATUS, &compiled );
//     if ( !compiled )
//     {
//         string512 buffer    = { };
//         glGetShaderInfoLog  ( m_shader_program, sizeof ( buffer ), nullptr, buffer );
//         if ( *buffer != 0 )
//         {
//             LOGGER( "! Shader linking error: %s", buffer );
//         }
//     }

//     glUseProgram        ( m_shader_program );
