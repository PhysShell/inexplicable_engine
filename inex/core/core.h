#ifndef INEX_CORE_CORE_H_INCLUDED
#	define INEX_CORE_CORE_H_INCLUDED

#	include <inex/core/api.h>

namespace inex {
namespace core {

struct engine;

namespace debug {

enum error_mode {
	error_mode_silent,
	error_mode_verbose,
}; // enum error_mode

enum bugtrap_usage {
	no_bugtrap,
	native_bugtrap,
	managed_bugtrap,
}; // enum error_mode
} // namespace debug

enum log_file_usage {
	create_log,
	append_log,
	no_log,
}; // enum error_mode

enum debug_initialization {
	delay_debug_initialization,
	perform_debug_initialization,
}; // enum bugtrap_usage

INEX_CORE_API	void	preinitialize	(
							core::engine * engine,
							pcstr command_line,
							bool contains_app,
							pcstr application,
							pcstr build_date
						);
INEX_CORE_API	void	initialize	(
							pcstr debug_thread_id,
							log_file_usage log_file_usage,
							debug_initialization debug_initialization
						);
INEX_CORE_API	void	finalize	( );

INEX_CORE_API	bool	initialized ( );

} // namespace core
} // namespace inex

#endif // #ifndef INEX_CORE_CORE_H_INCLUDED