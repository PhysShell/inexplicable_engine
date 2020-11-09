////////////////////////////////////////////////////////////////////////////
//	Created 	: 02.11.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef GAME_PC_APPLICATION_H_INCLUDED
#	define GAME_PC_APPLICATION_H_INCLUDED

#include <inex/game/game_module_proxy.h>

namespace game {

class application
{
public:
			void		initialize		( );
			void		execute			( );
			void		finalize		( );
	inline	u32			get_exit_code	( ) const { return m_exit_code; }

private:
			void		preinitialize	( );
			void		postinitialize	( );

private:
	HWND				m_splash_screen;

private:
	game_module_proxy	m_game_proxy;
	u32					m_exit_code;
}; // class application

} // namespace game

#endif // #ifndef GAME_PC_APPLICATION_H_INCLUDED