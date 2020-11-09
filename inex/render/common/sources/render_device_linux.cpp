#include "pch.h"
#include <inex/render/common/sources/render_device.h>
#include <inex/render/ogl/ogl_extensions.h>
#include <inex/3rd_patry/include/GLFW/glfw3.h>


namespace inex {
namespace render {

static      window_impl*    temp;
constexpr   pcstr           window_title        = "inex";

void    render_device::create_helper ( window_impl*&   window,
                                u32     const&  width,
                                u32     const&  height )
{
    LOGGER              ( "starting render device..." );
    temp		        = glfwCreateWindow( width, height, window_title, nullptr, nullptr );
    LOGGER              ( "* '%s' window: initial config: [%d x %d]", window_title, width, height );
    ASSERT_D            ( temp, "Couldn't create window and its OpenGL context." );
    glfwMakeContextCurrent( temp );
    ogl::dump_user_specifications ( );
	bool success		= ogl::init_extensions( );
    ASSERT_D            ( success , "Failed to load OpenGL extensions\n") ;
    window              = temp;
}

void    render_device::init_draw ( )
{
}

void    render_device::draw ( )
{
}

// void    render_device::destroy ( )
// {
// }

// void    render_device::render ( )
// {
// }

} // namespace render
} // namespace engine
