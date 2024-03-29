#ifndef MACRO_LOG_H_INCLUDED
#	define MACRO_LOG_H_INCLUDED

#ifdef LOG_ERROR
#	error do not define LOG_ERROR macro
#endif // #ifdef LOG_ERROR
#ifdef LOG_WARNING
#	error do not define LOG_WARNING macro
#endif // #ifdef LOG_WARNING
#ifdef LOG_INFO
#	error do not define LOG_INFO macro
#endif // #ifdef LOG_INFO

#	define LOG_VECTORS_BRACES_STYLE
#	define LOGGER( ... )						::inex::logging::Msg( __VA_ARGS__ )

#	if defined LOG_VECTORS_BRACES_STYLE
#		define LOG_FLOAT3( X )						LOGGER( "- [float4][debug]\t: [%.2f][%.2f][%.2f]", X.x, X.y, X.z )
#		define LOG_FLOAT4( X )						LOGGER( "- [float4][debug]\t: [%.2f][%.2f][%.2f][%.2f]", X.x, X.y, X.z, X.w )
#	else // #	if defined LOG_VECTORS_BRACES_STYLE
#   	define LOG_FLOAT3( X )                      LOGGER( "- [float3][debug]\t: x = %f, y = %f, z = %f", X.x, X.y, X.z )
#		define LOG_FLOAT4( X )						LOGGER( "- [float4][debug]\t: x = %f, y = %f, z = %f, w = %f", X.x, X.y, X.z, X.w )
#	endif // #	if defined LOG_VECTORS_BRACES_STYLE

#	define LOG_FLOATNX4( X, N )					do { for ( u8 i = 0; i < N; ++i ) LOG_FLOAT4( X.get_single( i ) ); } while ( 0 )

#	define LOG_FLOAT4X3( X )					do { LOGGER( "- [float4x3][debug]\t: '" QUOTE( X ) "':" ); LOG_FLOATNX4( X, 3 ); LOGGER( "\r" ); } while ( 0 )
#	define LOG_FLOAT4X4( X )					do { LOGGER( "- [float4x4][debug]\t: '" QUOTE( X ) "':" ); LOG_FLOATNX4( X, 4 ); LOGGER( "\r" ); } while ( 0 )

#define LOG_ERROR( ... )						::inex::logging::check_verbosity( INEX_LOG_MODULE_INITIATOR ":" , ::inex::logging::error) ? \
												::inex::logging::Msg( __VA_ARGS__ ) : 0

#endif // #ifndef MACRO_LOG_H_INCLUDED
