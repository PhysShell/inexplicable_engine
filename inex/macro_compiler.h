#ifndef MACRO_COMPILER_H_INCLUDED
#	define MACRO_COMPILER_H_INCLUDED

#	ifdef _MSC_VER
#		if !defined( _MT )
#			error Please enable multi-threaded library...
#		endif // #if !defined(_MT)
#	endif // #ifdef _MSC_VER

#	ifdef _MSC_VER
#		define IE_PUSH_WARNINGS( )		__pragma ( warning ( push ) )
#		define IE_DISABLE_WARNING( x )	__pragma ( warning ( disable : x ) )
#		define IE_POP_WARNINGS( )		__pragma ( warning ( pop ) )
/** Check if there's such a thing in GCC/CLang
 * #pragma clang diagnostic push
 * #pragma clang diagnostic ignored "-Warc-performSelector-leaks"
 * #pragma clang diagnostic pop
 */
#	endif //#ifdef _MSC_VER

// don't forget that conventions were removed from msvc64 ( or not only )
// work around GCC compiler
#	if defined __GNUC__ && !defined ( __clang__ )
#	   define __cdecl __attribute__( ( __cdecl__ ) )
#	endif // #if defined __GNUC__ && !defined ( __clang__ )

#	if defined ( _MSC_VER ) && ( _MSC_VER >= 1900 ) \
			|| ( defined ( __GNUC__ ) && ( __GNUC__ >= 7 ) )
#	   define  IE_FILESYSTEM_SUPPORTED
#	else // #if defined ( _MSC_VER ) || ( __GNUC__ >= 7 )
#	   pragma  message( "Use custom filesystem..." )
#	endif  // #if defined ( _MSC_VER ) || ( __GNUC__ >= 7 )

#endif // #ifndef MACRO_COMPILER_H_INCLUDED

