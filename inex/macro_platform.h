#ifndef MACRO_PLATFORM_H_INCLUDED
#	define MACRO_PLATFORM_H_INCLUDED

////////////////////////////////////////////////////////////////////////////
// INEX_PLATFORM_WINDOWS_32
////////////////////////////////////////////////////////////////////////////
#   ifdef INEX_PLATFORM_WINDOWS_32
#   	error do not define INEX_PLATFORM_WINDOWS_32 macro
#   endif // #ifdef INEX_PLATFORM_WINDOWS_32

#   ifdef _WIN32
#   	define INEX_PLATFORM_WINDOWS_32	1
#   endif // #ifdef _WIN32

////////////////////////////////////////////////////////////////////////////
// INEX_PLATFORM_WINDOWS_64
////////////////////////////////////////////////////////////////////////////
#   ifdef INEX_PLATFORM_WINDOWS_64
#   	error do not define INEX_PLATFORM_WINDOWS_64 macro
#   endif // #ifdef INEX_PLATFORM_WINDOWS_64

#   ifdef _WIN64
#   	define INEX_PLATFORM_WINDOWS_64	1
//#   error   WIN64 IS DEAD!!!!
#   endif // #ifdef _WIN64

////////////////////////////////////////////////////////////////////////////
// INEX_PLATFORM_WINDOWS
////////////////////////////////////////////////////////////////////////////
#	ifdef INEX_PLATFORM_WINDOWS
#		error do not define INEX_PLATFORM_WINDOWS macro
#	endif // #ifdef INEX_PLATFORM_WINDOWS

#	if defined ( INEX_PLATFORM_WINDOWS_32 ) || defined ( INEX_PLATFORM_WINDOWS_64 )
#		define INEX_PLATFORM_WINDOWS	1
#	else // #if defined ( INEX_PLATFORM_WINDOWS_32 ) && !defined ( INEX_PLATFORM_WINDOWS_64 )
#		define INEX_PLATFORM_WINDOWS	0
#	endif // #if defined ( INEX_PLATFORM_WINDOWS_32 ) && !defined ( INEX_PLATFORM_WINDOWS_64 )

////////////////////////////////////////////////////////////////////////////
// INEX_PLATFORM_LINUX
////////////////////////////////////////////////////////////////////////////
#   ifdef INEX_PLATFORM_LINUX
#   	error do not define INEX_PLATFORM_LINUX macro
#   endif // #ifdef INEX_PLATFORM_LINUX

// android implies linux
#   if defined ( __linux__ ) && !defined ( __ANDROID__ )
#       define INEX_PLATFORM_LINUX	1
#   else // #if defined ( __linux__ ) && !defined ( __ANDROID__ )
#       define INEX_PLATFORM_LINUX    0
#   endif // #if defined ( __linux__ ) && !defined ( __ANDROID__ )

////////////////////////////////////////////////////////////////////////////
// check macros
////////////////////////////////////////////////////////////////////////////
#	if INEX_PLATFORM_WINDOWS
#		if 	INEX_PLATFORM_LINUX
#			error	error you cannot specify several target platforms
#		endif // #if INEX_PLATFORM_LINUX
#	endif // #if INEX_PLATFORM_WINDOWS

#endif // #ifndef INEX_MACRO_PLATFORM_H_INCLUDED
