#ifndef LOG_H_INCLUDED
#	define LOG_H_INCLUDED


namespace inex {
namespace logging {
	void	initialize 	( bool no_log = false );
	void	finalize    ( );
	IECORE_API
	void 	Msg         ( pcstr format, ... );
	bool	put_string  ( pcstr msg );
} // namespace logging
} // namespace inex
#endif // #ifndef LOG_H_INCLUDED
