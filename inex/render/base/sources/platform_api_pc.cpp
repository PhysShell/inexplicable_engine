#include "pch.h"
#include "platform_api.h"

namespace inex {
namespace render {

namespace gl4 {
	render::platform * create_render_platform( inex::render::engine::wrapper& wrapper, HWND window_handle);
} // namespace gl4

namespace dx10{
	//render::platform * create_render_platform( inex::render::engine::wrapper& wrapper, HWND window_handle);
} // namespace dx10



//static inex::command_line::key		s_dx10("dx10", "", "render", "");

render::platform * create_render_platform( inex::render::engine::wrapper& wrapper, HWND window_handle)
{
	if( !0/*s_dx10*/)
		return gl4::create_render_platform( wrapper, window_handle);
	//else
		//return dx10::create_render_platform( wrapper, window_handle);
}

} // namespace render
} // namespace inex
