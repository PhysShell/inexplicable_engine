////////////////////////////////////////////////////////////////////////////
//	Created 	: 04.01.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_RENDER_API_H_INCLUDED
#	define INEX_RENDER_API_H_INCLUDED

#	ifndef INEX_RENDER_API
#   include <inex/macro_compiler.h>

//#		ifdef INEX_STATIC_LIBRARIES
//#			define INEX_CORE_API
//#		else
#			ifdef INEX_RENDER_EXPORTS
#				define INEX_RENDER_API	INEX_DLL_EXPORT
#			else // #ifdef IECORE_EXPORTS
#				define INEX_RENDER_API	INEX_DLL_IMPORT
#			endif // #ifdef IECORE_EXPORTS
//#		endif // #ifndef INEX_STATIC_LIBRARIES
#	endif // #ifdef INEX_CORE_API

namespace inex {
namespace render {

struct world;

namespace engine {
	struct wrapper;
} // namespace engine

INEX_RENDER_API	world*	create_world	( render::engine::wrapper& engine, HWND window_handle );
INEX_RENDER_API	void	destroy_world	( world*& world );

} // namespace render
} // namespace inex

#endif // #ifndef INEX_RENDER_API_H_INCLUDED
