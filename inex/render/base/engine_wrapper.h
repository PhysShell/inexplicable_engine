////////////////////////////////////////////////////////////////////////////
//	Created		: 02.11.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_RENDER_BASE_ENGINE_WRAPPER_H_INCLUDED
#define INEX_RENDER_BASE_ENGINE_WRAPPER_H_INCLUDED

#include <functional>

#define	MAX_CACHE_LINE_PAD	64
#define	INEX_MAX_CACHE_LINE_PAD			char (m_cache_line_pad_$, __LINE__) [XRAY_MAX_CACHE_LINE_SIZE]

//#include <inex/limited_intrusive_list.h>
// #include <boost/function.hpp>

namespace inex {

namespace collision {
	struct world;
} // namespace input
	
namespace render {
namespace engine {

struct /*XRAY_NOVTABLE */ command {
	inline			command					( ) : remove_frame_id( 0 ) {}
	INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR( command )
	virtual	void	execute					( ) = 0;

	command*		next;
	// MAX_CACHE_LINE_PAD;
	u32				remove_frame_id;
}; // struct command

typedef std::function< void () >			window_thread_callback_type;

struct NOVTABLE wrapper {
	virtual	void	delete_on_logic_tick	( command* command ) = 0;
	virtual	void	delete_on_editor_tick	( command* command ) = 0;

	virtual	void	draw_frame_logic		( ) = 0;
	virtual	void	draw_frame_editor		( ) = 0;

	virtual	void	run_in_window_thread	( window_thread_callback_type const& callback ) = 0;

protected:
	INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR( wrapper )
}; // struct wrapper

} // namespace engine
} // namespace render
} // namespace inex

#endif // #ifndef INEX_RENDER_BASE_ENGINE_WRAPPER_H_INCLUDED