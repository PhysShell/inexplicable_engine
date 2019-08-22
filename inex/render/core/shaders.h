////////////////////////////////////////////////////////////////////////////
//	Created 	: 21.08.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef SHADERS_H_INCLUDED
#   define SHADERS_H_INCLUDED

#   include <inex/types.h>
#   include <inex/render/ogl/ogl_extensions.h>

namespace inex  {
namespace render_ogl   {

enum    enum_shader_type
{
    enum_shader_type_vertex     = GL_VERTEX_SHADER,
    enum_shader_type_geometry   = GL_GEOMETRY_SHADER,    
    enum_shader_type_fragment   = GL_FRAGMENT_SHADER // analog of D3D's pixel shader
}; // enum enum_shader_type

void fsf ( );

class shader
{
public:
                        shader          ( enum_shader_type type, GLchar* const path );
        void            create          ( ) ;
        void            destroy         ( ) ;
        void            compilev         ( const GLchar* ) ; void compilef( const GLchar*); void compile();
        void            check_errors    ( ) ;
        // void            use             ( ) {     glUseProgram        ( m_shader_program ); }
        void            load_vs_and_fs  ( const GLchar* vsp, const GLchar* fsp );
// inline  u32&            self            ( ) {   return m_object;    }
public:
    GLchar              *m_source           ;
    u32                 m_object;
    enum_shader_type    m_type              ;
}; // class shader

} // namespace render_ogl
} // namespace

#endif // #ifndef SHADERS_H_INCLUDED