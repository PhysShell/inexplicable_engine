#ifndef MACRO_LOG_H_INCLUDED
#	define MACRO_LOG_H_INCLUDED

#define IE_LOG_F(file, ...)				inex::core::ieLog{file}(__VA_ARGS__);
// into engine.log
#define IE_LOG( ... )					inex::core::ieLog{ "engine.log" }( __VA_ARGS__ );
#define LOGGER( ... )						inex::core::logging::Msg( __VA_ARGS__ );


#ifdef DEBUG
#	define IE_DEBUG_LOG_F( file, ... )	inex::core::ieLog{ file }( __VA_ARGS__ );
#	define IE_DEBUG_LOG( ... )			inex::core::ieLog{ "engine.log" }( __VA_ARGS__ );
#else // #ifdef DEBUG
#	define IE_DEBUG_LOG_F( file, ... )	{ }
#	define IE_DEBUG_LOG( ... )			{ }
#endif // #ifdef DEBUG

#endif // #ifndef MACRO_LOG_H_INCLUDED

