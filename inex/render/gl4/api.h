#ifndef INEX_RENDER_OGL3_API_H_INCLUDED
#define INEX_RENDER_OGL3_API_H_INCLUDED

#	include <inex/extensions.h>

#			ifdef INEX_RENDER_OGL3_EXPORTS
#				define INEX_RENDER_OGL3_API	INEX_DLL_EXPORT
#			else // #ifdef IECORE_EXPORTS
#				define INEX_RENDER_OGL3_API	INEX_DLL_IMPORT
#			endif // #ifdef IECORE_EXPORTS
//#		endif // #ifndef INEX_STATIC_LIBRARIES



#endif // #ifndef INEX_RENDER_OGL3_API_H_INCLUDED
