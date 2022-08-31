#pragma once

namespace inex {
namespace render {

struct vertex_colored
{
	math::float3	position;
	math::color		color;

	inline vertex_colored()
	{
	}

	inline vertex_colored(
			math::float3 const& position,
			math::color	const& color
		) :
		position( position ),
		color	( color )
	{
	}
}; // struct vertex_colored

} // namespace render
} // namespace inex