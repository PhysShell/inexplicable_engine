#ifndef INEX_DEBUG_H_INCLUDED
#	define INEX_DEBUG_H_INCLUDED

#	include <functional>
#	include <utility>
#	include <type_traits>

namespace inex {
namespace debug {

namespace detail {
template <
	typename		ReturnType, 
	typename		Function, 
	typename ...	ForwardedArguments
>
inline
ReturnType	wrapper ( Function function, ForwardedArguments && ... forwarded_arguments )
{
	return					function( std::forward< ForwardedArguments >( forwarded_arguments ) ... );
}

template < typename Function, typename ... ForwardedArguments >
struct helper
{
	using type				= typename std::result_of< Function( ForwardedArguments... ) >::type;
}; // struct helper

} // namespace detail

#if INEX_PLATFORM_LINUX
template < typename Function, typename ... ForwardedArguments >
void   benchmark ( Function function, ForwardedArguments ... forwarded_arguments )
{
	timeval 				time;
	double 					start, end;
	gettimeofday			( &time, nullptr );
	start 					= time.tv_usec;
	wrapper< helper< Function, ForwardedArguments... >::type >				( function, forwarded_arguments ... );
	gettimeofday			( &time, nullptr );
	end 					= time.tv_usec;
	LOGGER					( "[benchmark][-]\t\t: %f usec", end - start );
}
#elif INEX_PLATFORM_WINDOWS // #if INEX_PLATFORM_LINUX

template < typename Function, typename ... ForwardedArguments >
float   benchmark ( Function function, ForwardedArguments && ... forwarded_arguments )
{
	LARGE_INTEGER			frequency;
	LARGE_INTEGER			start, end;
	float					elapsed_time;

	ASSERT_S				( QueryPerformanceFrequency( &frequency ) );
	QueryPerformanceCounter	( &start );
	
	detail::wrapper< detail::helper< Function, ForwardedArguments ... >::type >				( function, forwarded_arguments ... );
	QueryPerformanceCounter	( &end );
	elapsed_time			= ( float )( end.QuadPart - start.QuadPart ) / frequency.QuadPart;

	return					elapsed_time;
}
#endif // #if INEX_PLATFORM_LINUX

// todo: dd debug/release #ifdef's
#define BENCHMARK( x, ... ) float b = inex::debug::benchmark( x, __VA_ARGS__ ); LOGGER ( "[benchmark][%s]\t\t: %f usec", #x , b )

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
