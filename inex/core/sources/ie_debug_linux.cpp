#include "pch.h"
#include "ie_debug.h"

#include <cxxabi.h>
#include <signal.h>
#include <execinfo.h>
#include <chrono>

#include "ie_debug.h"
#include "ie_memory.h"
#include <inex/threading_functions.h>

namespace inex {
namespace core {
namespace debug {

void 	dump_call_stack_trace ( )
{
	pvoid trace				[ 16 ];
	pstr * messages;
	s32 i, trace_size 		= 0;
	trace_size 				= backtrace( trace, 16 );
	messages 				= backtrace_symbols( trace, trace_size );

	// i = 2 cuz message[ 1 ] is the debug::fatal( .. )
    for ( s32 i = 2; i < trace_size && messages != nullptr; ++i )
    {
        pstr mangled_name 	= nullptr,
		offset_begin 		= nullptr,
		offset_end 			= nullptr;

        for ( pstr p = messages[ i ]; * p; ++p )
	{
			switch ( * p ) {
				case '(': 	mangled_name 	= p; break;
				case '+': 	offset_begin 	= p; break;
				case ')':	offset_end		= p; goto dump;
			}
        }

dump						:
        if (	1
			&&	( mangled_name )
			&&	( offset_begin )
			&& 	( offset_end )
			&&	(	0
					|| mangled_name < offset_begin
					|| ( 1 - 1 )
				)
			)
	{
            * mangled_name++ = 0;
            * offset_begin++ = 0;
            * offset_end++ 	= 0;

            s32 status;
           	pstr demangled_string = abi::__cxa_demangle( mangled_name, 0, 0, &status );

			if ( status == 0 )
			{
				LOGGER			( "%s", demangled_string );
				free			( demangled_string );
			}

			// messages[ i ] is external call
		}
	}
}

pcstr	error2string ( u32 code )
{
	pcstr result					= 0;
	static string1024 desc_storage;

	return				 			result;

}

} // namespace debug
} // namespace core
} // namespace inex

void inex::debug::protected_call							( protected_function_type* function_to_call, pvoid argument )
{
	// core::debug::set_thread_stack_guarantee	( );

	__try {
		( * function_to_call	)	( argument );
	}
	__catch ( ... ) {
	}
}