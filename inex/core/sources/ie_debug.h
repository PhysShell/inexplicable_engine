#ifndef INEX_DEBUG_H_INCLUDED
#	define INEX_DEBUG_H_INCLUDED

namespace inex {
namespace debug {

// better make a wrapper on gettimeofday
// other most dumb way would be to add five hundred versions of
/*
template < typename R, typename P1, typename P2 >
float   benchmark ( R ( *function_pointer ) ( P1 , P2  ), P1 p1, P2 p2 )
{
	timeval 				time;
	double 					start, end;
	gettimeofday			( &time, nullptr );
	start 					= time.tv_usec;
	function_pointer        ( p1, p2 );
	gettimeofday			( &time, nullptr );
	end 					= time.tv_usec;
	return 					end - start;
}
*/

#if INEX_PLATFORM_LINUX
#	define BENCHMARK_RPOLOGUE 	timeval time; double start, end; gettimeofday( &time, nullptr ); start = time.tv_usec; 
#	define BENCHMARK_EPILOGUE	gettimeofday ( &time, nullptr ); end = time.tv_usec;
#elif INEX_PLATFORM_WINDOWS // #if INEX_PLATFORM_LINUX
#	error please specify benchmark routines for your platform 
#endif // #if INEX_PLATFORM_LINUX

// todo: dd debug/release #ifdef's
#define BENCHMARK( x )  BENCHMARK_RPOLOGUE		\
						x; 						\
						BENCHMARK_EPILOGUE 		\
						LOGGER ( "[benchmark][%s]\t\t: %f usec", #x , end - start )

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
