#pragma once
#include <inex/render/core/model.h>
#include <inex/core/sources/fs_ini_file.h>

namespace inex {
	namespace resources {
		struct managed_resource_ptr
		{
			math::float4x4	m_vertices;
			pcstr			vs;
			pcstr			fs;
		}; // class manager_resource_ptr
	} // namespace resources

namespace render {

//class res_geometry;
//typedef res_geometry * ref_geometry;
//struct render_geometry
//{
//	ref_geometry	geom;
//
//	u32			vertex_count;
//	u32			index_count;
//	u32			primitive_count;
//};//struct render_geometry

class render_model : public resources::unmanaged_resource 
{
public:
						render_model		( );
	virtual	void		load_properties		( ini::ini_file const& properties );
	//virtual	void		append_surface		( render_surface* ){};
	//math::aabb			m_aabbox;
	virtual bool		get_locator			( pcstr locator_name, model_locator_item& result ) const;

protected:
	model_locator_item*			m_locators			= 0;
	u16							m_locators_count	= 0;
};

class render_model_instance_impl	: public render_model_instance
{
public:
						render_model_instance_impl	( );

	virtual	void		set_constants				( )		{}
	//virtual math::aabb	get_aabb					( )		= 0;

	//virtual void		get_surfaces				( render_surface_instances&, bool /*visible_only*/ ){};

	// TODO: make these protected
	
	//collision_object<render_model_instance_impl>	m_collision_object;
	virtual void		set_transform				( math::float4x4 const& transform ) { m_transform = transform; }
	inline math::float4x4 const& transform			( ) const { return m_transform; }
protected:
 	math::float4x4									m_transform;
};

typedef render_model_instance_impl * render_model_instance_impl_ptr;

typedef std::vector< render_model_instance_impl_ptr >	render_model_instances;

} //namespace render
} // namespace inex 