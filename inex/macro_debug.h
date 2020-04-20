#ifndef MACRO_DEBUG_H_INCLUDED
#	define MACRO_DEBUG_H_INCLUDED

#if  defined (UNREACHABLE_CODE)
#	error please do not define  UNREACHABLE_CODE
#endif // #if defined  (UNREACHABLE_CODE)

#if defined( _MSC_VER )
#   define FUNCNAME __FUNCSIG__
#elif defined ( __GNUC__ ) // #if defined(_MSC_VER)
#   define FUNCNAME __PRETTY_FUNCTION__
#endif // #if defined(_MSC_VER)

#define DEBUG_INFO			__FILE__, __LINE__, FUNCNAME

//Sincerely waiting for __VA_OPT__ to come out in C++20a.
//#define ASSERT(expr, ...) if(!(a))do{FATAL(#a__VA_OPT__(,) __VA_ARGS__);}while(0)
#define FATAL( expr, ... ) 	inex::debug::fatal( DEBUG_INFO, #expr, __VA_ARGS__ )
#define ASSERT_D( a, ... ) 	if ( !( a ) )do { FATAL( #a, __VA_ARGS__ ); } while ( 0 )
#define ASSERT_S( a )		if ( !( a ) )do { FATAL( #a, nullptr ); } while ( 0 )

#define STATIC_ASSERT( x, y )	typedef char sassert[ !( x ) ? 0 : -1 ]

// use it when 'x' is just a single value
#define VERIFY(x)       	ASSERT_S( x )

#ifdef DEBUG
#	define NODEFAULT		inex::debug::Debug.do_exit( "unreachable reached :-(" )
#	define UNREACHABLE_CODE	NODEFAULT
#else // #ifdef DEBUG
#	define NODEFAULT		COMPILER_NODEFAULT
#	define UNREACHABLE_CODE	NODEFAULT
#endif // #ifdef DEBUG



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
