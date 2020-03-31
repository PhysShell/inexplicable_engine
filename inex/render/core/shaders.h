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

//------------------------------------------------
class shader
{
public:
inline                  shader          ( shader const& right ) : 
                        m_object        ( right.m_object ),
                        m_source        ( right.m_source ),
                        m_type          ( right.m_type )
                        {
                        }

                        shader          ( enum_shader_type type, pcstr path );
        void            create          ( ) ;
        void            destroy         ( ) ;
        void            compilev        ( pcstr ) ; void compilef( pcstr); void compile();
        void            check_errors    ( ) ;
        // void            use             ( ) {     glUseProgram        ( m_shader_program ); }
        void            load_vs_and_fs  ( pcstr vsp, pcstr fsp );
inline  u32             self            ( ) {   return m_object;    }
private:
    pcstr               m_source           ;
    u32                 m_object;
    enum_shader_type    m_type             ;
}; // class shader

//------------------------------------------------
class shader_program
{
public:

//         template < >
// inline  void            attach_helper < u32 >  ( u32 t )
//                         {
//                             glAttachShader( m_shader_program, t );
//                         }

        void            link            ( );
        void            check_errors    ( );

inline  void            create          ( )
                        {
                            m_shader_program    = glCreateProgram( );
                        }
inline  void            use             ( )
                        {
                            glUseProgram        ( m_shader_program );
                        }
inline  void            unbind          ( )
                        {
                            glUseProgram        ( 0u );
                        }
inline  s32             find_attribute  ( pcstr attribute )
                        {
                            return              glGetAttribLocation( m_shader_program, attribute );
                        }
// To do: behave different when it's shader or u32 metaprogrammingly
        template < typename T, typename... Args >
inline  void            attach          ( T t, Args ... args )
                        {
                            static_assert   ( helper< T >::value, "Incorrect arguments" );
                            glAttachShader  ( m_shader_program, t.self( ) );
                            // t.destroy( ) ???
                            attach          ( args ... );
                        }

private:
    template < typename T > struct helper               {   enum { value = 0 }; };
    template < >            struct helper  < shader >   {   enum { value = 1 }; };
    template < typename T >
inline  void            attach   ( T t )
                        {
                            static_assert   ( helper< T >::value, "Incorrect arguments" );
                            glAttachShader  ( m_shader_program, t.self( ) );
                        }

    u32                 m_shader_program                    ;
}; // class shader_program

} // namespace render_ogl
} // namespace

#endif // #ifndef SHADERS_H_INCLUDED
