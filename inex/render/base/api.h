#ifndef INEX_RENDER_BASE_API_H_INCLUDED
#	define INEX_RENDER_BASE_API_H_INCLUDED

#	include <inex/render/api.h>

//#		ifdef INEX_STATIC_LIBRARIES
//#			define INEX_CORE_API
//#		else
#			ifdef INEX_RENDER_BASE_EXPORTS
#				define INEX_RENDER_BASE_API	INEX_DLL_EXPORT
#			else // #ifdef IECORE_EXPORTS
#				define INEX_RENDER_BASE_API	INEX_DLL_IMPORT
#			endif // #ifdef IECORE_EXPORTS
//#		endif // #ifndef INEX_STATIC_LIBRARIES

#	include <inex/core/sources/memory_general_allocator.h>

namespace inex {
namespace render {

typedef memory::general_allocator									logic_allocator_type;
typedef memory::general_allocator									editor_allocator_type;
typedef memory::general_allocator									render_allocator_type;

INEX_RENDER_BASE_API	void	memory_allocator	(
									render_allocator_type& render_allocator,
									logic_allocator_type& logic_allocator,
									editor_allocator_type& editor_allocator
								);

} // namespace render
} // namespace inex

#endif // #ifndef INEX_RENDER_BASE_API_H_INCLUDED