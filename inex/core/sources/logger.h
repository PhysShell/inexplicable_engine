#ifndef LOG_H_INCLUDED
#	define LOG_H_INCLUDED


namespace inex {
namespace core {
namespace log {

void 	IECORE_API	Msg         ( pcstr format, ... );
bool					put_string  ( pcstr msg );
void   IECORE_API       initialize 	( bool no_log = false );
void   IECORE_API       finalize    	( );

} // namespace log
} // namespace core
} // namespace inex
#endif // #ifndef LOG_H_INCLUDED
