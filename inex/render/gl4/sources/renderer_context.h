#pragma once

#include <inex/render/base/base_classes.h>
#if INEX_PLATFORM_LINUX
#	include <inex/render/common/scene.h>
#endif // #if INEX_PLATFORM_LINUX
namespace inex {
namespace render {
class scene;
class scene_view;

class renderer_context
{ 
public:
						renderer_context		( );
	
	void				set_scene				( scene * scene );
	scene *				get_scene				( )							{ return m_scene; }
	
	void				set_scene_view			( scene_view_ptr view_ptr );
	scene_view const *	get_scene_view			( )	const;

	void				create_casceded_shadow_map_buffers(u32 shadow_map_size);
	
	//void				set_target_context		( renderer_context_targets const * targets_context);

	void 	set_w			( const math::float4x4& m);
	void 	set_v			( const math::float4x4& m);
#ifndef MASTER_GOLD
	void 	set_culling_v	( const math::float4x4& m);
#endif // #ifndef MASTER_GOLD
	void 	set_p			( const math::float4x4& m);

	void 	set_w_identity	()						{ set_w( math::float4x4().identity());}

	//void 	push_set_w		( const math::float4x4& m) 	{ m_w_stack.push_back( m_w ); set_w( m);}
	//void 	push_set_v		( const math::float4x4& m) 	{ m_v_stack.push_back( m_v ); set_v( m);}
	//void 	push_set_p		( const math::float4x4& m) 	{ m_p_stack.push_back( m_p ); set_p( m);}

	//void 	pop_w			() 						{ set_w( m_w_stack.back()); m_w_stack.pop_back();}
	//void 	pop_v			() 						{ set_v( m_v_stack.back()); m_v_stack.pop_back();}
	//void 	pop_p			() 						{ set_p( m_p_stack.back()); m_p_stack.pop_back();}

	const math::float4x4&		get_w			() const 		{ return m_w;}

#ifndef MASTER_GOLD
	//const math::float4x4&		get_v			() const		{ return m_v_stack.empty() ? m_culling_v : m_v;}
	//const math::float4x4&		get_v_inverted	() const		{ return m_v_stack.empty() ? m_culling_v_inverted : m_v_inverted;}

	//const math::float4x4&		get_culling_v	() const		{ return m_v_stack.empty() ? m_culling_v : m_v;}
	//const math::float4x4&		get_culling_v_inverted () const	{ return m_v_stack.empty() ? m_culling_v_inverted : m_v_inverted;}
#else // #ifndef MASTER_GOLD
	const math::float4x4&		get_v			() const		{ return m_v;}
	const math::float4x4&		get_v_inverted	() const		{ return m_v_inverted;}
	const math::float4x4&		get_culling_v	() const		{ return m_v;}
	const math::float4x4&		get_culling_v_inverted () const	{ return m_v_inverted;}
#endif // #ifndef MASTER_GOLD
	const math::float4x4&		get_v			() const		{ return m_v;}
	const math::float4x4&		get_p			() const		{ return m_p;}
	const math::float4x4&		get_p_inverted	() const		{ return m_p_inverted;}

	float				get_near		() const		{ return m_near_far_invn_invf.x;}
	float				get_far			() const		{ return m_near_far_invn_invf.y;}
	math::float3 const*		get_eye_rays	() 				{ return &m_eye_rays[0];}
	math::float4 const&		get_near_far	() 				{ return m_near_far_invn_invf;}

	const math::float4x4&		get_wv			() const		{ return m_wv;}
	const math::float4x4&		get_vp			() const		{ return m_vp;}
#ifndef MASTER_GOLD
	//const math::float4x4&		get_culling_vp	() const		{ return m_v_stack.empty() ? m_culling_vp : m_vp;}
#else // #ifndef MASTER_GOLD
	const math::float4x4&		get_culling_vp	() const		{ return m_vp;}
#endif // #ifndef MASTER_GOLD
	const math::float4x4&		get_wvp			() const		{ return m_wvp;}

	void				set_view2shadow	( math::float4x4 const & view2shadow, u32 index = 0);
	const math::float4x4&		get_view2shadow	( u32 index = 0) const;

