////////////////////////////////////////////////////////////////////////////
//	Created 	: 21.08.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef SHADERS_H_INCLUDED
#	define SHADERS_H_INCLUDED

#	include <inex/render/gl4/gl4_external.h>

namespace inex  {
namespace render_ogl   {

enum    enum_shader_type
{
    enum_shader_type_vertex     = GL_VERTEX_SHADER,
    enum_shader_type_geometry   = GL_GEOMETRY_SHADER,
    enum_shader_type_fragment   = GL_FRAGMENT_SHADER, // analog of D3D's pixel shader
	enum_shader_type_tesselation
}; // enum enum_shader_type

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

						shader			( )	= default;

						shader          ( enum_shader_type type, pcstr path, bool auto_compilation = 1 );
inline	void			create			( enum_shader_type type, pcstr path, bool auto_compilation = 1 )	{ m_type = type; m_source = path; if ( auto_compilation ) compile( ); }
        void            destroy         ( ) ;
		void			compile			( )	;
        void            check_errors    ( ) ;

inline  u32             self            ( ) {   return m_object;    }
inline	void			set_uniform1f	( float const value )	{	/*check if shader active active*/ glUniform1f( m_object, value );	}


private:
    pcstr               m_source			;
    u32                 m_object			;
    enum_shader_type    m_type				;
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

		void			validate		( );
inline  void            create          ( )                 {   m_shader_program    = glCreateProgram( );                   }
inline  void            use             ( )                 {   glUseProgram        ( m_shader_program );                   }
inline  void            unbind          ( )                 {   glUseProgram        ( 0u );                                 }
inline  s32             find_attribute  ( pcstr attribute ) {   return  glGetAttribLocation( m_shader_program, attribute ); }
inline  s32             find_unifrom    ( pcstr uniform )   {   s32 result = glGetUniformLocation( m_shader_program, uniform ); VERIFY( result != -1 ); return result;	}   
// To do: behave different when it's shader or u32 metaprogrammingly
        template < typename T, typename... Args >
inline  void            attach          ( T t, Args ... args )
                        {
                            static_assert   ( helper< T >::value, "expected shader object" );
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
                            static_assert   ( helper< T >::value, "expected shader object" );
                            glAttachShader  ( m_shader_program, t.self( ) );
                        }

private:
    u32                 m_shader_program                    ;
}; // class shader_program

} // namespace render_ogl
} // namespace

#endif // #ifndef SHADERS_H_INCLUDED
