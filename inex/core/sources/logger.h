#ifndef LOG_H_INCLUDED
#	define LOG_H_INCLUDED
#	include <inex/macro_debug.h>
#	include <inex/core/sources/log_callback.h>

namespace inex {
namespace logging {
namespace detail {

}

enum class verbosity {
	invalid		=	 0,	//	do not use it !!
	silent		=	 1,	//	1 << 0,
	error		=	 2,	//	1 << 1,
	warning		=	 3,	//	1 << 2,
	info		=	 4,	//	1 << 3,
	debug		=	 5,	//	1 << 4,
	trace		=	 6,	//	1 << 5,
	unset		=	 1 << 31,
}; // enum verbosity

	void	preinitialize	( );
	void	initialize 		( bool no_log = false );
	void	finalize		( );
	INEX_CORE_API
	void 	Msg				( pcstr format, ... );
	INEX_CORE_API
	bool	put_string		( pcstr msg );
	INEX_CORE_API
	bool 	check_verbosity ( pcstr initiator, verbosity verbosity );

struct debug_log_disable_raii
{
	debug_log_disable_raii				( )	{	inex::debug::disable_log_callback	( );	}
	~debug_log_disable_raii				( )	{	inex::debug::enable_log_callback	( );	}
};

} // namespace logging
} // namespace inex
#endif // #ifndef LOG_H_INCLUDED
