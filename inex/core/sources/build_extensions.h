#ifndef BUILD_EXTENSIONS_H_INCLUDED
#	define BUILD_EXTENSIONS_H_INCLUDED

#include <inex/extensions.h>
#include <inex/core/api.h>
#include <inex/core/core.h>

namespace inex {
namespace build {
					void	preinitialize				( pcstr const build_date );
					void	initialize					( core::engine * );
	INEX_CORE_API	u32		calculate_build_id			( pcstr current_date );
					bool	print_build_id_command_line ( );
	INEX_CORE_API	pcstr	build_date					( );
} // namespace build
} // namespace inex

#endif // #ifndef BUILD_EXTENSIONS_H_INCLUDED