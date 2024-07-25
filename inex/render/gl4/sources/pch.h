// pch.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef PCH_H_INCLUDED
#	define PCH_H_INCLUDED
#	include <inex/extensions.h>
#			ifdef INEX_RENDER_GL4_EXPORTS
#				define INEX_RENDER_OGL4_API	INEX_DLL_EXPORT
#			else // #ifdef INEX_RENDER_GL4_EXPORTS
#				define INEX_RENDER_OGL4_API	INEX_DLL_IMPORT
#			endif // #ifdef INEX_RENDER_GL4_EXPORTS
//#		endif // #ifndef INEX_STATIC_LIBRARIES

#endif // #ifndef PCH_H_INCLUDED
// TODO: reference additional headers your program requires here
