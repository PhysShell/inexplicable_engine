////////////////////////////////////////////////////////////////////////////
//	Created 	: 27.12.2018
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_ENGINE_API_H_INCLUDED
#	define INEX_ENGINE_API_H_INCLUDED

#	include <inex/macro_compiler.h>

#if defined INEX_ENGINE_EXPORT
#	define INEX_ENGINE_API	INEX_DLL_EXPORT
#else // #ifdef IECORE_EXPORTS
#	define INEX_ENGINE_API	INEX_DLL_IMPORT
#endif // #ifdef IECORE_EXPORTS

namespace inex {

namespace engine_user {
	struct module_proxy;
} // namespace engine_user

namespace engine {

INEX_ENGINE_API	void	preinitialize					( pcstr command_line, pcstr application, pcstr build_date );
INEX_ENGINE_API	void	initialize						( inex::engine_user::module_proxy* module_proxy );
INEX_ENGINE_API	void	execute							( );
INEX_ENGINE_API	int		get_exit_code					( );
INEX_ENGINE_API	void	finalize						( );
INEX_ENGINE_API	bool	command_line_editor				( );
INEX_ENGINE_API	bool	command_line_no_splash_screen	( );

} // namespace engine
} // namespace inex

#endif // #ifndef INEX_ENGINE_API_H_INCLUDED
