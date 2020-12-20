////////////////////////////////////////////////////////////////////////////
//	Created		: 02.11.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef ENGINE_WORLD_H_INCLUDED
#	define ENGINE_WORLD_H_INCLUDED

#	include <inex/utils.h>

#include <inex/core/engine.h>
//#include <inex/input/engine.h>
#include <inex/render/base/engine_wrapper.h>
#include <inex/engine/engine_user.h>

#include <inex/core/sources/memory_general_allocator.h>
#include <inex/threading_functions.h>

#if !defined(_MSC_VER)
	typedef pvoid HWND;
#endif // #if !defined(_MSC_VER)

namespace inex {
namespace engine {

typedef std::function< void () >					logic_thread_callback_type;

class engine_world :
	public core::engine,
	//public input::engine,
	public render::engine::wrapper,
	public inex::engine_user::engine//,
	//private inex::detail::noncopyable
{
public:
							engine_world			( pcstr command_line, pcstr application, pcstr build_date );
	virtual					~engine_world			( );
			void			initialize				( );
			void			run						( );

	virtual void			set_exit_code			( int exit_code ) { m_exit_code = exit_code; }
	virtual	int				get_exit_code			( ) const { return m_exit_code; }
	virtual	pcstr			get_resource_path		( ) const;
	virtual	pcstr			get_mounts_path			( ) const;
	virtual	pcstr			get_underscore_G_path	( ) const;
	virtual bool			app_is_active			( );
	virtual void			on_app_activate			( );
	virtual void			on_app_deactivate		( );

			bool			command_line_editor		( )	{ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; return 1; }
			bool	command_line_no_splash_screen	( ) { LOGGER( "FIX ME %s", __FILE__LINE__ ) ; return 1; }
			bool			setup_engine_user		( inex::engine_user::module_proxy* module_proxy );
public:
	render::world&			render_world			( )	const	{ return *m_render_world;	}
	inex::engine_user::world& engine_user_world		( ) const	{ return *m_engine_user_world; }
	//ui::world const&		ui_world				( )	const	{ return *m_ui_world;		}
	//input::world&			input_world				( )	const	{ return *m_input_world;	}
	//editor::world*			editor_world			( )	const	{ return m_editor;			}
	//rtp::world*				rtp_world				( )			{ return m_rtp_world; }
private:
	virtual	void			tick					( );
	virtual	bool			on_before_editor_tick	( );
	virtual	void			on_after_editor_tick	( );
	virtual	void			run_renderer_commands	( ) { LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
	virtual	void			draw_frame				( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
	virtual	void			flush_debug_commands	( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
	virtual	void			on_resize				( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
	virtual	void			enable_game				( bool value );
	virtual	void			delete_on_logic_tick	( render::engine::command* command ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
	virtual	void			delete_on_editor_tick	( render::engine::command* command ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
	virtual	void			run_in_window_thread	( render::engine::window_thread_callback_type const& callback ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
	virtual	void			draw_frame_logic		( );
	virtual	void			draw_frame_editor		( );
	virtual	void			exit					( int exit_code ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
	virtual	void			enter_editor_mode		( );
	virtual	render::world&	get_renderer_world		( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; return *((render::world*)(0)); }
	virtual	sound::world&	get_sound_world			( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; return *((sound::world*)(0));}
	virtual	animation::world& get_animation_world	( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; return *((animation::world*)(0)); }
	virtual	float			get_last_frame_time		( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; return 0.f; }
	virtual	bool			command_line_editor_singlethread	( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; return 1; }

	virtual	void 			load_level				( pcstr project_name );
	virtual	void 			unload_level			( );


private:
			void			initialize_core			( );
			void			initialize_editor		( );
			void			initialize_render		( );
			void			initialize_logic		( );
			void			post_initialize			( );
			void			enable_game_impl		( bool const value );

private:
			void			initialize_input		( );
			void			initialize_engine_user	( );
			void			initialize_network		( ){ LOGGER( "FIX ME %s", __FUNCTION__ ) ; }
			void			initialize_network_modules ( ){ LOGGER( "FIX ME %s", __FUNCTION__ ) ; }
			void			initialize_sound		( ){ LOGGER( "FIX ME %s", __FUNCTION__ ) ; }
			void			initialize_sound_modules( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
			void			initialize_ui			( );
			void			initialize_physics		( );
			void			initialize_rtp			( );
			void			initialize_animation	( );
			void			initialize_logic_modules( );

private:
			void			create_render			( );
			void			destroy_render			( );
			void	delete_processed_logic_orders	( bool destroying );
			void	delete_processed_editor_orders	( bool destroying );
			void			logic_tick				( );
			void			logic					( );
			void			editor					( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
			void			network_tick			( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
			void			network					( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
			void			sound_tick				( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
			void			sound					( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
			void			try_load_editor			( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
			void			unload_editor			( );
			void			show_window				( );
			bool			process_messages		( );
			void			logic_clear_resources	( );
			void			network_clear_resources	( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
			void			sound_clear_resources	( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
			void			editor_clear_resources	( );
			void			finalize_logic_modules	( );
			void	initialize_editor_thread_ids	( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; }
private:
	typedef render::engine::command			command_type;

	struct command_type_impl : public command_type {
		virtual			~command_type_impl			( ) { }
		virtual	void	execute						( ) { }
	}; // struct command_type_impl
	//typedef intrusive_spsc_queue< command_type, command_type, &command_type::next >	command_list_type;
	//typedef memory::doug_lea_allocator_type								doug_lea_allocator_type;
	
	typedef memory::general_allocator										doug_lea_allocator_type;

private:
	//static	void			delete_processed_orders	( command_list_type& list, doug_lea_allocator_type& allocator, u32 frame_id, bool destroying );

private:
	doug_lea_allocator_type			m_input_allocator;
	doug_lea_allocator_type			m_engine_user_allocator;
	doug_lea_allocator_type			m_network_allocator;
	doug_lea_allocator_type			m_sound_allocator;
	doug_lea_allocator_type			m_ui_allocator;
	doug_lea_allocator_type			m_physics_allocator;
	doug_lea_allocator_type			m_rtp_allocator;
	doug_lea_allocator_type			m_animation_allocator;
	doug_lea_allocator_type			m_render_allocator;
	doug_lea_allocator_type			m_editor_allocator;

	//command_list_type				m_processed_logic;
	//command_list_type				m_processed_editor;

	//timing::timer					m_timer;
	input::world*					m_input_world;
	render::world*					m_render_world;
	network::world*					m_network_world;
	sound::world*					m_sound_world;
	ui::world*						m_ui_world;
	physics::world*					m_physics_world;
	rtp::world*						m_rtp_world;
	editor::world*					m_editor;
	animation::world*				m_animation_world;

//	engine_user
	inex::engine_user::module_proxy* m_engine_user_module_proxy;
	inex::engine_user::world*		 m_engine_user_world;

	HWND							m_window_handle;
	HWND							m_main_window_handle;
	u32								m_logic_frame_id;
	u32								m_editor_frame_id;
	float							m_last_frame_time;
	threading::atomic32_type		m_destruction_started;
	bool							m_early_destruction_started;
	int								m_exit_code;
	bool							m_logic_frame_ended;
	bool							m_editor_frame_ended;
	bool							m_initialized;
	bool							m_game_enabled;
	bool							m_game_paused_last;
	bool							m_app_active;
}; // class engine_world

} // namespace engine

inline bool	command_line_editor					( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; return 0; }
inline bool	command_line_editor_singlethread	( ){ LOGGER( "FIX ME %s", __FILE__LINE__ ) ; return 1; }

} // namespace inex

#endif // #ifndef ENGINE_WORLD_H_INCLUDED	
