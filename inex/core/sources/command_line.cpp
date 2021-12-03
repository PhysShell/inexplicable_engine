#include "pch.h"
#include <inex/command_line.h>
#include <inex/core/ie_core.h>

static string128			s_command_line;


namespace inex {
namespace command_line {

static std::vector< key > 	s_command_line_keys			= 	nullptr;
static bool 				s_command_line_initialized 	= 	false;
static core::engine * 		s_engine 					=	nullptr;

key::key (pcstr full_name, pcstr short_name, pcstr category, pcstr description, pcstr argument_description) : 
																	m_full_name(full_name), 
																	m_short_name(short_name), 
																	m_category(category),
																	m_type(type_uninitialized), 
																	m_number_value(0.f), 
																	m_description(description),
																	m_argument_description(argument_description)
{
	//debug::preinitialize						( );
	//logging::preinitialize					( );
	debug::protected_call						( protected_key_construct, this );
}

void   key::protected_construct ()
{
	R_ASSERT									(m_full_name);
	R_ASSERT									(m_short_name);

	pcstr i	= NULL;
	for ( i = m_short_name; * i; ++i )
		if ( is_delimiter(* i, " \t=-") )
			break;

	R_ASSERT	(!* i, wrong_key_assert_message, m_short_name);

	for ( i = m_full_name; * i; ++i )
		if ( is_delimiter(* i, " \t=-") )
			break;

	R_ASSERT	(!* i, wrong_key_assert_message, m_full_name);
	R_ASSERT	(strings::length(m_short_name) + strings::length(m_full_name) > 0, empty_key_assert_message);

	if ( !s_command_line_keys )
	{
		bind_pointer_to_buffer_mt_safe	(	s_command_line_keys, 
											s_command_line_keys_buffer, 
											s_command_line_keys_creation,
											bind_pointer_to_buffer_mt_safe_placement_new_predicate() );
	}

	s_command_line_keys->push_back			(this);
	++s_command_line_keys_count;
}

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
