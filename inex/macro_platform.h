#ifndef MACRO_PLATFORM_H_INCLUDED
#	define MACRO_PLATFORM_H_INCLUDED

////////////////////////////////////////////////////////////////////////////
// IE_PLATFORM_WINDOWS_32
////////////////////////////////////////////////////////////////////////////
#   ifdef IE_PLATFORM_WINDOWS_32
#   	error do not define IE_PLATFORM_WINDOWS_32 macro
#   endif // #ifdef IE_PLATFORM_WINDOWS_32

#   ifdef _WIN32
#   	define IE_PLATFORM_WINDOWS_32	1
#   endif // #ifdef _WIN32

////////////////////////////////////////////////////////////////////////////
// IE_PLATFORM_WINDOWS_64
////////////////////////////////////////////////////////////////////////////
#   ifdef IE_PLATFORM_WINDOWS_64
#   	error do not define IE_PLATFORM_WINDOWS_64 macro
#   endif // #ifdef IE_PLATFORM_WINDOWS_64

#   ifdef _WIN64
#   	define IE_PLATFORM_WINDOWS_64	1
//#   error   WIN64 IS DEAD!!!!
#   endif // #ifdef _WIN64

////////////////////////////////////////////////////////////////////////////
// IE_PLATFORM_WINDOWS
////////////////////////////////////////////////////////////////////////////
#	ifdef IE_PLATFORM_WINDOWS
#		error do not define IE_PLATFORM_WINDOWS macro
#	endif // #ifdef IE_PLATFORM_WINDOWS

#	if defined ( IE_PLATFORM_WINDOWS_32 ) || defined ( IE_PLATFORM_WINDOWS_64 )
#		define IE_PLATFORM_WINDOWS	1
#	else // #if defined ( IE_PLATFORM_WINDOWS_32 ) && !defined ( IE_PLATFORM_WINDOWS_64 )
#		define IE_PLATFORM_WINDOWS	0
#	endif // #if defined ( IE_PLATFORM_WINDOWS_32 ) && !defined ( IE_PLATFORM_WINDOWS_64 )

////////////////////////////////////////////////////////////////////////////
// IE_PLATFORM_LINUX
////////////////////////////////////////////////////////////////////////////
#   ifdef IE_PLATFORM_LINUX
#   	error do not define IE_PLATFORM_LINUX macro
#   endif // #ifdef IE_PLATFORM_LINUX

// android implies linux
#   if defined ( __linux__ ) && !defined ( __ANDROID__ )
#       define IE_PLATFORM_LINUX	1
#   else // #if defined ( __linux__ ) && !defined ( __ANDROID__ )
#       define IE_PLATFORM_LINUX    0
#   endif // #if defined ( __linux__ ) && !defined ( __ANDROID__ )

////////////////////////////////////////////////////////////////////////////
// check macros
////////////////////////////////////////////////////////////////////////////
#	if IE_PLATFORM_WINDOWS
#		if 	IE_PLATFORM_LINUX
#			error	error you cannot specify several target platforms
#		endif // #if IE_PLATFORM_LINUX
#	endif // #if IE_PLATFORM_WINDOWS

#endif // #ifndef IE_MACRO_PLATFORM_H_INCLUDED
