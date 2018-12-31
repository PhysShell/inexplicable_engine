////////////////////////////////////////////////////////////////////////////
//	Created 	: 30.12.2018
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_CORE_API_H_INCLUDED
#	define INEX_CORE_API_H_INCLUDED

#	pragma message( "handle static library core" )

// this only defined in windows
#   ifdef IECORE_EXPORTS
#       define INEX_CORE_API __declspec(dllexport)
#   else // #ifdef IECORE_EXPORTS
#       ifdef _WIN32
#           define INEX_CORE_API __declspec(dllimport)
#       else
#           define INEX_CORE_API
#       endif // #ifdef _WIN32
#   endif // #ifdef IECORE_EXPORTS

namespace inex {
namespace core {
} // namespace ui
} // namespace core

#endif // #ifndef INEX_CORE_API_H_INCLUDED