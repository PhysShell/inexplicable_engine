#ifndef MACRO_COMPILER_H_INCLUDED
#	define MACRO_COMPILER_H_INCLUDED

#	ifdef _MSC_VER
#		if !defined( _MT )
#			error Please enable multi-threaded library...
#		endif // #if !defined(_MT)
#	endif // #ifdef _MSC_VER

#ifdef __linux__
#   define INEX_ALIGNOF __alignof__
#else // #ifdef __linux__
#   define INEX_ALIGNOF __alignof
#endif // #ifdef __linux__

#	ifdef _WIN32
#       ifdef _MSC_VER
# 		    define INEX_DLL_IMPORT	__declspec ( dllimport )
#		    define INEX_DLL_EXPORT	__declspec ( dllexport )
#	    elif defined ( _MSC_VER ) // #ifdef _MSC_VER
#		    define INEX_DLL_IMPORT	__attribute__ ( ( dllimport ) )
#		    define INEX_DLL_EXPORT	__attribute__ ( ( dllexport ) )
#       endif // #ifdef _MSC_VER
#   else // #ifdef _WIN32
#		define INEX_DLL_IMPORT
#		define INEX_DLL_EXPORT
#	endif // #ifdef _WIN32

#	ifdef _MSC_VER
/** Check if there's such a thing in GCC/CLang
 * #pragma clang diagnostic push
 * #pragma clang diagnostic ignored "-Warc-performSelector-leaks"
 * #pragma clang diagnostic pop
**/
#		define INEX_PUSH_WARNINGS( )		        __pragma ( warning ( push ) )
#		define INEX_DISABLE_WARNING( x )	        __pragma ( warning ( disable : x ) )
#		define INEX_POP_WARNINGS( )		            __pragma ( warning ( pop ) )
#       define COMPILER_PURE_VIRTUAL_DESTRUCTOR( x ) virtual ~x( ) = 0 { }

#       define INEX_FORCE_ALIGNMENT( x )            _declspec ( align( x ) )

#   else // #ifdef _MSC_VER
#       define COMPILER_PURE_VIRTUAL_DESTRUCTOR( x ) virtual ~x( ) { }

#       define INEX_FORCE_ALIGNMENT( x )            __attribute__ ( ( __aligned__ ( ( x ) ) ) )

#	endif //#ifdef _MSC_VER

// don't forget that conventions were removed from msvc64 ( or not only )
// work around GCC compiler
#	if defined __GNUC__ && !defined ( __clang__ )
#	   define __cdecl __attribute__( ( __cdecl__ ) )
#	endif // #if defined __GNUC__ && !defined ( __clang__ )

#	if defined ( _MSC_VER ) && ( _MSC_VER >= 1900 ) \
			|| ( defined ( __GNUC__ ) && ( __GNUC__ >= 7 ) )
#	   define  INEX_FILESYSTEM_SUPPORTED
#	else // #if defined ( _MSC_VER ) || ( __GNUC__ >= 7 )
#	   pragma  message( "Use custom filesystem..." )
#	endif  // #if defined ( _MSC_VER ) || ( __GNUC__ >= 7 )

#endif // #ifndef MACRO_COMPILER_H_INCLUDED

/*
#include <iostream>
#include <cstdlib>

template<typename ... TYPES>
class pack
{};

typedef pack< float, double, long double, unsigned short, unsigned int,
    unsigned long, unsigned long long, short, int, long, long long > primitive_types;

template<typename L, typename R>
class smaller
{
    public:
        static const bool value = sizeof(L) < sizeof(R);
};

template<typename, typename>
class pack_cat;

template<typename... L, typename... R>
class pack_cat<pack<L...>, pack<R...>>
{
    public:
        typedef pack<L..., R...> type;
};

template<template<typename, typename> class, typename, typename>
class pack_merge;

template<template<typename, typename> class MF, typename HL, typename... TL, typename HR, typename... TR>
class pack_merge<MF, pack<HL, TL...>, pack<HR, TR...>>
{
    public:
        typedef typename std::conditional<MF<HR, HL>::value,
                typename pack_cat<pack<HR>, typename pack_merge<MF, pack<HL, TL...>, pack<TR...>>::type>::type,
                typename pack_cat<pack<HL>, typename pack_merge<MF, pack<TL...>, pack<HR, TR...>>::type>::type>::type type;
};

template<template<typename, typename> class MF, typename H, typename... T>
class pack_merge<MF, pack<H, T...>, pack<>>
{
    public:
        typedef pack<H, T...> type;
};

template<template<typename, typename> class MF, typename... R>
class pack_merge<MF, pack<>, pack<R...>>
{
    public:
        typedef pack<R...> type;
};

template<typename>
class halve;

template<typename A, typename B, typename... T>
class halve<pack<A, B, T...>>
{
    public:
        typedef typename pack_cat<pack<A>, typename halve<pack<T...>>::L>::type L;
        typedef typename pack_cat<pack<B>, typename halve<pack<T...>>::R>::type R;
};

template<typename T>
class halve<pack<T>>
{
    public:
        typedef pack<T> L;
        typedef pack<> R;
};

template<>
class halve<pack<>>
{
    public:
        typedef pack<> L;
        typedef pack<> R;
};

template<template<typename, typename> class MF, typename P>
class pack_sort
{
    private:
        typedef typename halve<P>::L L;
        typedef typename halve<P>::R R;

    public:
        typedef typename pack_merge<MF, typename pack_sort<MF, L>::type, typename pack_sort<MF, R>::type>::type type;
};

template<template<typename, typename> class MF, typename H>
class pack_sort<MF, pack<H>>
{
    public:
        typedef pack<H> type;
};

template<template<typename, typename> class MF>
class pack_sort<MF, pack<>>
{
    public:
        typedef pack<> type;
};

template<typename>
class pack_get_last;

template<typename H, typename... T>
class pack_get_last<pack<H, T...>>
{
public:
    typedef typename pack_get_last<pack<T...>>::type type;

};

template<typename H>
class pack_get_last<pack<H>>
{
    public:
        typedef H type;
};

typedef typename pack_get_last<typename pack_sort<smaller, primitive_types>::type>::type largest;

template < typename T1, typename T2 >
struct is_same
{
    constexpr
    static bool value     = sizeof ( T1 ) == sizeof ( T2 );
}; // struct is_same

    INEX_ALIGNOF( largest );
    STATIC_ASSERT( __CHAR_BIT__ != 8, "WTF?!" );
*/