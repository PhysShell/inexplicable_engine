////////////////////////////////////////////////////////////////////////////
//	Created		: 02.11.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_ENGINE_ENGINE_USER_H_INCLUDED
#	define INEX_ENGINE_ENGINE_USER_H_INCLUDED

namespace inex {

namespace editor {
	struct world;
} // namespace editor

namespace animation {
	struct world;
} // namespace animation

namespace input {
	struct world;
} // namespace input

namespace render {
	struct world;

	namespace engine {
		struct command;
	} // namespace engine
} // namespace render

namespace network {
	struct engine;
	struct world;
} // namespace game

namespace sound {
	struct engine;
	struct world;
} // namespace game

namespace ui {
	struct world;
} // namespace ui

namespace physics {
	struct world;
} // namespace physics

namespace rtp {
	struct world;
} // namespace rtp

namespace engine_user {

typedef pvoid	allocator_type;

struct NOVTABLE engine {
	virtual	float	get_last_frame_time	( ) = 0;
	virtual	void	exit				( int exit_code ) = 0;
	virtual	void	enter_editor_mode	( ) = 0;
	virtual	bool	command_line_editor	( ) = 0;

protected:
	INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR( engine )
}; // class engine

struct NOVTABLE world {
	virtual	void	enable				( bool value ) = 0;
	virtual	void	tick				( u32 current_frame_id ) = 0;
	virtual	void	clear_resources		( ) = 0;
	virtual	void 	load				( pcstr project_name ) = 0;
	virtual	void 	unload				( pcstr ) = 0;

protected:
	INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR( world )
}; // class world

struct NOVTABLE module_proxy {
	virtual	world*	create_world		(
						inex::engine_user::engine&	engine, 
						inex::input::world&			input, 
						inex::render::world&		render, 
						inex::ui::world&			ui,
						inex::physics::world&		physics,
						inex::rtp::world&			rtp,
						inex::animation::world&		animation,
						inex::sound::world&			sound
					) = 0;
	virtual	void	destroy_world		( world*& world ) = 0;
	virtual	void	set_memory_allocator( allocator_type& allocator ) = 0;

protected:
	
	INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR( module_proxy )
}; // class module_proxy

} // namespace engine_user
} // namespace inex

#endif // #ifndef INEX_ENGINE_ENGINE_USER_H_INCLUDED