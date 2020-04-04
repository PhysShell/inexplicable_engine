#include "stdafx.h"
#include <inex/command_line.h>
#include <inex/core/ie_core.h>

namespace inex {
namespace command_line {

void    concat_command_line ( s32 argc, pstr* argv, pstr dest )
{
    string512 cmd_line              = { };
    for (   s32 i                   = 1;
            i                       < argc;
            ++                      i)
    {
        strcat                      ( cmd_line, argv [ i ] );
    }

    strcpy ( dest, cmd_line );
}

u32 	initialize ( pcstr line )
{
	u32			console_parameters_count	= 0;
    if          ( !strcmp( line, "" ) )   return console_parameters_count;
	// string512	console_parameters;

	// strncpy		( console_parameters, GetCommandLineA( ), sizeof ( console_parameters ) );
    
    pcstr       skip	                    = line; //+ strlen( line ) - 1;
    // for ( ; ; )
	// {
	// 	if ( *--skip == '"' )				break;
	// }
    // printf ( "skip = %s, len %d\n", skip, strlen( line ) );
	for ( ; *skip;  )
	{
        // printf ( "%c ", * skip );

		if ( *skip++ == '-' )				++console_parameters_count;
        
	}
    printf ( "" );
    return                                  console_parameters_count;
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

bool    check_key ( pcstr key )
{
    return              ( 0 != strstr( core::get_params( ), key ) ) ? 1 : 0;
}

} // namespace command_line
} // namespace inex
