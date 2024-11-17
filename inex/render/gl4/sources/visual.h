#ifndef VISUAL_H_INCLUDED
#	define VISUAL_H_INCLUDED

#	include <inex/extensions.h>
#	include <inex/render/base/world.h>
#	include <inex/render/base/visual.h>
//#	include <inex/render/core/shaders.h>
//#	include <inex/3rd_patry/include/GLFW/glfw3.h>
//#	include <inex/render/common/sources/res_shader.h>
//#	include <inex/render/base/common_types.h>
//#	include <inex/ogf.h>


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

inline  u32             self            ( ) const {   return m_object;    }
inline	void			set_uniform1f	( float const value ) const	{	/*check if shader active active*/ glUniform1f( m_object, value );	}


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
inline  void            create          ( )							{   m_shader_program    = glCreateProgram( );                   }
inline  void            use             ( ) const					{   glUseProgram        ( m_shader_program );                   }
inline  void            unbind          ( ) const					{   glUseProgram        ( 0u );                                 }
inline  s32             find_attribute  ( pcstr attribute ) const	{   return  glGetAttribLocation( m_shader_program, attribute ); }
inline  s32             find_unifrom    ( pcstr uniform ) const		{   s32 result = glGetUniformLocation( m_shader_program, uniform ); VERIFY( result != -1 ); return result;	}
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
    template < typename T >
inline  void            attach   ( T t )
                        {
                            static_assert   ( helper< T >::value, "expected shader object" );
                            glAttachShader  ( m_shader_program, t.self( ) );
                        }

private:
    u32                 m_shader_program                    ;
}; // class shader_program

template < >
struct shader_program::helper  < shader >   { enum { value = 1 }; };

} // namespace render_ogl
} // namespace

namespace inex {

namespace collision {
	struct geometry;
} // namespace collision

namespace render {

struct vertex_colored;

enum enum_flag_visual
{
	enum_flag_visual_managed	= 1,
};

struct render_mesh;

class render_visual : public render::visual
{
public:
										render_visual();
	virtual								~render_visual();

	virtual	void						load					( );
	virtual	void						render					( ) = 0;
	virtual	void						render_selected			( )		{ }
	virtual	collision::geometry const*	get_collision_geometry	( )		{ return nullptr; }
			bool						set_shader				( pcstr vertex_shader_path, pcstr fragment_shader_path )
			{
				m_vshader.create		( render_ogl::enum_shader_type_vertex, vertex_shader_path );
				m_fshader.create		( render_ogl::enum_shader_type_fragment, fragment_shader_path );

				m_program.create		( );
				m_program.attach		( m_vshader, m_fshader );
				m_program.link			( );

				m_vshader.destroy		( );
				m_fshader.destroy		( );

				return					true;
			}

	virtual render_mesh* mesh()	{ return nullptr; }

	u16	type;
	u32	flags;

	render_ogl::shader			m_vshader;
	render_ogl::shader			m_fshader;
	render_ogl::shader_program	m_program;

};//class visual

struct render_mesh : private inex::detail::noncopyable
{
	//res_geometry	geom;

	u32			vertex_buffer_id;
	u32			vertex_base;
	u32			vertex_count;

	u32			index_buffer_id;
	u32			index_base;
	u32			index_count;
	u32			primitive_count;
};//struct mesh

class simple_visual :	public render_mesh,
						public render_visual
{
	typedef render_visual				super;
public:
	virtual			~simple_visual		( ) { }
	virtual	void	load				( ) { }
	virtual	void	render				( )
	{
		//m_program.use		( );
#	if defined _DEBUG
		if (!m_is_verified)
		{
			m_program.validate	( );
			m_is_verified		= true;
		}
#	endif // #if defined _DEBUG
		glBindVertexArray	( index_buffer_id );
		glDrawArrays		( GL_TRIANGLES, 0, 3 );
		//m_program.unbind	( );
	}
	virtual render_mesh* mesh			( )	{ return this; }
	// virtual render_mesh* mesh()	{ return dynamic_cast< render_mesh * > ( this ); }

	//virtual	void	recalculate_memory_usage_impl ( ) { m_memory_usage_self.unmanaged = get_size(); }
private:
	bool			m_is_verified;
}; //class simple_visual

class triangle_primitive_visual :	public render_mesh,
									public render_visual
{
	typedef render_visual				super;
public:
	virtual				~triangle_primitive_visual		( ) { }
	virtual		void	load							( math::float4x4 const& vertices )
				{
					NOT_IMPLEMENTED();
		   float vertices_raw[] = {
        -0.5f, -0.5f, 0.0f, // ����� �������
         0.5f, -0.5f, 0.0f, // ������ �������
         0.0f,  0.5f, 0.0f  // ������� �������   
    };
			//resources::managed_resource_ptr resource;
			//resource.m_vertices	= vertices;
			//resource.fs			= "gamedata/shaders/ogl4.fs";
			//resource.vs			= "gamedata/shaders/ogl4.vs";

					set_shader				("gamedata/shaders/ogl4.vs", "gamedata/shaders/ogl4.fs");

					//auto it							= m_vertex_buffers.rbegin( );
					//temp->mesh( )->vertex_buffer_id	= ( *it )->vertex_buffer_id;
					//temp->mesh( )->index_buffer_id	= ( *it )->index_buffer_id;

					//m_vertices				= vertices;

					glGenVertexArrays		( 1, &index_buffer_id ); // vao
					glGenBuffers			( 1 , &vertex_buffer_id ); // vbo

					glBindVertexArray		( index_buffer_id );

					glBindBuffer			( GL_ARRAY_BUFFER, vertex_buffer_id );
					glBufferData			( GL_ARRAY_BUFFER, sizeof(vertices_raw), vertices_raw, GL_STATIC_DRAW );

					glVertexAttribPointer	( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr );
					glEnableVertexAttribArray ( 0 );

					glBindBuffer			( GL_ARRAY_BUFFER, 0 );

					LOGGER					(
						"* [Loading VB] %d verts, %d KiB",
						sizeof( vertices.elements ) / sizeof ( float ),
						sizeof ( vertices.elements ) / 1024
					);
				}

			void						prologue	( )	{ m_program.use( ); glBindVertexArray( index_buffer_id ); m_is_in_use = true; }
			void						epilogue	( ) { m_program.unbind( ); m_is_in_use = false; }
			void						draw_static	( ) const { ASSERT_D( m_is_in_use, "Visual must be initialized first before calling draw_static()" ); glDrawArrays ( GL_TRIANGLES, 0, 3); }


	render_ogl::shader_program& get_shader_program ( )	{ return m_program; };

	virtual		void	render							( )
						{
							m_program.use();
							glBindVertexArray		(index_buffer_id); // ��������� � ��� ���� ������ ���� VAO, �� ��� ������������� ��������� ��� ������ ��� (�� �� ������� ���, ����� �� ���� ������� ��������������)
							glDrawArrays			(GL_TRIANGLES, 0, 3);
						}
	virtual render_mesh* mesh							( )	{ return this; }

private:
	math::float4x4	m_vertices;
	bool			m_is_in_use;

}; // class triangle_primitive_visual



} // namespace render
} // namespace inex


#endif //VISUAL_H_INCLUDED
