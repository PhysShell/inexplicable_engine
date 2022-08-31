#include "pch.h"
#include <inex/render/facade/render_stage_type.h>

namespace inex {
namespace render {

enum_render_stage_type string_to_stage_type(pcstr stage_name)
{
	if		(strings::equals(stage_name, "g_stage"))					return enum_render_stage_type::geometry_render_stage;
	else if (strings::equals(stage_name, "distortion"))					return enum_render_stage_type::accumulate_distortion_render_stage;
	else if (strings::equals(stage_name, "forward"))					return enum_render_stage_type::forward_render_stage;
	else if (strings::equals(stage_name, "shadow"))						return enum_render_stage_type::shadow_render_stage;
	else if (strings::equals(stage_name, "ambient_occlusion"))			return enum_render_stage_type::ambient_occlusion_render_stage;
	else if (strings::equals(stage_name, "light_propagation_volumes"))	return enum_render_stage_type::light_propagation_volumes_render_stage;
	else if (strings::equals(stage_name, "lighting"))					return enum_render_stage_type::lighting_render_stage;
	else if (strings::equals(stage_name, "post_process"))				return enum_render_stage_type::post_process_render_stage;
	else if (strings::equals(stage_name, "debug_post_process"))			return enum_render_stage_type::debug_post_process_render_stage;
	else if (strings::equals(stage_name, "decals"))						return enum_render_stage_type::decals_accumulate_render_stage;
	else if (strings::equals(stage_name, "debug"))						return enum_render_stage_type::debug_render_stage;
	else																return enum_render_stage_type::unknown_render_stage;
}

pcstr stage_type_to_string(enum_render_stage_type stage_type)
{
	switch (stage_type)
	{
		case enum_render_stage_type::geometry_render_stage:										return "g_stage";
		case enum_render_stage_type::accumulate_distortion_render_stage:						return "distortion";
		case enum_render_stage_type::forward_render_stage:										return "forward";
		case enum_render_stage_type::shadow_render_stage:										return "shadow";
		case enum_render_stage_type::ambient_occlusion_render_stage:							return "ambient_occlusion";
		case enum_render_stage_type::light_propagation_volumes_render_stage:					return "light_propagation_volumes";
		case enum_render_stage_type::lighting_render_stage:										return "lighting";
		case enum_render_stage_type::post_process_render_stage:									return "post_process";
		case enum_render_stage_type::debug_post_process_render_stage:							return "debug_post_process";
		case enum_render_stage_type::debug_render_stage:										return "debug";
		case enum_render_stage_type::decals_accumulate_render_stage:							return "decals";
		default:																				return "unknown";
	};
}

} // namespace render
} // namespace inex


