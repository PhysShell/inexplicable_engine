#ifndef STDAFX_ENGINE_H_INCLUDED
#	define STDAFX_ENGINE_H_INCLUDED

//pragma once in PCH causes a warning in non-MSVC compilers
#ifdef _MSC_VER
//#	pragma once
//  stop send a thousands of warnings about a function being unsafe
#	define _CRT_SECURE_NO_WARNINGS
#endif // #ifdef _MSC_VER

#include <inex/extensions.h>

#endif // #ifndef STDAFX_ENGINE_H_INCLUDED
