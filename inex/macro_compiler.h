#ifndef MACRO_COMPILER_H_INCLUDED
#	define MACRO_COMPILER_H_INCLUDED

#ifdef _MSC_VER
#	if !defined( _MT )
#		error Please enable multi-threaded library...
#	endif // #if !defined(_MT)
#endif // #ifdef _MSC_VER

// don't forget that conventions were removed from msvc64 ( or not only )
// work around GCC compiler
#if defined __GNUC__ && !defined ( __clang__ )
#   define __cdecl __attribute__( ( __cdecl__ ) )
#endif // #if defined __GNUC__ && !defined ( __clang__ )

//try __MINGW64__
#if defined ( _MSC_VER ) && ( _MSC_VER >= 1900 ) \
    || ( defined ( __GNUC__ ) && ( __GNUC__ >= 7 ) )
#   define  IE_FILESYSTEM_SUPPORTED
#else // #if defined ( _MSC_VER ) || ( __GNUC__ >= 7 )
#   pragma  message( "Use custom filesystem..." )
#endif  // #if defined ( _MSC_VER ) || ( __GNUC__ >= 7 )

#endif // #ifndef MACRO_COMPILER_H_INCLUDED
 //<bool Recursive> template

// typename std::conditional<Recursive, ...
