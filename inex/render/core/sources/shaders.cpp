#include "pch.h"
#include <inex/render/core/shaders.h>
#include <inex/fs_utils.h>
#include <inex/core/sources/ie_memory.h>
#include <inex/core/sources/fs_file_system_internal.h>
#include <inex/core/sources/ie_trims.h>

namespace inex  {
namespace render_ogl   {

shader::shader ( enum_shader_type type, pcstr path, u8 auto_compilation ) :
    m_type      { type },
    // m_shader_program    { },
    m_source    { path }
{
    if ( auto_compilation )
        compile ( );
}

void    shader::destroy ( )
{
    glDeleteShader      ( m_object );
}

void    shader::compile ( )
{
    ASSERT_D( !fs::exists( m_source ), "Shader '%s' not found", m_source );
    m_object            = glCreateShader( m_type );
    
    // struct stat file_attributes;
    // stat                    ( m_v_source, &file_attributes );
    // tm * clock              = gmtime( file_attributes.st_ctim );
    logging::put_string ( "* [shader] compiling '");
    logging::put_string ( m_source );
    logging::put_string ( "', author: ");
    //------------------------------------------------
    fs::memory_mapped_file src( m_source );
    fs::reader timestamp ( src.m_data, strlen( src.m_data ) );
    string128 buffer    = { };
    timestamp.r_string  ( buffer, sizeof ( buffer ) );
    LOGGER( "%s ...", buffer + 3 );
    //------------------------------------------------
    glShaderSource      ( m_object, 1, ( const GLchar** )&src.m_data, nullptr );
    glCompileShader     ( m_object );

    check_errors        ( );
}

void    shader::check_errors ( )
{
    s32 compiled_successfully   = 0;
    glGetShaderiv               ( m_object, GL_COMPILE_STATUS, &compiled_successfully );
    if ( 0 == compiled_successfully )
    {
        string512 error_message = { };
        glGetShaderInfoLog      ( m_object, sizeof ( error_message ), NULL, error_message );
        ASSERT_D( 0, "* [shader][error]\t: failed to compile\n\t[log]\t:\t\t\t%s", m_source, *error_message ? error_message : "no log aquired" );
    } else { LOGGER( "* [shader][info]\t: compiled successfully" ); }
}

void    shader_program::link ( )
{
    logging::put_string         ( "* [shaders]\t: linking shaders ... " );
    glLinkProgram               ( m_shader_program );
    check_errors                ( );
    // glDetachShader
}

void    shader_program::check_errors ( )
{
    s32 compiled        ;
    glGetShaderiv       ( m_shader_program, GL_LINK_STATUS, &compiled );
    if ( 0 == compiled )
    {
        string512 buffer    = { };
        glGetShaderInfoLog  ( m_shader_program, sizeof ( buffer ), nullptr, buffer );
        ASSERT_D( 0 == *buffer, "Shader linking failed: %s", buffer );
    } else { LOGGER( " linked successfully" ); }
}

//------------------------------------------------
// void    shader_program::attach ( u32 count, shader* const& _shader, ... )
// {
//     // it differs on parameter seqence
//     shader* implicit_parameter     = _shader;
//     // ++;
//     while ( count -- )
//     {
//         printf( "Attach %p\n", &implicit_parameter->m_object );
//         glAttachShader          ( m_shader_program, implicit_parameter->m_object );
//         --                      implicit_parameter;
//     }
// }

void    shader::compilev ( pcstr path )
{
    // // vertex shader
    // m_vs                = glCreateShader( GL_VERTEX_SHADER );

    // fs::memory_mapped_file src ( path );
    
    // logging::put_string( "*\tCompiling shader [");
    // logging::put_string( path );
    // logging::put_string( "], ");    
    // ;

    // LOGGER( "********\n%s\n**********", src.m_data );

    // glShaderSource      ( m_vs, 1, &src.m_data, nullptr );
    // glCompileShader     ( m_vs );

    // s32 compiled        ;
    // glGetShaderiv       ( m_vs, GL_COMPILE_STATUS, &compiled );
    // if ( !compiled )
    // {
    //     string512 buffer;
    //     glGetShaderInfoLog  ( m_vs, sizeof ( buffer ), nullptr, buffer );
    //     LOGGER( "! Shader compilation error [m_vs.glsl]: %s", buffer );
    // }
}

void    shader::compilef ( const GLchar* path )
{
    // s32 compiled;
    // // fragment shader;
    // m_fs     = glCreateShader( GL_FRAGMENT_SHADER );

    // fs::memory_mapped_file src ( path );
    // logging::put_string( "*\tCompiling shader [");
    // logging::put_string( path );
    // logging::put_string( "], ");    

    // LOGGER( "********\n%s\n**********", src.m_data );

    // glShaderSource      ( m_fs, 1, &src.m_data, nullptr );
    // glCompileShader     ( m_fs );

    // glGetShaderiv       ( m_fs, GL_COMPILE_STATUS, &compiled );
    // if ( !compiled )
    // {
    //     string512 buffer;
    //     glGetShaderInfoLog  ( m_fs, sizeof ( buffer ), nullptr, buffer );
    //     LOGGER( "! Shader compilation error [m_fs]: %s", buffer );
    // }

}

void    shader::load_vs_and_fs ( pcstr vsp, pcstr fsp )
{
    // m_vs                  = glCreateShader( GL_VERTEX_SHADER );
    // m_v_source            = ( GLchar* )"#version 330 core\n"
    // "layout (location=0) in vec3 aPos;"
    // // we're setting position through gl_position var for next step
    // "void main() {gl_Position         = vec4(aPos.x,aPos.y,aPos.z,1.0); }";
    // LOGGER( "********\n%s\n**********", m_v_source );

    // glShaderSource      ( m_vs, 1, &m_v_source, NULL );
    // glCompileShader     ( m_vs );


    // m_fs                  = glCreateShader( GL_VERTEX_SHADER );
    // GLchar * m_f_source   = ( GLchar* )"#version 330 core\nout vec4 Color;void main() {Color= vec4(1.0f,.5f,.9f,1.0f);}";
    // LOGGER( "********\n%s\n**********", m_f_source );
    // glShaderSource      ( m_fs, 1, &m_f_source, NULL );
    // glCompileShader     ( m_fs );

    //     m_shader_program  = glCreateProgram( );
    // glAttachShader      ( m_shader_program, m_vs );
    // glAttachShader      ( m_shader_program, m_fs );
    // //
    // glLinkProgram       ( m_shader_program );

    // s32 compiled;
    // glGetShaderiv       ( m_shader_program, GL_LINK_STATUS, &compiled );
    // if ( !compiled )
    // {
    //     string512 buffer;
    //     glGetShaderInfoLog  ( m_shader_program, sizeof ( buffer ), nullptr, buffer );
    //     LOGGER( "! Shader linking error: %s", buffer );
    // }


}

void    shader::create ( )
{
//     s32 compiled;
//    // shader program
//     m_shader_program  = glCreateProgram( );
//     glAttachShader      ( m_shader_program, m_vs );
//     glAttachShader      ( m_shader_program, m_fs );
//     glLinkProgram       ( m_shader_program );

//     glGetShaderiv       ( m_shader_program, GL_LINK_STATUS, &compiled );
//     if ( !compiled )
//     {
//         string512 buffer;
//         glGetShaderInfoLog  ( m_shader_program, sizeof ( buffer ), nullptr, buffer );
//         LOGGER( "! Shader linking error: %s", buffer );
//     }

    ///glUseProgram        ( m_shader_program );
}

} // namespace render_ogl
} // namespace


