#include "stdafx.h"
#include <inex/command_line.h>
#include <inex/core/ie_core.h>

namespace inex {
namespace command_line {

void	initialize ( )
{
/*
	u32			console_parameters_count	= 0;
	string512	console_parameters;

	strncpy		( console_parameters, GetCommandLineA( ), sizeof ( console_parameters ) );
	pstr skip	= console_parameters + strlen( console_parameters ) - 1;
	for ( ; ; )
	{
		if ( *--skip == '"' )				break;
	}

	for ( ; *skip ; )
	{
		if ( *++skip == '-' )				++console_parameters_count;
	}
*/
}

void	copy_argument ( pcstr src, pstr dst, u8 separator )
{
    pcstr p			=	strchr( src, '=' );
    ASSERT_D( p, "Error while parsing cmd-argument '%s'.", src );

    size_t n		=	{ };
    while ( *p && *p != separator )
	{
		dst[ n++ ] 	= 	*p++;
	}

    dst[ n ]  		=	0;
}

pstr	get_value_by_key ( pcstr k, pstr v )
{
    pcstr p;
    if ( !( p = strstr( core::get_params( ), k ) ) )
    {
		return			nullptr;
	}

    size_t n			= { };
    p   				= strchr( p,'=' );
    // maybe check if the '=' relates exactly to the key we need?
    ASSERT_D( p, "Couldn't read value of the cmd-line argument '%s'. Did you forget '='?", k );
    ++p;
    while ( *p && *p != '-' )
	{
		 v[ n++ ]		= *p++;
	}
	
    v[ n ]  			= 0;
    return  			v;
}

} // namespace command_line
} // namespace inex
