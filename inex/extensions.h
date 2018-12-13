#ifndef EXTENSIONS_H_INCLUDED
#	define EXTENSIONS_H_INCLUDED


// this only defined in windows
#   ifdef IECORE_EXPORTS
#       define IECORE_API __declspec(dllexport)
#   else // #ifdef IECORE_EXPORTS
#       ifdef _WIN32
#           define IECORE_API __declspec(dllimport)
#       else
#           define IECORE_API
#       endif // #ifdef _WIN32
#   endif // #ifdef IECORE_EXPORTS

#   include <stdarg.h>
#   include <cstring>
#   include <iostream>
#   include <cstdint>

// os_extensions

#   include <inex/macro_extensions.h>
#   include <inex/types.h>
#   include <inex/os_extensions.h>
//#include _stl_extensions_vector.h
#   include <inex/core/sources/ie_syncronize.h>
//#include ie_memory.h
#   include <inex/core/sources/ie_debug.h>
#   include <inex/core/sources/logger.h>
#   include <inex/core/sources/fs_file_system.h>
//#   include <inex/core/sources/fs_manager.h>
#endif // #ifdef EXTENSIONS_H_INCLUDED
