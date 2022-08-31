#ifndef INEX_DEBUG_H_INCLUDED
#	define INEX_DEBUG_H_INCLUDED

#	include <functional>
#	include <utility>
#	include <type_traits>
#	include <excpt.h>
#   if INEX_PLATFORM_LINUX
#       include <sys/time.h>
#   endif // #if INEX_PLATFORM_LINUX

namespace inex {
namespace core {
namespace debug {

struct engine;

namespace detail {
template <
	typename		return_type,
	typename		function,
	typename ...	parameters_pack
>

inline
return_type	wrapper ( function function_to_benchmark, parameters_pack && ... parameters )
{
	return					function_to_benchmark( std::forward< parameters_pack >( parameters ) ... );
}

template < typename function, typename ... parameters_pack >
struct helper
{
	using type				= typename std::result_of< function( parameters_pack... ) >::type;
}; // struct helper

} // namespace detail

#	if INEX_PLATFORM_LINUX
template < typename function, typename ... parameters_pack >
void   benchmark ( function function_to_benchmark, parameters_pack && ... parameters )
{
	timeval 				time;
	double 					start, end;
	gettimeofday			( &time, nullptr );
	start 					= time.tv_usec;
	detail::wrapper< detail::helper< function, parameters_pack ... >::type >				( function_to_benchmark, parameters ... );
	gettimeofday			( &time, nullptr );
	end 					= time.tv_usec;
}
#	elif INEX_PLATFORM_WINDOWS // #if INEX_PLATFORM_LINUX

template < typename function, typename ... parameters_pack >
float   benchmark ( function function_to_benchmark, parameters_pack && ... parameters )
{
	LARGE_INTEGER			frequency;
	LARGE_INTEGER			start, end;
	float					elapsed_time;

	ASSERT_S				( QueryPerformanceFrequency( &frequency ) );
	QueryPerformanceCounter	( &start );

	detail::wrapper< detail::helper< function, parameters_pack ... >::type >				( function_to_benchmark, parameters ... );
	QueryPerformanceCounter	( &end );
	elapsed_time			= ( float )( end.QuadPart - start.QuadPart ) / frequency.QuadPart;

	return					elapsed_time;
}
#	endif // #if INEX_PLATFORM_LINUX

// todo: dd debug/release #ifdef's
#	define BENCHMARK( x, ... ) do { float b = inex::debug::benchmark( x, __VA_ARGS__ ); LOGGER ( "[benchmark][%s]\t\t: %f usec", #x , b ); } while ( 0 )

void 			initialize 				( debug::engine * engine );
void 			postinitialize			( );
void 			finalize 				( );

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
} // namespace core
} // namespace inex

namespace inex {
namespace debug {

typedef void protected_function_type		( pvoid );
INEX_CORE_API
void		protected_call					( protected_function_type* function_to_call, pvoid argument );

} // namespace debug
} // namespace inex

#endif // #ifndef INEX_DEBUG_H_INCLUDED
