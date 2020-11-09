#include "pch.h"
#include "build_extensions.h"
#include <inex/core/sources/ie_memory.h>
//#include "debug_internal.h"

static char s_print_build_id_string[]	=	"print_build_id";
//static inex::command_line::key			s_print_build_id	(s_print_build_id_string, "", "", "prints build id to stdout");
static pcstr s_build_date				= __DATE__;
static int	 s_build_id;

using namespace inex;

//s32	INEX_CCALL	_stricmp ( pcstr lhs, pcstr rhs )
//{
//	pstr str			= memory::ie_allocate< char >( std::strlen( lhs ) + 1 );
//	pstr str2			= memory::ie_allocate< char >( std::strlen( rhs ) + 1 );
//	pstr c				= str;
//
//	std::strcpy			( str, lhs );
//	std::strcpy			( str2, rhs );
//    while ( *c && isalpha( *c ) )
//    {
//        *c              = tolower( *c );
//        ++              c;
//    }
//
//	c					= str2;
//    while ( *c && isalpha( *c ) )
//    {
//        *c              = tolower( *c );
//        ++              c;
//    }
//
//	s32 result          = { std::strcmp( str, str2 ) };
//	memory::ie_delete	( str );
//	memory::ie_delete	( str2 );
//
//	return 				result;
//}

static u32 build_id				( u16 const day, u16 const month, u16 const year, pcstr current_date )
{
	pcstr month_id[ 12 ]	= { "Jan", "Feb", "Mar", "Apr", "May", "Jun","Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    u16 days_in_month[ 12 ]	= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// if date is Feb 29, use 28 or you'll kill the algorithm
    u16 start_day			= day;		// 7
    u16 start_month	    	= month;	// September
    u16 start_year	    	= year;		// 2017

	u16	days;
	u16	months				{ 0 };
	u16	years;
	string16 current_month;
	string256 buffer1		{ 0 };
	strcpy					( buffer1, current_date );
	sscanf					( buffer1, "%15s%hu%hu", current_month, &days, &years );

	for ( u8 i = 0; i < 12; i++ )
	{
		if ( _stricmp( month_id[ i ], current_month ) )
			continue;

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

	s_build_id				= ( years - start_year ) * 365 + days - start_day + leap_years;

	for ( u16 i = 0; i < months; ++i )
	{
		s_build_id			+= days_in_month[ i ];
	}

	for ( u16 i = 0; i < start_month - 1; ++i )
	{
		s_build_id			-= days_in_month[ i ];
	}

	return					s_build_id;
}

u32 inex::build::calculate_build_id ( pcstr current_date )
{
	return						build_id( 7, 9, 2017, current_date );
}

void inex::build::preinitialize	( pcstr const build_date )
{
	s_build_date				= build_date;
}

void inex::build::initialize	( core::engine *  )
{
	u32 const id	=	calculate_build_id ( s_build_date );
    logging::Msg( "\"Inexplicable Engine\" demo build %d", id );
    logging::Msg( "Engine compilation date : %s\n", __DATE__ );

}

pcstr inex::build::build_date	( )
{
	return					s_build_date;
}