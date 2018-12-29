////////////////////////////////////////////////////////////////////////////
//	Created 	: 27.12.2018
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef IE_UI_API_H_INCLUDED
#	define IE_UI_API_H_INCLUDED

// just for test purposes
#	define IE_STATIC_LIBRARIES

#	ifndef IE_UI_API
#		ifdef IE_STATIC_LIBRARIES
#			define IE_UI_API
#		else
#			error work around dlls
#		endif // #ifdef IE_STATIC_LIBRARIES
#	endif // #ifndef IE_UI_API

namespace inex {
namespace ui {

IE_UI_API	void	create_world	( );
IE_UI_API	void	destroy_world	( );

} // namespace ui
} // namespace inex

#endif // #ifndef IE_UI_API_H_INCLUDED