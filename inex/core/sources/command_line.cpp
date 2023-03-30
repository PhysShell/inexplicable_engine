#include "pch.h"
#include <inex/command_line.h>
#include <inex/core/core.h>
#include <inex/construction.h>
#include <vector>
static string128			s_command_line;


namespace inex {
namespace command_line {

static std::vector< key * > * s_command_line_keys					= 	nullptr;
static bool 				s_command_line_initialized 			= 	false;
static core::engine * 		s_engine 							=	nullptr;
static u32					s_command_line_keys_count			=	0;
#if INEX_PLATFORM_WINDOWS_64
static char					s_command_line_keys_buffer				[sizeof( threading::atomic32_value_type ) * CHAR_BIT];
#elif INEX_PLATFORM_WINDOWS_32 // #if INEX_PLATFORM_WINDOWS_64
static char					s_command_line_keys_buffer				[sizeof( threading::atomic32_value_type ) * CHAR_BIT / 2];
#endif // #if INEX_PLATFORM_WINDOWS_64
static threading::atomic32_type	s_command_line_keys_creation	=	0;

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

void   protected_key_construct (pvoid keyptr_)
{
	key * const keyptr	=	(key *)keyptr_;
	keyptr->protected_construct ();
}

static
bool   is_delimiter	(char const value, pcstr delimiters)
{
	return					!!strchr(delimiters, value);
}

void   key::protected_construct ()
{
	ASSERT_S									(m_full_name);
	ASSERT_S									(m_short_name);

	pcstr i	= NULL;
	for ( i = m_short_name; * i; ++i )
		if ( is_delimiter(* i, " \t=-") )
			break;

	pcstr const wrong_key_assert_message	=	"command_line_key with delimiter characters specified (they are not supported): \"%s\"";
	pcstr const empty_key_assert_message	=	"command_line_key with empty shortname specified";

	ASSERT_D	(!* i, wrong_key_assert_message, m_short_name);

	for ( i = m_full_name; * i; ++i )
		if ( is_delimiter(* i, " \t=-") )
			break;

	ASSERT_D	(!* i, wrong_key_assert_message, m_full_name);
	ASSERT_D	(strings::length(m_short_name) + strings::length(m_full_name) > 0, empty_key_assert_message);

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

//struct key_initializator
//{
//	void operator () (key * const command_line_key, pcstr key_name, pcstr key_value)
//	{
//		if ( !command_line_key )
//			return;
//
//		if ( strings::equal(command_line_key->full_name(), key_name) ||
//			 strings::equal(command_line_key->short_name(), key_name) )
//		{
//			command_line_key->initialize	(key_value);
//		}
//	}
//};

//template <class Predicate>
//void   iterate_keys (Predicate predicate)
//{
//	CURE_ASSERT								(s_command_line_ready, return, "please run initialize first");
//	pcstr command_line					=	g_command_line.c_str();
//	for ( pcstr current = command_line; * current; ++ current )
//	{
//		if ( is_whitespace(* current) )
//			continue;
//
//		if ( * current != '-' )
//		{
//			if ( !s_command_line_error.length() )
//				s_command_line_error.assignf	("expected '-' symbol and not %c at %s(%d)", 
//												 * current, command_line, current - command_line);
//			continue;
//		}
//
//		++ current;
//
//		if ( ! * current )
//		{
//			if ( !s_command_line_error.length() )
//				s_command_line_error.assignf	("last command line key is empty: %s", command_line);
//			break;
//		}
//
////		bool fullname_specified			=	false;
//		if ( * current == '-' )
//		{
////			fullname_specified			=	true;
//			++ current;
//
//			if ( ! * current )
//			{
//				if ( !s_command_line_error.length() )
//					s_command_line_error.assignf	("last command line key is empty: %s", command_line);
//				break;
//			}
//		}
//
//		pcstr	key_name_start			=	current;
//		for ( ; * current; ++ current )
//		{
//			if ( is_whitespace(* current) || * current == '=' )
//				break;
//		}
//
//		fixed_string512		key_name		(key_name_start, current);
//
//		if ( * current != '=' )
//		{
//			predicate						(find_key(key_name.c_str()), key_name.c_str(), NULL);
//			continue;
//		}
//		++ current;
//
//		if ( ! * current )
//		{
//			if ( !s_command_line_error.length() )
//				s_command_line_error.assignf	("key value is empty: %s", key_name_start);
//			break;
//		}
//
//		pcstr key_value_start			=	current;
//		bool search_quote				=	false;
//		if ( * current == '"' )
//		{
//			search_quote				=	true;				
//			++ current;
//			key_value_start				=	current;
//		}
//
//		for ( ; * current; ++ current )
//		{
//			if ( search_quote )
//			{
//				if ( * current == '"' && * (current - 1) != '\\' )
//					break;
//			}
//			else if ( is_whitespace(* current) )
//				break;
//		}
//
//		fixed_string512	key_value			(key_value_start, current);
//		if ( search_quote )
//			++ current;
//
//		predicate							(find_key(key_name.c_str()), key_name.c_str(), key_value.c_str());
//	}
//}

void   key::initialize ()
{
	m_type								=	type_unset;

	//iterate_keys							(key_initializator());
}

bool   key::is_set ()
{
	if ( m_type == type_uninitialized )
		initialize				();

	return						m_type != type_unset;
}

bool   key::is_set_as_string			(pcstr * out_value)
{
	if ( m_type == type_uninitialized )
		initialize							();

	if ( m_type == type_unset )
		return								false;

	if ( out_value )
		* out_value						=	m_string_value;
	return									true;
}

bool   key::is_set_as_number			(float * out_value)
{
	if ( m_type == type_uninitialized )
		initialize				();

	if ( m_type == type_unset )
		return					false;

	ASSERT_D						(m_type == type_number, "given value is not convertible to number: %s", m_string_value);
	//CURE_ASSERT					(m_type == type_number, return 0.f, "given value is not convertible to number: %s", m_string_value.c_str());

	if ( out_value )
		* out_value			=	m_number_value;
	return						true;
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
