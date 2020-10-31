////////////////////////////////////////////////////////////////////////////
//	Created 	: 30.12.2018
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_CORE_API_H_INCLUDED
#	define INEX_CORE_API_H_INCLUDED

#	ifndef EXTENSIONS_H_INCLUDED
#		error please include extenstions.h instead
#	endif // ifndef EXTENSIONS_H_INCLUDED

#	ifndef INEX_CORE_API
#   include <inex/macro_compiler.h>

//#		ifdef INEX_STATIC_LIBRARIES
//#			define INEX_CORE_API
//#		else
#			ifdef IECORE_EXPORTS
#				define INEX_CORE_API	INEX_DLL_EXPORT
#			else // #ifdef IECORE_EXPORTS
#				define INEX_CORE_API	INEX_DLL_IMPORT
#			endif // #ifdef IECORE_EXPORTS
//#		endif // #ifndef INEX_STATIC_LIBRARIES
#	endif // #ifdef INEX_CORE_API

namespace inex {
namespace core {
} // namespace ui
} // namespace core

#endif // #ifndef INEX_CORE_API_H_INCLUDED