	math::float3 const & 		get_view_pos	() const	{ return m_view_pos.xyz();}
	math::float3 const & 		get_view_dir	() const	{ return m_view_dir.xyz();}

#ifndef MASTER_GOLD
	math::float3 const & 		get_culling_view_pos() const	{ return m_culling_view_pos.xyz();}
	math::float3 const & 		get_culling_view_dir() const	{ return m_culling_view_dir.xyz();}
#else // #ifndef MASTER_GOLD
	math::float3 const & 		get_culling_view_pos() const	{ return m_view_pos.xyz();}
	math::float3 const & 		get_culling_view_dir() const	{ return m_view_dir.xyz();}
#endif // #ifndef MASTER_GOLD
	//	
	//void				set_solid_diffusecolor_specularintensity	( math::float3	color, float specular_intensity );
	//void				set_solid_material_parameters			( float specular_power, float diffuse_power, float tranclucensy, float material_id);
	//void				set_solid_emission_color				( math::float3 emission_color);

	void				reset_matrices	();
	void				update_eye_rays	();

	//u32					get_lighting_material_strtegy	();
	//float				get_shadow_map_z_bias			();

	void				set_time_delta	(float const time_delta) { m_time_delta = time_delta; }
	void				set_current_time(float const current_time) { m_current_time = current_time; }

	float				get_time_delta	() const { return m_time_delta; }
	float				get_current_time() const { return m_current_time; }
	
	math::float4		get_screen_resolution() const { return m_screen_resolution; }
	
public:
	
	//renderer_context_targets const* m_targets;
	
// 	ref_texture			m_t_skin_scattering;
// 	ref_texture			m_t_skin_scattering_small;
// 	ref_texture			m_t_skin_scattering_blurred_0;
// 	ref_texture			m_t_skin_scattering_blurred_1;
// 	ref_texture			m_t_skin_scattering_blurred_2;
// 	ref_texture			m_t_skin_scattering_blurred_3;
// 	ref_texture			m_t_skin_scattering_blurred_4;
	
	//ref_texture			m_t_gbuffer_position_downsampled;
	//ref_texture			m_t_gbuffer_normal_downsampled;

	//ref_texture		m_t_mlaa_edges;
	//ref_texture		m_t_mlaa_blended_weights;

	//fixed_string<128> names[NUM_TONEMAP_TEXTURES];
	//// Textures of render targets. Need to be updated after the targets context changed.
	//ref_texture		m_t_position;
	//ref_texture		m_t_position_ex;
	//ref_texture 	m_t_normal;
	//ref_texture 	m_t_color;
	//ref_texture 	m_t_emissive;
	//ref_texture 	m_t_distortion;
	//ref_texture 	m_t_ssao_accumulator;
	//ref_texture		m_t_ssao_accumulator_small;
	//
	////ref_texture		m_t_accumulator;
	//ref_texture		m_t_accumulator_diffuse;
	//ref_texture		m_t_accumulator_specular;
	//
	//// TODO: Use one big shadow map of all cascades!
	//ref_rt			m_rt_shadow_map[sun_cascade::num_max_sun_shadow_cascades];
	//ref_texture		m_t_shadow_map[sun_cascade::num_max_sun_shadow_cascades];
	//
	//ref_texture		m_t_frame_luminance[NUM_TONEMAP_TEXTURES];
	//ref_texture		m_t_frame_luminance_current;
	//ref_texture		m_t_frame_luminance_previous;
	//ref_texture		m_t_frame_luminance_histogram;
	//	

	////ref_texture		m_t_indirect_lighting;

	//ref_texture		m_t_light_scattering;
	//ref_texture		m_t_present;
	//ref_texture		m_t_generic_0;
	//ref_texture		m_t_generic_1;
	//
	//ref_texture		m_t_blur_0;
	//ref_texture		m_t_blur_1;

