#ifndef GL4_WORLD_H_INCLUDED
#	define GL4_WORLD_H_INCLUDED

#	include <inex/render/gl4/renderer.h>
#	include <inex/render/base/platform.h>

#	include <inex/render/base/world.h>

//#include <inex/render/common/sources/d3d_defs.h>
#	include <inex/render/gl4/gl4_external.h>
#	include <inex/render/common/sources/hw_wrapper.h>
//#include <inex/render/common/sources/render_device.h>
//#include <inex/render/gl3/sources/visual.h>
#	include <inex/render/gl4/sources/scene_render.h>
//
//#include <inex/render/common/sources/environment.h>
//#include <inex/render/common/sources/lights_db.h>
//#include <inex/render/common/sources/terrain.h>
//
#	include <inex/render/gl4/sources/model_manager.h>

#	include <inex/render/common/scene_view.h>

namespace inex {
namespace render {

struct viewport_type;
struct render_mesh;

namespace gl4 {

// to be renamed to world. (world_win.h)
class platform :
//	public inex::render::base_world,
	public inex::render::platform,
	public inex::render::gl4::renderer
{
public:
	//typedef inex::render::vector< inex::render::vertex_colored >	colored_vertices_type;
	typedef inex::render::vector< u16 >								colored_indices_type;

	typedef inex::render::ui::vertex const *	ui_vertices_type;

	inex::render::gl4::renderer *					m_renderer;

public:
							platform					( inex::render::engine::wrapper& wrapper, HWND window_handle );
	virtual					~platform					( );
	virtual	void			clear_resources			( )	{ }
	// platform methods
public:
	virtual	void			set_view_matrix			( float4x4 const& view_matrix ) {	NOT_IMPLEMENTED( );	}
	virtual	void			set_projection_matrix	( float4x4 const& projection )	{	NOT_IMPLEMENTED( );	}
	virtual	float4x4 const&	get_view_matrix			( ) const						{	NOT_IMPLEMENTED( );return float4x4( ); 	}
	virtual	float4x4 const&	get_projection_matrix	( ) const						{	NOT_IMPLEMENTED( );return float4x4( ); 	}
	//virtual	math::rectangle<math::int2_pod> get_viewport( ) const;
	virtual	void			set_world_matrix		( float4x4 const& w )			{	NOT_IMPLEMENTED( );	}
	float4x4 const&	get_world_matrix		( ) const;
	//virtual	void			draw_debug_lines		( colored_vertices_type const& vertices, colored_indices_type const& indices );
	//virtual	void			draw_debug_triangles	( colored_vertices_type const& vertices, colored_indices_type const& indices );
	virtual	void			clear_zbuffer			( float z_value )				{	 NOT_IMPLEMENTED( );	}
	virtual	void			draw_frame				( );
	virtual	u32				frame_id				( );
	virtual	void 			test_cooperative_level	( )								{	 NOT_IMPLEMENTED( );	}
	//virtual	void			add_static				( resources::managed_resource_ptr const& collision, resources::managed_resource_ptr const& geometry, resources::managed_resource_ptr const& visuals );
	
	virtual	void			add_visual					( u32 id, inex::render::visual_ptr v, float4x4 const& transform, bool selected /*= false*/, bool system_object /*= false*/, bool beditor )	{  NOT_IMPLEMENTED( );	}
	virtual	void			update_visual				( u32 id, float4x4 const& transform, bool selected )	{ NOT_IMPLEMENTED( );}
	virtual	void			remove_visual				( u32 id )	{  NOT_IMPLEMENTED( ); }
	//virtual	void			update_visual_vertex_buffer	( inex::render::visual_ptr v, inex::vectora<inex::render::buffer_fragment> const& fragments );
	//virtual	void			update_visual_index_buffer	( inex::render::visual_ptr v, inex::vectora<inex::render::buffer_fragment> const& fragments );
	//virtual	void			change_visual_shader		( inex::render::visual_ptr v, char const* shader, char const* texture );
	//virtual	void			add_light					( u32 id, light_props const& props, bool beditor );
	//virtual	void			update_light				( u32 id, light_props const& props, bool beditor );
	virtual	void			remove_light				( u32 id, bool beditor )	 {  NOT_IMPLEMENTED( ); }
	virtual	void			render_visuals				( );

	virtual	void			terrain_add_cell			( visual_ptr v, bool beditor )	{  NOT_IMPLEMENTED( ); }
	virtual	void			terrain_remove_cell			( visual_ptr v, bool beditor )	{  NOT_IMPLEMENTED( ); }

	//virtual	void 			terrain_update_cell_buffer	( visual_ptr v, inex::vectora<buffer_fragment_NEW> const& fragments, float4x4 const& transform);
	//virtual	void 			terrain_add_cell_texture	( visual_ptr v, texture_string const & texture, u32 user_tex_id);
	virtual	void 			terrain_remove_cell_texture	( visual_ptr v, u32 user_tex_id)	 {  NOT_IMPLEMENTED( ); }
	//virtual	void			terrain_exchange_texture	( texture_string const & old_texture, texture_string const & new_texture);


	virtual	void			draw_static				( ) { }
	virtual	void			draw_ui_vertices		( ui_vertices_type vertices, u32 const & count, int prim_type, int point_type )	 {  NOT_IMPLEMENTED( ); }

	// Editor specific functions
	//virtual	void			draw_editor_lines		( colored_vertices_type const& vertices, colored_indices_type const& indices );
	//virtual	void			draw_editor_triangles	( colored_vertices_type const& vertices, colored_indices_type const& indices );
	//virtual	void			draw_screen_lines		( math::float2 const* points, u32 count, color clr, float width, u32 pattern );
	//virtual	void			draw_3D_screen_lines	( math::float3 const* points, u32 count, color clr, float width, u32 pattern, bool use_depth );

	virtual	void			setup_grid_render_mode	( u32 grid_density )	 {  NOT_IMPLEMENTED( ); }
	virtual	void			remove_grid_render_mode	( )	{  NOT_IMPLEMENTED( ); }
	virtual	void			setup_rotation_control_modes ( int mode, int ref_value )	{  NOT_IMPLEMENTED( ); }

	virtual	void			set_editor_render_mode ( bool draw_editor, bool draw_game )	 {  NOT_IMPLEMENTED( ); }

	void					draw_scene						(
																scene_ptr const& scene,
																scene_view_ptr const& view,
																render_output_window_ptr const& output_window,
																viewport_type const& viewport,
																std::function< void ( bool ) > const& on_draw_scene
															);
	// renderer methods
public:
	virtual	pcstr			type					( );

public:
	typedef render::engine::wrapper		wrapper;

private:
			void 			create_resources		( );
			void 			destroy_resources		( );
			//void 			on_ui_texture_loaded	( resources::queries_result& data );
			void 			initialize_grid_textures( );
			void 			release_grid_textures	( );
			//void			on_test_visual_loaded	( resources::queries_result& data );
			//void			test					( pcstr args );
public:
			//void			setup_screen_res		( res_constant* c );

	//res_constant*	m_c_mat_vp;
	//res_constant*	m_c_mat_wvp;
	float4x4	m_view_matrix;
	float4x4	m_proj_matrix;
	float4x4	m_world_matrix;

public:
	//void setup_editor_selected_color(res_constant* c);

private:
	typedef render::base_world				super;

public:
			// GLFWwidnow
	inline	pvoid& device			( ) const;
	inline	wrapper&		engine				( ) const;

private:
	//environment				m_env;
	hw_wrapper				m_hw;
	//render_device			m_render_device;
	//
	////Do not change order of initialization of managers!!! 
	//resource_manager		m_res_mgr;
	//shader_manager			m_sh_mgr;

	//backend					m_backend;

	//material_manager		m_mat_mgr;
	model_manager			m_model_manager;
	scene_render*			m_scene;
	//lights_db				m_lights_db;
	//terrain					m_terrain;

	//IDirect3DVertexBuffer9* m_ui_vb;
	//IDirect3DIndexBuffer9*	m_ui_ib;
	//IDirect3DPixelShader9*	m_ui_ps;
	//IDirect3DPixelShader9*	m_ui_ps_font;
	//IDirect3DPixelShader9*	m_ui_ps_fill;
	//IDirect3DTexture9*      m_ui_texture;
	//IDirect3DTexture9*      m_ui_texture_font;

	//IDirect3DPixelShader9*	m_ps_geom;
	//IDirect3DVertexBuffer9* m_debug_vb;
	//IDirect3DIndexBuffer9*	m_debug_ib;

	//IDirect3DVertexBuffer9* m_editor_vb;
	//IDirect3DIndexBuffer9*	m_editor_ib;
	//float4					m_editor_selected_color;

	u32							m_render_frame_id;
	//math::float4x4			m_current_view_matrix;
	//ID3DXLine*				m_line;
	//IDirect3DTexture9*		m_grid_texture_50;
	//IDirect3DTexture9*		m_grid_texture_25;

	bool					m_render_test_scene;

}; // class world

} // namespace gl4
} // namespace render 
} // namespace inex 
namespace inex {
namespace render {
namespace gl4 {


inline pcstr platform::type				( )
{
	return	( "gl4" );
}

inline u32 platform::frame_id				( )
{
	return	( m_render_frame_id );
}

// place GLFWwindow here
inline pvoid& platform::device	( ) const
{
	//ASSERT	( m_device );
	// get_ref is from quasi singleton stuff
	return		device( );
	//return	*hw_wrapper::get_ref().device();//( *m_device );
}

} // namespace gl4
} // namespace render 
} // namespace inex 

//#include <inex/render/base/sources/platform_gl4_inline.h>

#endif // #ifndef GL4_WORLD_H_INCLUDED