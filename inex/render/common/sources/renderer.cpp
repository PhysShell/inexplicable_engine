#include "pch.h"
#include <inex/render/common/renderer.h>
#include <chrono>
#include <inex/static_cast_checked.h>

#include <inex/render/common/scene.h>
#include <inex/render/common/scene_view.h>
#include <inex/render/gl4/sources/renderer_context.h>

// render stages
#include <inex/render/common/stage_gbuffer.h>
// static statistics m_statistics;

namespace inex {
namespace timing {
class timer
{
public:
    void start					( )
    {
        m_start_time			= std::chrono::steady_clock::now();
        m_is_enabled			= true;
    }
    
    void stop					( )
    {
        m_end_time				= std::chrono::steady_clock::now();
        m_is_enabled			= false;
    }
    
    long long elapsed_ms		( ) const
    {
        std::chrono::time_point<std::chrono::steady_clock> end_time;
        
        if(m_is_enabled)
        {
            end_time				= std::chrono::steady_clock::now();
        }
        else
        {
            end_time				= m_end_time;
        }
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - m_start_time).count();
    }
    
    double elapsed_s			( ) const
    {
        return elapsed_ms() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::steady_clock>	m_start_time;
    std::chrono::time_point<std::chrono::steady_clock>	m_end_time;
	//float												m_time_factor;
    bool												m_is_enabled;
}; // class timer
}// namespace timing
namespace render {

renderer::renderer( renderer_context * renderer_context ):
	m_renderer_context	( renderer_context ),
	m_last_frame_time	( 0.f ),
	m_current_time		( 0.f ),
    m_timer             ( memory::ie_new< timing::timer >( ) )
{
        for ( u32 i = 0; i < m_stages.size( ); ++i)
            m_stages.set_elem                       ( i, nullptr );
  //  	for (stages_type::iterator it=m_stages.begin(); it!=m_stages.end(); ++it)
		//*it = 0;
	
	// TODO: Stages profiling with gpu and cpu timers.
	
	m_stage_debug									= 0;
	m_view_mode_stage								= 0;
	m_present_stage									= 0;
	
	m_stages[(u32)enum_render_stage_type::geometry_pre_pass_render_stage]		= memory::ie_new< stage_gbuffer >					(m_renderer_context, true);
	//m_stages[decals_accumulate_render_stage]		= NEW(stage_decals_accumulate)			(m_renderer_context);
	//m_stages[accumulate_distortion_render_stage]	= NEW(stage_accumulate_distortion)		(m_renderer_context);
	//m_stages[pre_lighting_stage]					= NEW(stage_pre_lighting)				(m_renderer_context);
	//m_stages[sun_shadows_accumulate_render_stage]	= NEW(stage_shadow_direct)				(m_renderer_context);
	//m_stages[sun_render_stage]						= NEW(stage_sun)						(m_renderer_context);
	//m_stages[deferred_lighting_render_stage]		= NEW(stage_lights)						(m_renderer_context, false);
	//m_stages[ambient_occlusion_render_stage]		= NEW(stage_ambient_occlusion)			(m_renderer_context);
	//m_stages[light_propagation_volumes_render_stage]= NEW(stage_light_propagation_volumes)	(m_renderer_context);
	//m_stages[enum_render_stage_type::geometry_render_stage]					= memory::ie_new< stage_gbuffer > (m_renderer_context, false);
	//m_stages[skybox_render_stage]					= NEW(stage_skybox)						(m_renderer_context);
	//m_stages[apply_distortion_render_stage]			= NEW(stage_apply_distortion)			(m_renderer_context);
	//m_stages[clouds_render_stage]					= NEW(stage_clouds)						(m_renderer_context);
	//m_stages[forward_render_stage]					= NEW(stage_forward)					(m_renderer_context);
	//m_stages[lighting_render_stage]					= NEW(stage_lights)						(m_renderer_context, true);
	//m_stages[particles_render_stage]				= NEW(stage_particles)					(m_renderer_context);
	//m_stages[post_process_render_stage]				= NEW(stage_postprocess)				(m_renderer_context);
}

renderer::~renderer ( )
{
    memory::ie_delete   ( m_timer );
}

void renderer::render(	scene_ptr const& in_scene,
						scene_view_ptr const& in_view,
						render_output_window_ptr const& output_window,
						viewport_type const& viewport,
						std::function< void ( bool ) > const& on_draw_scene,
						bool draw_debug_terrain )
{
	//backend::ref().disabled_shader_constansts_set	= s_disabled_shader_constansts_set;
	
	scene*		scene	= static_cast_checked< inex::render::scene * >( in_scene ); //static_cast_checked<xray::render::scene*>(in_scene.c_ptr());
	scene_view*	view	= static_cast_checked< inex::render::scene_view * >( in_view );

	view->inc_render_frame_index		();
	
 	m_current_time						= m_timer->elapsed_ms();
	
	float time_delta					= m_current_time - m_last_frame_time;
	time_delta							= inex::math::max(time_delta, 0.0f) * scene->get_slomo();
	
	m_renderer_context->set_current_time(m_last_frame_time);
	m_renderer_context->set_time_delta  (time_delta );
	
	m_renderer_context->set_scene		(scene);
	m_renderer_context->set_scene_view	(view);
	
	//if (!is_effects_ready() || !material::is_nomaterial_material_ready()) {
	//	xray::render::scene* const scene	= static_cast_checked<xray::render::scene*>(in_scene.c_ptr());
	//	scene->flush						( on_draw_scene );
	//	return;
	//}
	
	//statistics::ref().start();
	//
	//BEGIN_CPUGPU_TIMER(statistics::ref().general_stat_group.render_frame_time);
	//BEGIN_TIMER(statistics::ref().general_stat_group.cpu_render_frame_time);
	
	//static_cast_checked< render::render_output_window* > ( output_window/*.c_ptr()*/ )->resize( );
	
	//setup_render_output_window				( output_window, viewport);
	//
	//m_renderer_context->m_light_marker_id = 1;
	//
	//m_renderer_context->scene()->update_models();
	//
	//xray::particle::world* part_world = m_renderer_context->scene()->particle_world();
	//
	//scene->get_speedtree_forest()->tick(m_renderer_context);
	//
	//if (part_world)
	//	part_world->tick( time_delta, m_renderer_context->get_v() );
	//
	//backend::ref().reset();
	//backend::ref().flush();
	
	//scene_view_mode view_mode = view->get_view_mode();
	
	//backend::ref().set_render_targets	( &*m_renderer_context->m_targets->m_rt_position, &*m_renderer_context->m_targets->m_rt_normal, 0, 0);
	//backend::ref().reset_depth_stencil_target( );
	//backend::ref().clear_render_targets	( math::color( 1.f, 1.f, 1.f, 1.f), math::color( 0.f, 0.f, 0.f, 0.f), math::color( 0.f, 0.f, 0.f, 0.f), math::color( 0.f, 0.f, 0.f, 0.f));
	//
	//backend::ref().reset_depth_stencil_target();
	//backend::ref().clear_depth_stencil	(D3D_CLEAR_DEPTH|D3D_CLEAR_STENCIL, 1.0f, 0);
	//
	//if (m_view_mode_stage && m_view_mode_stage->is_support_view_mode(view_mode))
	//{
	//	// opaque pass
	//	if (m_stages[geometry_pre_pass_render_stage])
	//		m_stages[geometry_pre_pass_render_stage]->execute();
	//	
	//	m_view_mode_stage->execute(view_mode);
	//	statistics::ref().visibility_stat_group.num_total_rendered_triangles.value = backend::ref().num_total_rendered_triangles;
	//}
	

//	else
//	{
//		float view_mode_type = float(u32(view_mode)) + 0.5f;
//		switch (view_mode)
//		{
//			case lit_view_mode:
//			case lit_with_histogram_view_mode:
//			{
//				execute_stages();
//				
//				if (view_mode==lit_with_histogram_view_mode)
//				{
//					// Copy final scene color to albedo texture.
//					resource_manager::ref().copy2D(
//						&*m_renderer_context->m_targets->m_t_color,
//						0,
//						0,
//						&*m_renderer_context->m_targets->m_t_present,
//						0,
//						0,
//						m_renderer_context->m_targets->m_t_present->width(),
//						m_renderer_context->m_targets->m_t_present->height()
//					);
//					
//					m_gbuffer_to_screen_shader->apply();
//					backend::ref().set_ps_constant(m_gbuffer_to_screen_type, view_mode_type);
//					fill_surface(m_renderer_context->m_targets->m_rt_present, m_renderer_context);
//				}
//				
//				break;
//			}
//			case unlit_view_mode:
//			case unlit_with_ao_view_mode:
//			{
//				m_stages[accumulate_distortion_render_stage]->set_enabled(false);
//				m_stages[pre_lighting_stage]->set_enabled(false);
//				m_stages[sun_shadows_accumulate_render_stage]->set_enabled(false);
//				m_stages[sun_render_stage]->set_enabled(false);
//				m_stages[deferred_lighting_render_stage]->set_enabled(false);
//				m_stages[sun_shadows_accumulate_render_stage]->set_enabled(false);
//				m_stages[post_process_render_stage]->set_enabled(false);
//				m_stages[lighting_render_stage]->set_enabled(false);
//				
//				execute_stages();
//				
//				m_stages[accumulate_distortion_render_stage]->set_enabled(true);
//				m_stages[pre_lighting_stage]->set_enabled(true);
//				m_stages[sun_shadows_accumulate_render_stage]->set_enabled(true);
//				m_stages[sun_render_stage]->set_enabled(true);
//				m_stages[deferred_lighting_render_stage]->set_enabled(true);
//				m_stages[sun_shadows_accumulate_render_stage]->set_enabled(true);
//				m_stages[post_process_render_stage]->set_enabled(true);
//				m_stages[lighting_render_stage]->set_enabled(true);
//				
//				m_gbuffer_to_screen_shader->apply();
//				backend::ref().set_ps_constant(m_gbuffer_to_screen_type, view_mode_type);
//				fill_surface(m_renderer_context->m_targets->m_rt_present, m_renderer_context);
//				
//				break;
//			}
//			case normals_view_mode:
//			case specular_intencity_view_mode:
//			case specular_power_view_mode:
//			{
//				if (m_stages[geometry_pre_pass_render_stage])
//					m_stages[geometry_pre_pass_render_stage]->execute();
//				
//				if (m_stages[decals_accumulate_render_stage])
//					m_stages[decals_accumulate_render_stage]->execute();
//				
//				m_gbuffer_to_screen_shader->apply();
//				backend::ref().set_ps_constant(m_gbuffer_to_screen_type, view_mode_type);
//				fill_surface(m_renderer_context->m_targets->m_rt_present, m_renderer_context);
//				break;
//			}
//			case lighting_view_mode:
//			case lighting_diffuse_view_mode:
//			case lighting_specular_view_mode:
//			case emissive_only_view_mode:
//			case distortion_only_view_mode:
//			{
//				
//				if (m_stages[post_process_render_stage])
//					m_stages[post_process_render_stage]->set_enabled(false);
//				
//				execute_stages();
//				
//				if (m_stages[post_process_render_stage])
//					m_stages[post_process_render_stage]->set_enabled(true);
//				
//				m_gbuffer_to_screen_shader->apply();
//				
//				backend::ref().set_ps_constant(m_gbuffer_to_screen_type, view_mode_type);
//				fill_surface(m_renderer_context->m_targets->m_rt_present, m_renderer_context);
//				break;
//			}
//			case indirect_lighting_mode:
//			{
//				m_stages[geometry_pre_pass_render_stage]->execute();
//				m_stages[decals_accumulate_render_stage]->execute();
//				m_stages[accumulate_distortion_render_stage]->execute();
//				m_stages[pre_lighting_stage]->execute();
//				m_stages[sun_render_stage]->execute_disabled();
//				m_stages[sun_shadows_accumulate_render_stage]->execute_disabled();
//				m_stages[ambient_occlusion_render_stage]->execute();
//				m_stages[light_propagation_volumes_render_stage]->execute();
//				
//				m_gbuffer_to_screen_shader->apply();
//				
//				backend::ref().set_ps_constant(m_gbuffer_to_screen_type, view_mode_type);
//				fill_surface(m_renderer_context->m_targets->m_rt_present, m_renderer_context);
//				break;
//			}
//			case ambient_occlusion_only_view_mode:
//			{
//				if (m_stages[geometry_pre_pass_render_stage])
//					m_stages[geometry_pre_pass_render_stage]->execute();
//					
//				if (m_stages[decals_accumulate_render_stage])
//					m_stages[decals_accumulate_render_stage]->execute();
//					
//				if (m_stages[ambient_occlusion_render_stage])
//					m_stages[ambient_occlusion_render_stage]->execute();
//				
//				m_gbuffer_to_screen_shader->apply();
//				
//				backend::ref().set_ps_constant(m_gbuffer_to_screen_type, view_mode_type);
//				fill_surface(m_renderer_context->m_targets->m_rt_present, m_renderer_context);
//				break;
//			}
//		}
//	}
//	
//	backend::ref().reset_depth_stencil_target();
//	
//	if (m_stages[light_propagation_volumes_render_stage])
//		((stage_light_propagation_volumes*)m_stages[light_propagation_volumes_render_stage])->draw_debug();
//
//	if (m_stages[deferred_lighting_render_stage])
//		((stage_lights*)m_stages[deferred_lighting_render_stage])->debug_render();
//	
//
//	if (m_stage_debug)
//		m_stage_debug->execute			();
//	
//	backend::ref().set_render_targets( &*m_renderer_context->m_targets->m_rt_present, 0, 0, 0);
//	
//	scene->flush					( on_draw_scene );
//
//	backend::ref().reset_depth_stencil_target();
//	
//	if (m_stages[lighting_render_stage])
//		m_stages[lighting_render_stage]->debug_render	( );
//	
//	END_TIMER;
//	END_CPUGPU_TIMER;
//	
//	statistics::ref().visibility_stat_group.num_total_rendered_triangles.value = backend::ref().num_total_rendered_triangles;
//	statistics::ref().visibility_stat_group.num_total_rendered_points.value = backend::ref().num_total_rendered_points;
//	
//	double const es = statistics::ref().general_stat_group.render_frame_time.cpu_time.average() / 1000.0;
//	double const es2 = statistics::ref().general_stat_group.cpu_render_frame_time.average() / 1000.0;
//	
//	statistics::ref().general_stat_group.fps.value = math::floor(float(es > 0.0 ? (1.0 / es) : 0.0));
//	statistics::ref().general_stat_group.cpu_fps.value = math::floor(float(es2 > 0.0 ? (1.0 / es2) : 0.0));
//	
//	statistics::ref().general_stat_group.num_setted_shader_constants.value = backend::ref().num_setted_shader_constants;
//	statistics::ref().visibility_stat_group.num_draw_calls.value = backend::ref().num_draw_calls;
//	
//	backend::ref().disabled_shader_constansts_set = false;
//	
//	if (draw_debug_terrain)
//		system_renderer::ref().draw_debug_terrain();
	
	present							( output_window, viewport );
}

} // namespace render
} // namespaccee inex