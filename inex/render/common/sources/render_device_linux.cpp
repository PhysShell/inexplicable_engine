#include "pch.h"
#include <inex/render/common/sources/render_device.h>
#include <inex/render/ogl/ogl_extensions.h>
#include <inex/3rd_patry/include/GLFW/glfw3.h>


namespace inex {
namespace render {

static
window_impl* temp;

void    render_device::create_helper ( window_impl*&   window,
                                u32     const&  width,
                                u32     const&  height )
{
    constexpr pcstr window_title        = "inex";
    LOGGER( "- [render]\t: starting render device" );
    // window_impl* temp;
    temp		        = glfwCreateWindow( width, height, window_title, nullptr, nullptr );
    LOGGER( "* '%s' window: initial config: [%d x %d]", window_title, width, height );
    ASSERT_D            ( temp, "Couldn't create window and its OpenGL context." );
    glfwMakeContextCurrent( temp );
    ogl::dump_user_specifications ( );
    ASSERT_D            ( ogl::init_extensions( ), "Failed to load OpenGL extensions\n") ;
    #pragma todo( "PhysShell: is glew really neccessary?")
    // GLenum err          = glewInit();
    // glGetError          ( );
    // ASSERT_S            ( err == GLEW_OK );
    window              = temp;
}

void    render_device::init_draw ( )
{
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

    // vertex shader
    // 4th attribute aPos.w is for perspective division 
    u32 vertex_shader   = glCreateShader( GL_VERTEX_SHADER );
    const GLchar*       vertex_shader_source = ( GLchar* )"#version 330 core"
    "layout (location=0) in vec3 aPos;"
    // we're setting position through gl_position var for next step
    "void main() {gl_Position         = vec4(aPos.x,aPos.y,aPos.z,1.0); }";
    glShaderSource      ( vertex_shader, 1, &vertex_shader_source, nullptr );
    glCompileShader     ( vertex_shader );

    s32 compiled        ;
    glGetShaderiv       ( vertex_shader, GL_COMPILE_STATUS, &compiled );
    if ( !compiled )
    {
        string512 buffer;
        glGetShaderInfoLog  ( vertex_shader, sizeof ( buffer ), nullptr, buffer );
        LOGGER( "* [shader][error]\t: failed to compile \"%s\"", buffer );
    }

    // fragment shader
    u32 fragment_shader;
    const GLchar*   fragment_shader_source = ( GLchar* )"./fragment_shader";
    fragment_shader     = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource      ( fragment_shader, 1, &fragment_shader_source, NULL );
    glCompileShader     ( fragment_shader );

    // shader program
    u32 shader_program  = glCreateProgram( );
    glAttachShader      ( shader_program, vertex_shader );
    glAttachShader      ( shader_program, fragment_shader );
    glLinkProgram       ( shader_program );

    glGetShaderiv       ( shader_program, GL_LINK_STATUS, &compiled );
    if ( !compiled )
    {
        string512 buffer;
        glGetShaderInfoLog  ( vertex_shader, sizeof ( buffer ), nullptr, buffer );
        LOGGER( "* [shader][error]\t: failed to link \"%s\"", buffer );
    }

    glUseProgram        ( shader_program );
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

    draw                        ( );

}

void    render_device::draw ( )
{
    // drawcalls
    glClearColor    ( .2f, .3f, .3f, 1.0f );
    glClear         ( GL_COLOR_BUFFER_BIT );

    // call events and swap buffers
    glfwPollEvents	( );
    glfwSwapBuffers	( temp );
}

// void    render_device::destroy ( )
// {
// }

// void    render_device::render ( )
// {
// }

} // namespace render
} // namespace engine
