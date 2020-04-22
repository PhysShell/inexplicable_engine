#ifndef OS_WINDOWS_H_INCLUDED
#	define OS_WINDOWS_H_INCLUDED


// Exclude rarely-used stuff from Windows headers
// for details, see https://msdn.microsoft.com/ru-ru/library/6dwk3a1z(v=vs.90).aspx
#   define VC_EXTRALEAN
#   define WIN32_LEAN_AND_MEAN
#   define NOGDICAPMASKS
//#	define NOSYSMETRICS
#   define NOMENUS
#   define NOICONS
#   define NOKEYSTATES
#   define NODRAWTEXT
#   define NOMEMMGR
#   define NOMETAFILE
#   define NOSERVICE
#   define NOCOMM
#   define NOHELP
#   define NOPROFILER
#   define NOMCX
// GCC defines it in os_defines.h
#   ifndef NOMINMAX
#   	define NOMINMAX
#   endif // #ifndef NOMINMAX

#	include <windows.h>

#endif // #ifdef OS_WINDOWS_H_INCLUDED
