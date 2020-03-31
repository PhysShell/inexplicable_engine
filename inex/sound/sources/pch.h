// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

// PRECOMPILED HEADER MUST BE INCLUDED FIRST!
#ifndef PCH_H_INCLUDED
#	define PCH_H_INCLUDED

// pragma once in precompiled header causing a warning in non-MSVC compilers
#   ifdef _MSC_VER
//#   pragma once
#	    define _CRT_SECURE_NO_WARNINGS
//# pragma warning (disable:4661)
#   endif // #ifdef _MSC_VER


#   include <inex/extensions.h>
#endif // #ifndef PCH_H_INCLUDED

// PCH stops here
#ifdef _MSC_VER
#   pragma hdrstop
#endif // #ifdef _MSC_VER

// and other headers can be included
