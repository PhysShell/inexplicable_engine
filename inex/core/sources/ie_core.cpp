//-----------------------------------------------------------------------------
// File: ie_core.cpp
//
// Programmers:
//	Shell		- Feudor Shelipov
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include <inex/core/ie_core.h>
#include "processor_info.h"
#include "ie_trims.h"
#include "ie_memory.h"
//#include "application.h"
//#include "detail_test.h"

namespace inex {
namespace core {

/*IECORE_API*/  static pcstr	build_date;
/*IECORE_API*/  static int	    build_id;
                string128       command_line_parameters		{ };

// or should I use global var?
//#ifndef USE_SINGLETON
pstr   IECORE_API  get_params ( )
{
    return 			command_line_parameters;
}
//#endif //#ifndef USE_SINGLETON

#ifdef __GNUC__
int	IE_CCALL	_stricmp ( pcstr lhs, pcstr rhs )
{
	pstr str			= new char[ std::strlen( lhs ) + 1 ];
	pstr str2			= new char[ std::strlen( rhs ) + 1 ];
	pstr c				= str;

	std::strcpy			( str, lhs );
	std::strcpy			( str2, rhs );

	while ( *c )
	{
		if ( isalpha( *c ) )
		{
			*c			= tolower( *c );
		}

		++c;
	}

	c					=	str2;

	while ( *c )
	{
		if ( isalpha( *c ) )
		{
			*c			=	tolower( *c );
		}

		++c;
	}

	int result			= std::strcmp( str, str2 );
	delete [ ] 			str;
	delete [ ] 			str2;

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

	build_id				= ( years - start_year ) * 365 + days - start_day;

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

    log::initialize		( 0 != strstr( command_line_parameters, "-nolog" ) );
    compute_build_id	( );
    log::Msg( "\"Inexplicable Engine\" demo build %d", build_id );
    log::Msg( "Engine compilation date : %s\n", __DATE__ );

    CPU::print_cpu_info		( );
    CPU::get_cpu_feats		( );

    string32        temp	{ };
    if ( str::get_command_line_argument( "-data", temp ) )
	{
        fsmgr::initialize	( temp );
    }
	else
	{
		fsmgr::initialize	( "./gamedata/" );
	}
}

void	finalize ( )
{
    log::Msg ( "*** Destroying core ***" );
    fsmgr::finalize			( );
    memory::finalize       		( );
    log::finalize       		( );

}
} // names core
} // namespace inex





