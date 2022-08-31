#pragma once
namespace inex {
namespace render {

// This will temporary live here 
const u32 stencil_material_mask			= 0x03;
const u32 stencil_light_marker_shift	= 0x02;

class renderer_context;

class stage : inex::detail::noncopyable
{
public:
				 stage				(renderer_context* context)
				 {
				 }

	virtual		 ~stage				() {}
	virtual void  execute			();
	virtual void  execute_disabled	() {}
	virtual	void  debug_render		() {}
	virtual pcstr stage_name		() const { return ""; };
			void  set_enabled		(bool enable);
	virtual bool  is_enabled		() const;
	
	// not sure if this need to live here
	static void  rm_near			()
	{
		//D3D_VIEWPORT VP = {0};//	{0,0,T->get_width(),T->get_height(),0,0.02f };
		//backend::ref().get_viewport( VP);
		//VP.MinDepth = 0;
		//VP.MaxDepth = 0.02f;
		//backend::ref().set_viewport( VP);
	}
	static void  rm_normal			()
	{
		//D3D_VIEWPORT VP = {0};//	{0,0,T->get_width(),T->get_height(),0,1.f };
		//backend::ref().get_viewport( VP);
		//VP.MinDepth = 0;
		//VP.MaxDepth = 1.0f;
		//backend::ref().set_viewport( VP);
	}
	static void  rm_far				()
	{
		//D3D_VIEWPORT VP = {0};//	{0,0,T->get_width(),T->get_height(),0.99999f,1.f };
		//backend::ref().get_viewport( VP);
		//VP.MinDepth = 0.99999f;
		//VP.MaxDepth = 1.0f;
		//backend::ref().set_viewport( VP);
	}
	
	// This need to be moved some utility class or namespace
		   void  u_compute_texgen_screen(math::float4x4& m_Texgen);
		   void  u_compute_texgen_jitter(math::float4x4& m_Texgen_J);
	
protected:
	renderer_context*				m_context;
	bool							m_enabled;
}; // class stage

} // namespace inex
} // namespace xray