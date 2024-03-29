#ifndef INEX_RENDER_WORLD_H_INCLUDED
#	define INEX_RENDER_WORLD_H_INCLUDED

namespace inex {
namespace render {

namespace engine	{	struct renderer; struct command;	}
namespace game		{	struct renderer;					}
namespace ui		{	struct renderer;					}
namespace editor	{	struct renderer;					}

struct NOVTABLE world {
	virtual	void				clear_resources	( ) = 0;

	virtual	engine::renderer&	engine			( ) = 0;
	virtual	game::renderer&		game			( ) = 0;
	virtual	ui::renderer&		ui				( ) = 0;
	virtual	editor::renderer&	editor			( ) = 0;

	virtual	void				push_command	( engine::command* command ) = 0;
	virtual	void				destroy_command	( engine::command* command ) = 0;
	virtual	void			set_editor_render_mode	( bool beditor, bool bgame ) = 0;

protected:
	//INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR( world )
}; // class world

} // namespace render
} // namespace inex

#endif // #ifndef INEX_RENDER_WORLD_H_INCLUDED
