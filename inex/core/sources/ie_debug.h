#ifndef IE_DEBUG_H_INCLUDED
#	define IE_DEBUG_H_INCLUDED


namespace inex {
namespace core{
namespace debug {

void IE_CCALL	fatal					( 	pcstr 	file,
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
} // namespace core
} // namespace inex

#endif // #ifndef IE_DEBUG_H_INCLUDED
