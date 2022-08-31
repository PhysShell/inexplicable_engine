#pragma once
#include <inex/render/core/quasi_singleton.h>
#include <inex/render/core/vertex_colored.h>
#include <inex/render/gl4/sources/renderer_context.h>
#include <vector>

namespace inex {
namespace render {

//typedef math::rectangle< math::float2 >	viewport_type;
	struct viewport_type { };
class system_renderer : public  quasi_singleton<system_renderer>
{
public:

public:
	typedef std::vector< vertex_colored >	colored_vertices_type;
	typedef std::vector< u16 >				colored_indices_type;

public:
	system_renderer	( renderer_context * renderer_context);
	~system_renderer();

	//untyped_buffer * create_quad_ib();
	
	void set_w	( math::float4x4 const& m ) { m_renderer_context->set_w( m ); }	
	void set_v	( math::float4x4 const& m ) { m_renderer_context->set_v( m ); }	
	void set_p	( math::float4x4 const& m ) { m_renderer_context->set_p( m ); }	

	math::float4x4 const& get_w	( )	const	{ return m_renderer_context->get_w( ); }
	math::float4x4 const& get_v	( )	const	{ return m_renderer_context->get_v( ); }
	math::float4x4 const& get_p	( )	const	{ return m_renderer_context->get_p( ); }
	
	void setup_scene_view			( scene_view_ptr view_ptr);
	void setup_render_output_window	( render_output_window_ptr output_window, viewport_type const& viewport);
	
	void draw_lines				(
		vertex_colored const* const vertices_begin,
		vertex_colored const* const vertices_end,
		u16 const* const indices_begin,
		u16 const* const indices_end,
		bool covering_effect = false
	);
	void draw_triangles			(
		vertex_colored const* const vertices_begin,
		vertex_colored const* const vertices_end,
		u16 const* const indices_begin,
		u16 const* const indices_end,
		bool covering_effect = false
	);
	//void draw_screen_lines		( inex::math::float3 const* points, u32 count, math::color const& color, float width, u32 pattern, bool use_depth, bool is_screen_space_coord);
	//void draw_3D_point			( inex::math::float3 const& position, float width, math::color const& color, bool use_depth);
	//void draw_aabb				( math::aabb const& aabb, math::color const& color);
	//void draw_obb				( math::float4x4 const& transform, math::color const& color);
	//void setup_grid_render_mode	( u32 grid_density );
	//void remove_grid_render_mode( );
	//
	//void setup_rotation_control_modes ( bool color_write);
	//
	//void draw_ui_vertices		( vertex_formats::TL const * vertices, u32 const & count, int prim_type, int point_type );
	//
	//void set_model_ghost_mode			( polymorph_vector_base<render_model_instance> const& render_models, bool value);
	//
	//void draw_ghost_render_models		( render_surface_instances& render_models);
	//void draw_render_models_selection	( render_surface_instances& render_models);
	//void draw_system_render_models		( render_surface_instances const& render_models);
	//void draw_debug_terrain				( );
	//void draw_particle_system_instance_selections ( render::vector<particle::particle_system_instance_ptr> const& instances);
	//void draw_speedtree_instance_selections ( render::vector<render::speedtree_instance_ptr> const& instances);
	//
	//void set_selection_parameters		( inex::math::float4 selection_color, float selection_rate );
	
	
private:
	//inex::render::material_effects_instance_cook_data* m_cook_data_to_delete;
	//bool is_effects_ready				() const;

	//typedef inex::render::map<render_model_instance*, material_effects> render_model_to_material_type;
	// render_model_to_material_type m_render_model_to_material;
	//
	math::float4		m_selection_color;
	float				m_selection_rate;
	math::float4		m_current_selection_color;
	math::float4		m_ghost_model_color;
	
	//void on_material_loaded (inex::resources::queries_result& result);
	//material_effects_instance_ptr m_terrain_debug_material;
	//material_effects		m_terrain_debug_material_effects;
	
	renderer_context*		m_renderer_context;
	
	// system line
	//ref_effect				m_sh_sl;
	//ref_geometry			m_colored_geom_sl;
	//shader_constant_host*	m_WVP_sl;
	//shader_constant_host*	m_c_start_corner;
	//
	//vertex_buffer			m_vertex_stream;
	//index_buffer			m_index_stream;

	//ref_effect				m_sh_particle_selection;
	//ref_effect				m_sh_vcolor;
	//ref_effect				m_sh_grid_25;
	//ref_effect				m_sh_grid_50;
	//ref_effect				m_sh_ui;
	//ref_effect				m_notexture_shader;
	//ref_effect				m_editor_selection_shader[num_vertex_input_types];
	//ref_effect				m_speedtree_selection_shader;
	//ref_effect				m_editor_model_ghost_shader;
	//
	//
	//ref_geometry			m_colored_geom;
	//ref_geometry			m_grid_geom;
	//ref_geometry			m_ui_geom;
	//ref_texture				m_grid_texture_25;
	//ref_texture				m_grid_texture_50;
	//
	//ref_state				m_rotation_mode_states[2];
	//
	//bool					m_grid_mode;
	//float					m_grid_density;
	//shader_constant_host*	m_grid_density_constant;
	//
	//bool					m_color_write;
	//u32						m_rotation_mode_ref_value;
}; // class system_renderer

} // namespace render
} // namespace inex