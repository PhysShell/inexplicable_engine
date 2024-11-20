#ifndef HW_WRAPPER_BASE_GL4_H_INCLUDED
#	define HW_WRAPPER_BASE_GL4_H_INCLUDED

#	if INEX_PLATFORM_LINUX
#       if INEX_USE_XLIB_IN_HW_WRAPPER
#		    include <inex/render/common/sources/hw_wrapper_base_gl4_linux_xlib.h>
#       else // #if INEX_USE_XLIB_IN_HW_WRAPPER
#           include <inex/render/common/sources/hw_wrapper_base_gl4_linux_wayland.h>
#       endif
#	elif INEX_PLATFORM_WINDOWS // #if INEX_PLATFORM_LINUX
#		include <inex/render/common/sources/hw_wrapper_base_gl4_win_winapi.h>
#	endif // #if INEX_PLATFORM_LINUX

#endif // #ifndef HW_WRAPPER_BASE_OGL3_H_INCLUDED