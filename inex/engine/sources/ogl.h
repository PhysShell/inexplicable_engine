////////////////////////////////////////////////////////////////////////////
//	Created 	: 17.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////
#ifndef OGL_H_INCLUDED
#	define OGL_H_INCLUDED

namespace inex {
namespace engine {

struct glwindow
{
    s32 width,  height;
    // state flags ( enum ?? )
    bool active, fullscreen, running;
}; //struct glwindow

// keyboard and mouse state
struct input
{
	u8      key_state[256];
	u8      button_state[3];
	s16     current_position[2];
}; // struct input

bool    gl_window_initialize( const glwindow * window);

} // namespace engine 
} // namespace inex 

#endif // #ifndef OGL_H_INCLUDED