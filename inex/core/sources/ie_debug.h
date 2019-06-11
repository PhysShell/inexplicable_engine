#ifndef INEX_DEBUG_H_INCLUDED
#	define INEX_DEBUG_H_INCLUDED

namespace inex {
namespace debug {

INEX_CORE_API
float           benchmark               ( void ( *function_pointer )( ) );

INEX_CORE_API
void INEX_CCALL	fatal					( 	pcstr 	file,
											u32 	line,
											pcstr 	func,
											pcstr 	expr,
											pcstr 	format,
											...
										);
void			aquire_macros			( 	pcstr 	file,
											u32 	line,
											pcstr 	func,
											pcstr 	expr
										);
pcstr		    error2string			( u32 code );
void 			dump_call_stack_trace 	( );

} // namespace debug
} // namespace inex

#endif // #ifndef INEX_DEBUG_H_INCLUDED
