#ifndef MACRO_EXTENSIONS_H_INCLUDED
#	define MACRO_EXTENSIONS_H_INCLUDED

#define SIZEOF_ARRAY( arrayName, elementType )	( sizeof( arrayName ) / sizeof( elementType ) )

//#ifndef DEBUG
//#	error "inex TO ALL: DEBUG MODE ONLY ALLOWED "
//#else
//#	include	"debug_output.h"
//#	pragma message ( "DEBUG MODE IS ACTIVE" )
//#endif

#include "macro_platform.h"
#include "macro_string.h"
#include "macro_debug.h"
#include "macro_declarations.h"
#include "macro_log.h"
#include "macro_unreferenced_parameter.h"
#include "macro_compiler.h"

#endif // #ifndef MACRO_EXTENSIONS_H_INCLUDED
