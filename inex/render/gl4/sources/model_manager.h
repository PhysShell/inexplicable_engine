#ifndef MODEL_MANAGER_H_INCLUDED
#	define MODEL_MANAGER_H_INCLUDED

#	include <inex/extensions.h>
#	include <inex/render/common/sources/res_shader.h>
#	include <inex/render/gl4/sources/visual.h>

#	include <vector>

namespace inex {
	namespace resources {
		struct managed_resource_ptr
		{
			math::float4x4	m_vertices;
			pcstr			vs;
			pcstr			fs;
		}; // class manager_resource_ptr
	} // namespace resources

namespace memory		{ using chunk_reader	= reader ; }

namespace render {
	using math::float3;
	using math::float4x4;

		
class model_manager
{
public:
	model_manager():
		m_view_point(0, 0, 0),
		m_marker				(u32(-1)),
		m_draw_game				(true),
		m_draw_editor			(true)

	{}

	~model_manager()			= default;

	void clear_resources		( );

	void init();
								// resource_base is derived from intrusive_ptr to do ref-counting, managed resource 
	virtual	void add_static		(resources::managed_resource_ptr const& collision, resources::managed_resource_ptr const& geometry, resources::managed_resource_ptr const& visuals);
								// temporary
	void	load_vertex_buffers	( resources::managed_resource_ptr const& geometry );
	// void	load_index_buffers	( memory::chunk_reader& reader, u32 usage );
	void	load_visuals		( memory::chunk_reader& reader );
	void	load_shaders		(resources::managed_resource_ptr const& geometry );
	// void	load_sectors		( memory::chunk_reader& reader );

	void	render_static		();

	void	update(const float3& new_view_point, const float4x4& wvp_mat);

	inline ref_geometry	create_geom(u32 vb_id, u32 ib_id);

	static render_visual*	create_instance(u16 type);
	static void				destroy_instance(render_visual* v);
	static u16				get_visual_type(memory::chunk_reader& reader);

	u32				create_vb(u32 size, u32 usage, pcvoid data);
	u32				create_ib(u32 size, u32 usage, pcvoid data);
	

public:

	// This will temporary live here
	void			set_draw_editor	( bool value) { m_draw_editor = value;}
	void			set_draw_game	( bool value) { m_draw_game = value;}

	bool			get_draw_editor	(){ return m_draw_editor;}
	bool			get_draw_game	(){ return m_draw_game;}


	typedef std::vector< render_mesh* >		VertexBuffers;
	typedef std::vector< render_visual* >	Visuals;

	Visuals&		get_visuals			( )	{ return m_visuals; }
	VertexBuffers&	get_vertex_buffers	( )	{ return m_vertex_buffers; }

private:
	void dump_visuals(u32 i, render_visual* visual);

private:


	//ref_shader		m_static_shader;
	//ref_shader		m_tree_shader;

	std::vector<render_visual*>	m_visuals_selection;
	float3				m_view_point;
	float4x4			m_mx_form;


	Visuals				m_visuals;

	VertexBuffers	m_vertex_buffers;
	//IndexBuffers	m_index_buffers;
	//Declarators		m_declarators;

	u32 m_marker;

	bool			m_draw_editor;
	bool			m_draw_game;

public:
	//ref_shader		m_test_shader;
}; // class model_manager

} // namespace render
} // namespace inex

#endif // #ifndef MODEL_MANAGER_H_INCLUDED