#ifndef LOG_H_INCLUDED
#	define LOG_H_INCLUDED


namespace inex {
namespace logging {
namespace detail {
	enum class logging_mode_enum
	{
		silent	=						( 1u << 0U ),
		info	=						( 1u << 1U ),
		warning	=						( 1u << 2U ),
		error	=						( 1u << 3U ),
		debug	=						( 1u << 4U ),
		trace	=						( 1u << 5U )
	}; // enum class logging_mode_enum
} // namespace detail

	void	initialize 	( bool no_log = false );
	void	finalize    ( );
	INEX_CORE_API
	void 	Msg         ( pcstr format, ... );
	INEX_CORE_API
	bool	put_string  ( pcstr msg );
} // namespace logging
} // namespace inex
#endif // #ifndef LOG_H_INCLUDED
