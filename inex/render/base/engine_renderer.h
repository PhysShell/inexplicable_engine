#ifndef INEX_RENDER_BASE_ENGINE_RENDERER_H_INCLUDED
#define INEX_RENDER_BASE_ENGINE_RENDERER_H_INCLUDED

namespace inex {
namespace render {
namespace engine {

struct /*XRAY_NOVTABLE */renderer {
	virtual	bool	run						( bool wait_for_command ) = 0;
	virtual	bool	run_editor_commands		( bool wait_for_command ) = 0;
	//virtual	u32		frame_id				( ) = 0;
	//virtual	void	set_view_matrix			( float4x4 const& view_matrix ) = 0;
	//virtual	void	set_projection_matrix	( float4x4 const& view_matrix ) = 0;
	virtual	void	draw_frame				( ) = 0;
	virtual	void	purge_orders			( ) = 0;
	virtual	void	flush_debug_commands	( ) = 0;
	virtual	void 	test_cooperative_level	( ) = 0;

	INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR( renderer )
}; // class world

} // namespace engine
} // namespace render
} // namespace inex

#endif // #ifndef INEX_RENDER_BASE_ENGINE_RENDERER_H_INCLUDED