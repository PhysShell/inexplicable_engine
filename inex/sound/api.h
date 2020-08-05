////////////////////////////////////////////////////////////////////////////
//	Created 	: 16.10.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_SOUND_API_H_INCLUDED
#	define INEX_SOUND_API_H_INCLUDED


#	ifndef INEX_SOUND_API
#		ifdef INEX_SOUND_EXPORTS
#			define INEX_SOUND_API	INEX_DLL_EXPORT
#		else // #ifdef INEX_SOUND_EXPORTS
#			define INEX_SOUND_API	INEX_DLL_IMPORT
#		endif // #ifdef INEX_SOUND_EXPORTS
#	endif // #ifdef INEX_SOUND_API

namespace inex {
namespace sound {

INEX_SOUND_API	void	create_world	( );
INEX_SOUND_API	void	destroy_world	( );

} // namespace sound
} // namespace inex

#endif // #ifndef INEX_SOUND_API_H_INCLUDED
