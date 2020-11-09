#include "pch.h"
#include <inex/command_line.h>
#include <inex/core/ie_core.h>

static string128	s_command_line;

namespace inex {
namespace command_line {

void 	initialize ( pcstr const line )
{
	strcat		( s_command_line, line );

	u32	parameters_count	= 0;
    if ( !strcmp( line, "" ) )
	{
		LOGGER	( "* [command line][info]: empty command line" );
		return;
	}

	for ( pcstr skip = line; *skip;  )
	{
		if ( *skip++ == '-' )
			++parameters_count;
	}

    LOGGER	( "* [command line][info]: '%d' parameters: '%s'", parameters_count, line );
}

void    concat_command_line ( s32 argc, pstr* argv, pstr dest )
{
    string512 cmd_line	= { 0 };

    for ( s32 i = 1; i < argc; ++i )
        strcat			( cmd_line, argv [ i ] );

    strcpy ( dest, cmd_line );
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
    if ( !( p = strstr( s_command_line, k ) ) )
		return			nullptr;

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

bool    check_key ( pcstr key )
{
    return              ( 0 != strstr( s_command_line, key ) ) ? 1 : 0;
}

} // namespace command_line
} // namespace inex
