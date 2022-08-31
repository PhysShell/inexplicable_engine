#pragma once

#include <inex/extensions.h>
#include <inex/resources.h>
namespace inex {

namespace collision {
	class animated_object;
} // namespace collision

namespace render {

struct model_locator_item
{
	string32		m_name;
	math::float4x4	m_offset;
	u16				m_bone;
};

class render_model_instance : public resources::unmanaged_resource 
{
public:
	virtual void		update		( )		{}
	virtual bool		get_locator	( pcstr /*locator_name*/, model_locator_item& /*result*/ ) const {return false;}
protected:
	INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR( render_model_instance )
}; // class render_model_instance

//typedef	resources::resource_ptr<
//	render_model_instance,
//	resources::unmanaged_intrusive_base
//> render_model_instance_ptr;

typedef render_model_instance * render_model_instance_ptr;

class static_model_instance : public resources::unmanaged_resource 
{
public:
	render::render_model_instance_ptr	m_render_model;
	//collision::geometry_ptr				m_collision_geom;
};

//typedef	resources::resource_ptr<
//	static_model_instance,
//	resources::unmanaged_intrusive_base
//> static_model_ptr;

class skeleton_model_instance : public resources::unmanaged_resource
{
public:
	render_model_instance_ptr			m_render_model;
	//animation::skeleton_ptr				m_skeleton;
}; // class skeleton_model_instance

//typedef	resources::resource_ptr<
//	skeleton_model_instance,
//	resources::unmanaged_intrusive_base >
//skeleton_model_ptr;

//class terrain_model_instance : public resources::unmanaged_resource 
//{
//public:
//	render::render_model_instance_ptr		m_render_model;
//	collision::geometry_instance*			m_collision_geom;
//	physics::bt_collision_shape_ptr			m_bt_collision_shape;
//};
//
//typedef	resources::resource_ptr<
//	terrain_model_instance,
//	resources::unmanaged_intrusive_base
//> terrain_model_ptr;

} // namespace render
} // namespace inex