////////////////////////////////////////////////////////////////////////////
//	Created 	: 21.08.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////
#ifndef RENDER_DEVICE_H_INCLUDED
#	define RENDER_DEVICE_H_INCLUDED

#   include <inex/types.h>

struct  GLFWwindow;
typedef GLFWwindow      window_impl;

namespace inex      {
namespace render    {

class render_device_base
{
public:
                        render_device_base  ( ) = default   ;
inline  virtual         ~render_device_base ( )             { ; }
        virtual void    create              ( ) = 0         ;

private:
    enum struct enum_device_state
    {
        enum_device_state_ok = 1,
        enum_device_state_lost,
        enum_device_state_need_reset
    }; // enum struct enum_device_state
}; // class render_device_base

// namespace render_ogl
class render_device : public render_device_base
{
public:
        virtual void    create          ( ) override { ; }
                void    create_helper   ( window_impl   *&  window,
                                            u32     const&  width,
                                            u32     const&  height )
                                            ;

                void    draw            ( ) ;
// inline          window* context         ( ) {   return m_context;   }
private:
                void    init_draw       ( ) ;
}; // class render_device

} // namespace render
} // namespace inex

#endif // #ifndef RENDER_DEVICE_H_INCLUDED
