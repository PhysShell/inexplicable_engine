#include "pch.h"
#include <inex/render/core/shaders.h>
#include <inex/fs_utils.h>
#include <inex/core/sources/ie_memory.h>
#include <inex/core/sources/fs_file_system_internal.h>
#include <inex/core/sources/ie_trims.h>

namespace inex  {
namespace render_ogl   {

shader::shader ( enum_shader_type type, pcstr path, bool auto_compilation ) :
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
    memory::reader timestamp ( src.m_data, strlen( src.m_data ) );
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
    if ( 0 == compiled_successfully ) {
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
    if ( 0 == compiled ) {
        string512 buffer    = { };
        glGetShaderInfoLog  ( m_shader_program, sizeof ( buffer ), nullptr, buffer );
        ASSERT_D( 0 == *buffer, "Shader linking failed: %s", buffer );
    } else { LOGGER( " linked successfully" ); }
}

void	shader_program::validate ( )
{
	glValidateProgram	( m_shader_program );
	s32 params			= -1;
	glGetProgramiv		( m_shader_program, GL_VALIDATE_STATUS, &params );
	LOGGER				("program %i GL_VALIDATE_STATUS = %i\n", m_shader_program, params);
	if (GL_TRUE != params)
		ASSERT_S( !"SHADER INVALIDATION" );

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


} // namespace render_ogl
} // namespace


