#include <inex/render/gl4/sources/pch.h>
#include <inex/render/common/render_model.h>

namespace inex {
namespace render {

render_model::render_model( )
:m_locators(NULL),
m_locators_count(0)
//,m_aabbox( math::create_identity_aabb() )
{
}

void render_model::load_properties( ini::ini_file const& properties )
{
	//m_aabbox.max			= inex::math::float3(properties["bounding_box"]["max"]);
	//m_aabbox.min			= inex::math::float3(properties["bounding_box"]["min"]);

	//m_locators_count		= (u16)properties.value_exists("locators") ? (u16)properties["locators"].size() : 0;

	//if(m_locators_count)
	//{
	//	m_locators	= ALLOC(model_locator_item, m_locators_count);
	//	for(u16 i=0; i<m_locators_count; ++i)
	//	{
	//		configs::binary_config_value const& v = properties["locators"][i];
	//		model_locator_item& item	= m_locators[i];
	//		pcstr name					= v["name"];
	//		int bone_idx				= v["bone_idx"];
	//		item.m_bone					= u16(bone_idx);
	//		strings::copy				( item.m_name, name );
	//		item.m_offset				= math::create_rotation(v["rotation"]) * math::create_translation(v["position"]);
	//	}
	//}

}

} //namespace render
} // namespace inex 
