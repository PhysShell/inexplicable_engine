////////////////////////////////////////////////////////////////////////////
//	Created 	: 02.11.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef GAME_MODULE_PROXY_H_INCLUDED
#	define GAME_MODULE_PROXY_H_INCLUDED

#	include <inex/engine/engine_user.h>

namespace game {

class game_module_proxy : public inex::engine_user::module_proxy {
private:
	virtual	inex::engine_user::world*	create_world	(
						inex::engine_user::engine&	engine, 
						inex::input::world&			input, 
						inex::render::world&		render, 
						inex::ui::world&			ui,
						inex::physics::world&		physics,
						inex::rtp::world&			rtp,
						inex::animation::world&		animation,
						inex::sound::world&			sound
					)	{	return 0; }
	virtual	void					destroy_world		( inex::engine_user::world*& world )				{ }
	virtual	void					set_memory_allocator( inex::engine_user::allocator_type& allocator )	{ }
}; // struct game_module_proxy

} // namespace game

#endif // #ifndef GAME_MODULE_PROXY_H_INCLUDED