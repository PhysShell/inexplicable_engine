#include "pch.h"
#include "ie_debug.h"
#include <inex/macro_compiler.h>

#if INEX_PLATFORM_WINDOWS_32 && ! defined INEX_PLATFORM_WINDOWS_64
	INEX_PUSH_WARNING
	INEX_DISABLE_WARNING( 4820 )
	INEX_DISABLE_WARNING( 4365 )
	INEX_DISABLE_WARNING( 4191 )
#   include "RpcExStackTraceEngine.h"
	INEX_POP_WARNING
#endif

namespace inex {
namespace debug {

using inex::logging::Msg;

void 	dump_call_stack_trace ( )
{
	RpcExStackTraceEngine	call_stack;
	call_stack.Initialize	( );
	if ( RpcExStackTraceEngine::InitializationState::IS_Done == call_stack.GetInitializationState( ) )
		;//inex::core::logging::Msg ( "Call Stack Engine Initialized..." );

	string2048				buf;
	if ( S_OK == call_stack.WalkStack ( buf, sizeof( buf ), 8u ) )
		Msg					( "%s", buf );
	else
		Msg					( "!Unable to get current call stack trace." );
}

pcstr	error2string ( u32 code )
{
	pcstr result					= 0;
	static string1024 desc_storage;

	FormatMessage (
		FORMAT_MESSAGE_FROM_SYSTEM,
		0,
		code,
		0,
		desc_storage,
		sizeof( desc_storage ) - 1,
		0
	);

	result						=	desc_storage;
	return				 				result;

}

} // namespace debug
} // namespace core