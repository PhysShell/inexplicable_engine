#ifndef PLATFORM_API_H_INCLUDED
#define PLATFORM_API_H_INCLUDED

#include <inex/render/base/engine_wrapper.h>

namespace inex {
namespace render {

	struct platform;

	render::platform * create_render_platform( inex::render::engine::wrapper& wrapper, HWND window_handle);

} // namespace render
} // namespace inex

#endif // #ifndef PLATFORM_API_H_INCLUDED