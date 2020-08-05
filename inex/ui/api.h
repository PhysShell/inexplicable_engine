////////////////////////////////////////////////////////////////////////////
//	Created 	: 27.12.2018
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_UI_API_H_INCLUDED
#	define INEX_UI_API_H_INCLUDED

// just for test purposes
// #	define INEX_STATIC_LIBRARIES

#	ifndef INEX_UI_API
#		define INEX_UI_API	INEX_DLL_EXPORT
#	else // #ifdef INEX_UI_API
#		define INEX_UI_API	INEX_DLL_IMPORT
#	endif // #ifdef INEX_UI_API

namespace inex {
namespace ui {

INEX_UI_API	void	create_world	( );
INEX_UI_API	void	destroy_world	( );

} // namespace ui
} // namespace inex

#endif // #ifndef INEX_UI_API_H_INCLUDED
