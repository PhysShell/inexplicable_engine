#ifndef MACRO_DEBUG_H_INCLUDED
#	define MACRO_DEBUG_H_INCLUDED

#if defined( _MSC_VER )
#   define FUNCNAME __FUNCSIG__
#elif defined ( __GNUC__ ) // #if defined(_MSC_VER)
#   define FUNCNAME __PRETTY_FUNCTION__
#endif // #if defined(_MSC_VER)

#define DEBUG_INFO			__FILE__, __LINE__, FUNCNAME

// to be sure
#define ASSERTIONS_ENABLED
#define UNREACHABLE_CODE_ENABLED

#ifdef DEBUG
#	define ASSERTIONS_ENABLED
#	define UNREACHABLE_CODE_ENABLED
#endif // #ifdef DEBUG

// Sincerely waiting for __VA_OPT__ to come out in C++20a.
// #define ASSERT(expr, ...) if(!(a))do{FATAL(#a__VA_OPT__(,) __VA_ARGS__);}while(0)
#ifdef ASSERTIONS_ENABLED
#	define SLOW_ASSERT
#	define FATAL( expr, ... ) 	inex::debug::fatal( DEBUG_INFO, #expr, __VA_ARGS__ )
#	define ASSERT_D( a, ... ) 	if ( !( a ) )do { FATAL( #a, __VA_ARGS__ ); } while ( 0 )
#	define ASSERT_S( a )		if ( !( a ) )do { FATAL( #a, nullptr ); } while ( 0 )
#	define VERIFY( x )       	ASSERT_S( x )
#else
#	define FATAL( expr, ... )
#	define ASSERT_D( a, ... )
#	define ASSERT_S( a )
#	define VERIFY( x )
#endif // #ifdef ASSERTIONS_ENABLED

#ifdef __cplusplus
#	if __cplusplus >= 201103L
#		define STATIC_ASSERT( x, y )	static_assert( x, #y );
#	else
#		define STATIC_ASSERT( x, y )	typedef char sassert[ !( x ) ? 0 : -1 ]
#	endif // #ifdef if __cplusplus >= 201103L
#endif // #ifdef __cplusplus

#if  defined ( UNREACHABLE_CODE )
#	error please do not define  UNREACHABLE_CODE
#endif // #if defined  (UNREACHABLE_CODE)

#ifdef UNREACHABLE_CODE_ENABLED
#	define _UNREACHABLE_CODE( description, ... ) ASSERT_S			( !#description ); COMPILER_NODEFAULT;
#	define UNREACHABLE_CODE( ... )				_UNREACHABLE_CODE	( "unreachable code accessed!", ##__VA_ARGS__ )
#	define NODEFAULT( ... )						_UNREACHABLE_CODE	( "unintended default case accessed!", ##__VA_ARGS__ )
#	define NOT_IMPLEMENTED( ... )				_UNREACHABLE_CODE	( "functionality has not been implemented yet!", ##__VA_ARGS__ )
#else // #ifdef UNREACHABLE_CODE_ENABLED
#	define NODEFAULT		COMPILER_NODEFAULT
#	define UNREACHABLE_CODE	NODEFAULT
#endif // #ifdef UNREACHABLE_CODE_ENABLED



//#ifdef DEBUG
//#	define VERIFY(expression)	do { if (!(expression)) throw; } while (0)
//#	define NODEFAULT			do { __debugbreak(); } while (0)
//#else // #ifdef DEBUG
//#	define VERIFY(expression)	do {} while (0)
//#	define NODEFAULT			__assume(0)
//#endif // #ifdef DEBUG

//#define		PRINT(A)		std::cout << #A << " = [" << (A) << "]\n";

//#define     DEBUG_VAR(t,n)  " " QUOTE(t) " " QUOTE(n)" "

#endif // #ifndef MACRO_DEBUG_H_INCLUDED
