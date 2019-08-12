////////////////////////////////////////////////////////////////////////////
//	Created 	: 15.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_DEVICE_H_INCLUDED
#	define ENGINE_DEVICE_H_INCLUDED

namespace inex {
namespace engine {

class render_device_base;

class device
{
public:
    void                        run     ( );

private:
    render_device_base*         m_render_device;
    float                       m_delta; // amount of game time since the last frame

// need to store window data, delta, camera, render ( or render agents ) itself
// or render here contains render agents????????
}; // class device

float    get_time ( );

} // namespace engine 
} // namespace inex 

#endif // #ifndef ENGINE_DEVICE_H_INCLUDED