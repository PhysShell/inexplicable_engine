#pragma once
enum class render_stage_type_enum
{
	geometry_pre_pass_render_stage = 0,
	decals_accumulate_render_stage,
	accumulate_distortion_render_stage,
	pre_lighting_stage,
	sun_shadows_accumulate_render_stage,
	sun_render_stage,
	deferred_lighting_render_stage,
	ambient_occlusion_render_stage,
	light_propagation_volumes_render_stage,
	geometry_render_stage,
	skybox_render_stage,
	clouds_render_stage,
	apply_distortion_render_stage,
	forward_render_stage,
	particles_render_stage, // TODO: stage particles to forward
	lighting_render_stage,
	post_process_render_stage,
	debug_post_process_render_stage,
	debug_render_stage,
	
	shadow_render_stage,
	
	num_render_stages,
	unknown_render_stage,

}; // render_stage_type_enum

render_stage_type_enum	string_to_stage_type	(pcstr stage_name);
pcstr					stage_type_to_string	(render_stage_type_enum stage_type);
