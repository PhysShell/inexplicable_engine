#ifndef VISUAL_H_INCLUDED
#	define VISUAL_H_INCLUDED

#	include <inex/3rd_patry/include/GLFW/glfw3.h>
#	include <inex/extensions.h>
#	include <inex/render/base/world.h>
#	include <inex/render/base/visual.h>
#	include <inex/render/core/shaders.h>
//#	include <inex/render/common/sources/res_shader.h>
//#	include <inex/render/base/common_types.h>
//#	include <inex/ogf.h>

namespace inex {

namespace collision {
	struct geometry;
} // namespace collision

namespace render {

struct vertex_colored
{
	math::float3	position;
	u32				color;
}; 

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
		//m_program.validate	( );
#	endif // #if defined _DEBUG
		glBindVertexArray	( index_buffer_id );
		glDrawArrays		( GL_TRIANGLES, 0, 3 );
		//m_program.unbind	( );
	}
	virtual render_mesh* mesh			( )	{ return this; }
	// virtual render_mesh* mesh()	{ return dynamic_cast< render_mesh * > ( this ); }

	//virtual	void	recalculate_memory_usage_impl ( ) { m_memory_usage_self.unmanaged = get_size(); }

}; //class simple_visual

class triangle_primitive_visual :	public render_mesh, 
									public render_visual
{
	typedef render_visual				super;
public:
	virtual				~triangle_primitive_visual		( ) { }
	virtual		void	load							( math::float4x4 const& vertices )
				{
					m_vertices				= vertices;

					glGenBuffers			( 1 , &vertex_buffer_id );
					glBindBuffer			( GL_ARRAY_BUFFER, vertex_buffer_id );
					glBufferData			( GL_ARRAY_BUFFER, sizeof ( vertices.elements ), vertices.elements, GL_STATIC_DRAW );
					glBindBuffer			( GL_ARRAY_BUFFER, 0 );

					LOGGER					( 
						"* [Loading VB] %d verts, %d KiB", 
						sizeof( vertices.elements ) / sizeof ( float ), 
						sizeof ( vertices.elements ) / 1024 
					);

					glGenVertexArrays		( 1, &index_buffer_id );
					glBindVertexArray		( index_buffer_id );
					glEnableVertexAttribArray ( 0 );
					glBindBuffer			( GL_ARRAY_BUFFER, index_buffer_id );
					glVertexAttribPointer	( 0, 4, GL_FLOAT, GL_FALSE, 0, nullptr );
				}

			void						prologue	( )	{ m_program.use( ); glBindVertexArray( index_buffer_id ); }
			void						epilogue	( ) { m_program.unbind( ); }
			void						draw_static	( ) { glDrawArrays ( GL_TRIANGLES, 0, 3); }


	render_ogl::shader_program& get_shader_program ( )	{ return m_program; };

	virtual		void	render							( ) { }
	virtual render_mesh* mesh							( )	{ return this; }	

private:
	math::float4x4	m_vertices;

}; // class triangle_primitive_visual



} // namespace render 
} // namespace inex 


#endif //VISUAL_H_INCLUDED