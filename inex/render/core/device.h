////////////////////////////////////////////////////////////////////////////
//	Created 	: 15.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////
#ifndef DEVICE_H_INCLUDED
#	define DEVICE_H_INCLUDED

#include <inex/render/ogl/ogl_extensions.h>

struct GLFWwindow;

namespace inex {
namespace ogl {

class render_device_base;

class device
{
public:
        void                run             ( )                         ;
        void                create          ( )                         ;
        void                destroy         ( )                         ;
        void                render          ( )                         ;
        void                loop            ( )                         ;
        void                process_input   ( )                         ;
inline  GLFWwindow*         context         ( ) {   return m_context;   }


private:
    GLFWwindow*             m_context                                   ;
    render_device_base*     m_render_device                             ;
    float                   m_delta                                     ; 

// need to store window data, delta, camera, render ( or render agents ) itself
// or render here contains render agents????????
}; // class device

float    get_time ( );

} // namespace ogl 
} // namespace inex 

#endif // #ifndef DEVICE_H_INCLUDED