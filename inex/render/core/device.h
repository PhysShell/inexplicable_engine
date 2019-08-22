////////////////////////////////////////////////////////////////////////////
//	Created 	: 15.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////
#ifndef DEVICE_H_INCLUDED
#	define DEVICE_H_INCLUDED

typedef struct GLFWwindow window_impl;
namespace inex      {
namespace render    {
    class render_device;
} // namespace render
namespace ogl       {

class render_device_base;

class device
{
public:
        void                run             ( )                         ;
        void                create          ( )                         ;
        void                destroy         ( )                         ;
        void                render          ( )                         ;
        void                process_input   ( )                         ;

public:
        void                initialize      ( )                         ;
inline  render::render_device*render_device ( )
                                {
                                    return  m_render_device             ;
                                }

private:                                  ;
    render::render_device*  m_render_device                             ;
    window_impl*            m_context                                   ;
    float                   m_delta                                     ; 
    u32                     m_width, m_height;

// need to store window data, delta, camera, render ( or render agents ) itself
// or render here contains render agents????????
}; // class device

float    get_time ( );

} // namespace ogl 
} // namespace inex 

#endif // #ifndef DEVICE_H_INCLUDED