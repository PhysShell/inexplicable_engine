#ifndef MACRO_LOG_H_INCLUDED
#	define MACRO_LOG_H_INCLUDED

//#	define	log_silent							( 1u << 0U )
//#	define	log_info							( 1u << 1U )
//#	define	log_warning							( 1u << 2U )
//#	define	log_error							( 1u << 3U )
//#	define	log_debug							( 1u << 4U )
//#	define	log_trace							( 1u << 5U )
//
//
//#	ifdef LOGGING_SENSITIVITY
//#		error please do not define LOGGING_SENSITIVITY
//#	endif 
//
//#	define LOGGING_SENSITIVITY					log_trace;
#	define LOGGER( ... )						inex::logging::Msg( __VA_ARGS__ )
#   define LOG_FLOAT3( X )                      LOGGER( "- [float3][debug]\t: x = %f, y = %f, z = %f", X.x, X.y, X.z )


#endif // #ifndef MACRO_LOG_H_INCLUDED