	//ref_texture		m_t_tangents;
	//ref_texture		m_t_bitangents;
	//
	//ref_texture		m_t_null;
	//
	//ref_texture		m_t_decals_diffuse;
	//ref_texture		m_t_decals_normal;
	//
	//ref_geometry	m_g_quad_uv;
	//ref_geometry	m_g_quad_2uv;
	//ref_geometry	m_g_quad_eye_ray;
	//
	//untyped_buffer_ptr		m_quad_ib;
	//
	//u32				m_light_marker_id;
	
	float			m_time_delta;
	float			m_current_time;

	//fixed_vector<sun_cascade, sun_cascade::num_max_sun_shadow_cascades>	m_sun_cascades;
	
	//post_process_parameters m_post_process_parameters;
	
	render::scene_view*		get_scene_view			();
	
	//speedtree_forest::tree_render_info_array_type	m_visible_trees;
	
private:

	void			update_near_far();			

	render::scene*	m_scene;
	scene_view_ptr	m_scene_view;

	fixed_vector<math::float4x4, 16>	m_w_stack;
	fixed_vector<math::float4x4, 16>	m_v_stack;
	fixed_vector<math::float4x4, 16>	m_p_stack;

	math::float4x4		m_w;			// local		=> world
	math::float4x4		m_w_transposed;
	math::float4x4		m_v;			// world		=> view
	math::float4x4		m_v_transposed;
	math::float4x4		m_v_inverted;	// view			=> world
	math::float4x4		m_v_inverted_transposed;
	math::float4x4		m_p;			// view			=> projection
	math::float4x4		m_p_transposed;
	math::float4x4		m_p_inverted;	// projection	=> view
	math::float4x4		m_wv;			// local		=> view
	math::float4x4		m_wv_transposed;
	math::float4x4		m_vp;			// world		=> projection
	math::float4x4		m_vp_transposed;
#ifndef MASTER_GOLD
	math::float4x4		m_culling_v;
	math::float4x4		m_culling_v_inverted;
	math::float4x4		m_culling_vp;
#endif // #ifndef MASTER_GOLD
	math::float4x4		m_wvp;			// local		=> projection
	math::float4x4		m_wvp_transposed;

	math::float4x4		m_v2shadow0;	// from view to shadow space transform
	math::float4x4		m_v2shadow1;	// from view to shadow space transform
	math::float4x4		m_v2shadow2;	// from view to shadow space transform
	math::float4x4		m_v2shadow3;	// from view to shadow space transform
	
	//shader_constant_host const * m_c_cascade_shadow_map_size;
	float			m_cascade_shadow_map_size;
	
	math::float4			m_near_far_invn_invf;		// Near, far, 1/near, 1/far retrieved from projection matrix.
	math::float3			m_eye_rays[4];

	math::float4			m_fog_params;
	math::float4			m_screen_resolution;
	math::float4			m_solid_color_specular;
	math::float4			m_solid_material_parameters;
	math::float4			m_solid_emission_color;

	// Used math::float4 for shader constant binding.
	math::float4			m_view_pos;
	math::float4			m_view_dir;

#ifndef MASTER_GOLD
	math::float4			m_culling_view_pos;
	math::float4			m_culling_view_dir;
#endif // #ifndef MASTER_GOLD

	//shader_constant_host const *		m_c_w;
	//shader_constant_host const *		m_c_w_inv;
	//shader_constant_host const *		m_c_v;
	//shader_constant_host const *		m_c_p;
	//shader_constant_host const *		m_c_wv;
	//shader_constant_host const *		m_c_vp;
	//shader_constant_host const *		m_c_wvp;
	//shader_constant_host const *		m_c_v2w;

	//shader_constant_host const *		m_c_near_far;
	//shader_constant_host const *		m_c_fog_params;
	//shader_constant_host const *		m_c_screen_resolution;
	//shader_constant_host const *		m_c_view_pos;
	//shader_constant_host const *		m_c_view_dir;
	//
	//shader_constant_host const *		m_c_solid_color_specular;
	//shader_constant_host const *		m_c_solid_material_parameters;
	//shader_constant_host const *		m_c_solid_emission_color;
	//
	//shader_constant_host const *		m_c_scene_time;
	//
	//u32									m_frame_index;
}; // class renderer_context
} // namespace render
} // namespace inex
