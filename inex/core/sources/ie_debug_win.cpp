#include "pch.h"
#include "ie_debug.h"
#include <inex/core/core.h>
#include <inex/macro_compiler.h>
#include <errhandlingapi.h>
#include <winnt.h>

#if INEX_PLATFORM_WINDOWS_32 && ! defined INEX_PLATFORM_WINDOWS_64
	INEX_PUSH_WARNING
	INEX_DISABLE_WARNING( 4820 )
	INEX_DISABLE_WARNING( 4365 )
	INEX_DISABLE_WARNING( 4191 )
#   include "RpcExStackTraceEngine.h"
	INEX_POP_WARNING
#elif defined ( INEX_PLATFORM_WINDOWS_64 )
#endif // #if INEX_PLATFORM_WINDOWS_32 || defined INEX_PLATFORM_WINDOWS_64

namespace inex {
namespace core {
namespace debug {

using inex::logging::Msg;

//inex::threading::atomic32_value_type  interlocked_increment	(inex::threading::atomic32_value_type & value )
//{
//	return									InterlockedIncrement( &value );
//}
//
//inex::threading::atomic32_value_type  interlocked_decrement	(inex::threading::atomic32_value_type & value )
//{
//	return									InterlockedDecrement( &value );
//}
//
//inex::threading::atomic32_value_type  interlocked_exchange	(inex::threading::atomic32_value_type & target, inex::threading::atomic32_value_type value )
//{
//	return									InterlockedExchange( &target, value );
//}
//
//inex::threading::atomic32_value_type  interlocked_compare_exchange	(inex::threading::atomic32_value_type & target, inex::threading::atomic32_value_type value, inex::threading::atomic32_value_type comparand )
//{
//	return									InterlockedCompareExchange(&target, value, comparand);

void 	dump_call_stack_trace ( )
{
	#if INEX_PLATFORM_WINDOWS_32 && ! defined INEX_PLATFORM_WINDOWS_64
	RpcExStackTraceEngine	call_stack;
	call_stack.Initialize	( );
	if ( RpcExStackTraceEngine::InitializationState::IS_Done == call_stack.GetInitializationState( ) )
		;//inex::core::logging::Msg ( "Call Stack Engine Initialized..." );

	string2048				buf;
	if ( S_OK == call_stack.WalkStack ( buf, sizeof( buf ), 8u ) )
		Msg					( "%s", buf );
	else
		Msg					( "!Unable to get current call stack trace." );
#elif ( INEX_PLATFORM_WINDOWS_64 )
#endif // #if INEX_PLATFORM_WINDOWS_32 || defined INEX_PLATFORM_WINDOWS_64
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
} // namespace inex

typedef LONG WINAPI UnhandledExceptionFilterType( struct _EXCEPTION_POINTERS *pExceptionInfo);

static	LONG WINAPI unhandled_exception_handler					( _EXCEPTION_POINTERS* const exception_information )
{
	if ( !inex::core::initialized( ) )
	{
		//inex::core::debug::platform::prologue_dump_call_stack	( exception_information );
		//inex::debug::terminate	( "" );
	}

	//if ( !inex::core::debug::bugtrap::initialized( ) )
	//	inex::core::debug::bugtrap::initialize	( );

	//prologue					( exception_information );
	//epilogue					( exception_information );

#if !defined(NDEBUG)
	return						( EXCEPTION_CONTINUE_SEARCH );
#endif // #if !defined(NDEBUG) || !INEX_PLATFORM_XBOX_360
}

int   unhandled_exception_filter	( int const exception_code, _EXCEPTION_POINTERS* const exception_information )
{
#ifdef DEBUG
	_clearfp					( );	// clear floating-point exceptions flag
#endif // #ifdef DEBUG

	UnhandledExceptionFilterType* current_handler = SetUnhandledExceptionFilter( 0 );
	if ( !current_handler )
		current_handler			= &unhandled_exception_handler;

	SetUnhandledExceptionFilter	( current_handler );

	pcstr	description			= "<no description>";
	switch ( exception_code ) {
		case EXCEPTION_ACCESS_VIOLATION : {
			description			= "ACCESS_VIOLATION : The thread attempts to read from or write to a virtual address for which it does not have access.";
			break;
		}
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED : {
			description			= "ARRAY_BOUNDS_EXCEEDED : The thread attempts to access an array element that is out of bounds, \r\nand the underlying hardware supports bounds checking.";
			break;
		}
		case EXCEPTION_BREAKPOINT : {
			description			= "BREAKPOINT : A breakpoint is encountered.";
			break;
		}
		case EXCEPTION_DATATYPE_MISALIGNMENT : {
			description			= "DATATYPE_MISALIGNMENT : The thread attempts to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries, 32-bit values on 4-byte boundaries, and so on.";
			break;
		}
		case EXCEPTION_FLT_DENORMAL_OPERAND : {
			description			= "FLT_DENORMAL_OPERAND : One of the operands in a floating point operation is denormal. A denormal value is one that is too small to represent as a standard floating point value.";
			break;
		}
		case EXCEPTION_FLT_DIVIDE_BY_ZERO : {
			description			= "FLT_DIVIDE_BY_ZERO : The thread attempts to divide a floating point value by a floating point divisor of 0 (zero).";
			break;
		}
		case EXCEPTION_FLT_INEXACT_RESULT : {
			description			= "FLT_INEXACT_RESULT : The result of a floating point operation cannot be represented exactly as a decimal fraction.";
			break;
		}
		case EXCEPTION_FLT_INVALID_OPERATION : {
#if 0
#				define PREFIX	"FLT_INVALID_OPERATION : "
			switch ( exception_information->ContextRecord->ExtendedRegisters[2] ) {
				case _FPE_INVALID : {
					description		= PREFIX "Invalid instruction (SNaN, probably, uninitialized variable)";
					break;
				}
				case _FPE_DENORMAL : {
					description		= PREFIX "Denormal occured";
					break;
				}
				case _FPE_ZERODIVIDE : {
					description		= PREFIX "The thread attempts to divide a floating point value by a floating point divisor of 0 (zero).";
					break;
				}
				case _FPE_OVERFLOW : {
					description		= PREFIX "The exponent of a floating point operation is greater than the magnitude allowed by the corresponding type.";
					break;
				}
				case _FPE_UNDERFLOW : {
					description		= PREFIX "The exponent of a floating point operation is less than the magnitude allowed by the corresponding type.";
					break;
				}
				case _FPE_INEXACT : {
					description		= PREFIX "The result of a floating point operation cannot be represented exactly as a decimal fraction.";
					break;
				}
				case _FPE_UNEMULATED : {
					description		= PREFIX "Unemulated instruction occured";
					break;
				}
				case _FPE_SQRTNEG : {
					description		= PREFIX "An attempt to take a square root from the negative floating point number";
					break;
				}
				case _FPE_STACKOVERFLOW : {
					description		= PREFIX "The stack has overflowed, because of a floating point operation.";
					break;
				}
				case _FPE_STACKUNDERFLOW : {
					description		= PREFIX "The stack has underflowed, because of a floating point operation.";
					break;
				}
				case _FPE_EXPLICITGEN : {
					description		= PREFIX "Someone raised signal SIGFPE or a corresponding exception";
					break;
				}
				default : {
					description		= PREFIX "An unknown floating point exception.";
					break;
				}
			}
#				undef PREFIX
#else // #if 0
			description			= "FLT_INVALID_OPERATION : An unknown floating point exception.";
#endif // #if 0
			break;
		}
		case EXCEPTION_FLT_OVERFLOW : {
			description			= "FLT_OVERFLOW : The exponent of a floating point operation is greater than the magnitude allowed by the corresponding type.";
			break;
		}
		case EXCEPTION_FLT_STACK_CHECK : {
			description			= "FLT_STACK_CHECK : The stack has overflowed or underflowed, because of a floating point operation.";
			break;
		}
		case EXCEPTION_FLT_UNDERFLOW : {
			description			= "FLT_UNDERFLOW : The exponent of a floating point operation is less than the magnitude allowed by the corresponding type.";
			break;
		}
		case EXCEPTION_ILLEGAL_INSTRUCTION : {
			description			= "ILLEGAL_INSTRUCTION : The thread tries to execute an invalid instruction.";
			break;
		}
		case EXCEPTION_INT_DIVIDE_BY_ZERO : {
			description			= "INT_DIVIDE_BY_ZERO : The thread tries to access a page that is not present, and the system is unable to load the page. For example, this exception might occur if a network connection is lost while running a program over a network.";
			break;
		}
		case EXCEPTION_INT_OVERFLOW : {
			description			= "INT_OVERFLOW : The result of an integer operation causes a carry out of the most significant bit of the result.";
			break;
		}
		case EXCEPTION_INVALID_DISPOSITION : {
			description			= "INVALID_DISPOSITION : An exception handler returns an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception.";
			break;
		}
		case EXCEPTION_NONCONTINUABLE_EXCEPTION : {
			description			= "NONCONTINUABLE_EXCEPTION : The thread attempts to continue execution after a non-continuable exception occurs.";
			break;
		}
		case EXCEPTION_PRIV_INSTRUCTION : {
			description			= "PRIV_INSTRUCTION : The thread attempts to execute an instruction with an operation that is not allowed in the current computer mode.";
			break;
		}
		case EXCEPTION_SINGLE_STEP : {
			description			= "SINGLE_STEP : A trace trap or other single instruction mechanism signals that one instruction is executed.";
			break;
		}
		case EXCEPTION_STACK_OVERFLOW : {
			description			= "STACK_OVERFLOW : The thread uses up its stack.";
			break;
		}
	}

	// here we catch Structured Exception in case
	// when raising exceptions is turned off in debugger
 	//if ( inex::debug::is_debugger_present() )
 	//	DEBUG_BREAK				( );

	//if ( inex::testing::is_testing() ) {
	//	inex::testing::on_exception	(inex::assert_untyped, description, exception_information, false);
	//	return					EXCEPTION_EXECUTE_HANDLER;
	//}

	//LOGI_ERROR					( "debug", "" );
	//LOGI_ERROR					( "debug", description );
	//LOGI_ERROR					( "debug", "" );

	//if ( show_dialog_for_unhandled_exceptions( ) )
	//{
	//	char						buffer[8192];
	//	strings::copy				(buffer, description);
	//	strings::append				(buffer, "\r\n\r\n");
	//	inex::core::debug::platform::on_error	(NULL, buffer, NULL, exception_information, inex::core::debug::platform::error_type_unhandled_exception);
	//}

	//if ( inex::testing::run_tests_command_line() || 
	//	 inex::build::print_build_id_command_line() )
 	//	inex::debug::terminate	( "" );
 	//else
	//	current_handler			( exception_information );

	return						( EXCEPTION_CONTINUE_SEARCH );
}

void inex::debug::protected_call							( protected_function_type* function_to_call, pvoid argument )
{
	// core::debug::set_thread_stack_guarantee	( );

	__try {
		( * function_to_call	)	( argument );
	}
	__except ( unhandled_exception_filter ( GetExceptionCode( ), GetExceptionInformation( ) ) ) {
	}
}