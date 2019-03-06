//-----------------------------------------------------------------------------
// File: ie_core.cpp
//
// Programmers:
//	Shell		- Feudor Shelipov
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include <inex/core/ie_core.h>
#include <inex/command_line.h>
#include "processor_info.h"
#include "ie_trims.h"
#include "ie_memory.h"
#include "memory_general_allocator.h"

namespace inex {
namespace core {

/*INEX_CORE_API*/  static pcstr	build_date;
/*INEX_CORE_API*/  static int	    build_id;
                string128       command_line_parameters		{ };

// or should I use global var?
//#ifndef USE_SINGLETON
pstr   INEX_CORE_API  get_params ( )
{
    return 			command_line_parameters;
}
//#endif //#ifndef USE_SINGLETON

#ifdef __GNUC__
s32	INEX_CCALL	_stricmp ( pcstr lhs, pcstr rhs )
{
	pstr str			= memory::ie_allocate< char >( std::strlen( lhs ) + 1 );
	pstr str2			= memory::ie_allocate< char >( std::strlen( rhs ) + 1 );
	pstr c				= str;

	std::strcpy			( str, lhs );
	std::strcpy			( str2, rhs );
    while ( *c && isalpha( *c ) )
    {
        *c              = tolower( *c );
        ++              c;
    }

	c					= str2;
    while ( *c && isalpha( *c ) )
    {
        *c              = tolower( *c );
        ++              c;
    }

	s32 result          = { std::strcmp( str, str2 ) };
	memory::ie_delete	( str );
	memory::ie_delete	( str2 );

	return 				result;
}
#endif // #ifdef __GNUC__

void	compute_build_id ( )
{
    pcstr month_id[ 12 ]  =
	{
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    u16 days_in_month[12] =
	{
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

	// if date is Feb 29, use 28 or you'll kill the algorithm
    u16 start_day			= 7;	// 7
    u16 start_month	    	= 9;	// September
    u16 start_year	    	= 2017;	// 2017

	build_date				= __DATE__;
	u16	days;
	u16	months				{ 0 };
	u16	years;
	string16 month;
	string256 buffer;
	strcpy					( buffer, __DATE__ );
	sscanf					( buffer, "%15s%hu%hu", month, &days, &years );

	for ( u8 i = 0; i < 12; i++ )
	{
		if ( _stricmp( month_id[ i ], month ) )
		{
			continue;
		}

		months				= i;
		break;
	}

    u8 leap_years           = 0;
    u16 count_current_year  = ( months > 0 ) ? years + 1 : years;

	for ( u32 i             =	start_month > 2 ? start_year + 1 : start_year;
            i               <	count_current_year;
            ++					i  )
	{
        if ( ( i % 4  == 0 && i % 100 != 0 ) || i % 400 == 0 )
        {
            ++leap_years;
        }
	}

	build_id				= ( years - start_year ) * 365 + days - start_day + leap_years;

	for ( u16 i = 0; i < months; ++i )
	{
		build_id			+= days_in_month[ i ];
	}

	for ( u16 i = 0; i < start_month - 1; ++i )
	{
		build_id			-= days_in_month[ i ];
	}
}

void	initialize ( s32 command_line_argument_count, pstr* command_line_values )
{
    // aV[0] is a path to application
    // and the cycle-var is s32 'cause it IS int main
    for ( s32 i = { 1 }; i < command_line_argument_count; ++i )
	{
        strcat			( command_line_parameters, command_line_values[ i ] );
    }

	memory::initialize		( );
    logging::initialize		( 0 != strstr( command_line_parameters, "-nolog" ) );
    compute_build_id	( );
    logging::Msg( "\"Inexplicable Engine\" demo build %d", build_id );
    logging::Msg( "Engine compilation date : %s\n", __DATE__ );

    threading::aquire_processor_information		( );
    //threading::get_cpu_feats		( );

    string32        temp	{ };
    if ( command_line::get_value_by_key( "-data", temp ) )
	{
        fs::initialize	( temp );
    }
	else
	{
#if INEX_PLATFORM_WINDOWS
		fs::initialize	( "gamedata/" );
#elif INEX_PLATFORM_LINUX // #if INEX_PLATFORM_WINDOWS
		fs::initialize	( "./gamedata/" );
#endif // #if INEX_PLATFORM_WINDOWS
	}

/* 	memory::platform::region	r;
	r.size						= 128;
	r.address					= memory::require_arena_from_os( r.size ); */
	memory::general_allocator 	g;
	g.initialize				( 0, 0, "test allocator" );
	pstr ptr 					= ( pstr )g.malloc_impl( 1 );
	// LOGGER( "* actually allocated!" );
	constexpr pcstr string 		= "'alloc test'";
	size_t len 					= std::strlen( string );
	strcpy 						( ptr, string );
	LOGGER( ptr ? ptr : "00000" );

	LOGGER( "string lies at:\t'%p'\n", ptr );
	g.free_impl					( ptr );
}

void	finalize ( )
{
    logging::Msg		( "*** Destroying core ***" );
    fs::finalize		( );
    memory::finalize    ( );
    logging::finalize   ( );
}

} // names core
} // namespace inex
