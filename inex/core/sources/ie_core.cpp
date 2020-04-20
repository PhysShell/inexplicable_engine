//-----------------------------------------------------------------------------
// File: ie_core.cpp
//
// Programmers:
//	Shell		- Feudor Shelipov
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include <inex/core/ie_core.h>
#include <inex/command_line.h>
#include <inex/threading_functions.h>
#include <inex/math_float3.h>
#include <inex/strings_functions.h>
#include "processor_info.h"
#include "ie_trims.h"
#include "ie_memory.h"
#include "memory_general_allocator.h"
#include "encryption.h"

namespace inex {
namespace fpu {
void    initialize  ( );
} // namespace fpu
namespace core {

/*INEX_CORE_API*/  static pcstr	build_date;
/*INEX_CORE_API*/  static int	    build_id;
                string128       command_line_parameters		{ };
                    static u32  s_processor_features        { };
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


// void	test ( )
// {
// 	memory::platform::region	r;
// 	r.size						= 128;
// 	r.address					= memory::require_arena_from_os( r.size );
// 	memory::general_allocator 	g;
// 	g.initialize				( 0, 0, "test allocator" );
//     g.dump_memory_statistics    ( );
// 	pstr ptr 					= g.malloc_impl< char >( 2 )
// 	, ptr2 						= g.malloc_impl< char >( 25 ),
// 		ptr3					= g.malloc_impl< char >( 21 ),
// 		ptr4					= g.malloc_impl< char >( 3 );
// 	//LOGGER( "* actually allocated!" );
// 	constexpr pcstr string 		= "1";
// 	strings::strncpy            ( ptr, string, strings::strlen( string ) );
//     strings::strncpy            ( ptr2, "2231", strings::strlen( "2231" ) );
//     strings::strncpy            ( ptr3, "342", strings::strlen( "342" ) );
// 	LOGGER( "s1 %s",  ptr ); LOGGER( "s2 %s", ptr2 ); LOGGER( "s3 %s", ptr3 ); LOGGER( "s4 %s", ptr4 );
//     g.dump_memory_statistics    ( );
// 	//LOGGER( "string1 lies at:\t'%p'\n", ptr );
// 	//LOGGER( "string2 lies at:\t'%p'\n", ptr2 );
//     g.free_impl					( ptr );
// 	g.free_impl					( ptr2 );
//     g.dump_memory_statistics    ( );
//     ptr                         = ( pstr )g.malloc_impl( 17 );
//     ptr2                        = ( pstr )g.malloc_impl( 3 );
//     g.dump_memory_statistics    ( );
// 	strcpy 						( ptr, string );
// 	strcpy 						( ptr2, "211111111111111111" );
//     g.free_impl                 ( ptr );
//     g.free_impl                 ( ptr2 );
//     g.free_impl                 ( ptr3 );
//     g.free_impl                 ( ptr4 );
// 	//LOGGER( "s1 %p",  ptr ); LOGGER( "s2 %p", ptr2 ); LOGGER( "s3 %p", ptr3 );
// }


void	initialize ( pcstr command_line_string )
{
    // aV[0] is a path to application
    // and the cycle-var is s32 'cause it IS int main
    //for ( s32 i = { 1 }; i < command_line_argument_count; ++i )
	//{
        strcat			( command_line_parameters, command_line_string );
    //}

	memory::initialize		( );
    logging::initialize		( 0 != strstr( command_line_parameters, "-nolog" ) );
    compute_build_id	( );
    logging::Msg( "\"Inexplicable Engine\" demo build %d", build_id );
    logging::Msg( "Engine compilation date : %s\n", __DATE__ );
    // logging::Msg( "\n... Command line initialized: '%s'", command_line_parameters );
    s_processor_features    = threading::aquire_processor_information		( );
    fpu::initialize         ( );
    encryption::initialize_crc32    ( );
    pstr buff               = memory::ie_allocate< char >( 4 );
    strings::strncpy        ( buff, "123", sizeof( "123" ) );
    LOGGER( "Str!:\t%s", buff );
    u32 crc                 = encryption::crc32( buff, 3 );
    LOGGER( "CRC!:\t0x%08x", crc );
    memory::ie_delete       ( buff );
    //threading::get_cpu_feats		( );

    string128       temp	{ };
    if ( command_line::get_value_by_key( "-data", temp ) )
	{
        fs::initialize	( temp );
    }
	else
	{
		fs::initialize	( "gamedata/" );
	}

    // test		( );

    logging::Msg( "* %d Hz clock on your machine", threading::clock_cycle_per_second( ) );
	logging::Msg( "* L1 Cache line size: %d bits\n", threading::cache_line_size( ) );
}

void	finalize ( )
{
    logging::Msg		( "*** Destroying core ***" );
    fs::finalize		( );
    memory::finalize    ( );
    logging::finalize   ( );
}

} // names core

namespace fpu {

/***
*
* void initialize ( )
*
* Entry:
*
*
*
* Exit:
*
*
*
****************************************************/
void    initialize ( )
{
    LOGGER( "Initializing FPU..." );
    math::MATH g_CM;
    g_CM.matrix_multiple    = math::multiple_pure;

    // if ( command_line::check_key( "-pure_math" ) )
    if ( !command_line::check_key( "-no_sse" ) && core::s_processor_features & 1 )
    {
        g_CM.matrix_multiple = math::multiple_sse;
    }

    float f1                = 1.0f,
            f2              = 0.1f;

    float* pf1              = memory::ie_allocate< float >( sizeof ( float ) );
    float* pf2              = memory::ie_allocate< float >( sizeof ( float ) );
    *pf1    = *pf2          = .1f;
    g_CM.matrix_multiple( pf1, pf2 );
    memory::ie_delete       ( pf1 );
    memory::ie_delete       ( pf2 );

    // LOGGER ( "pf1=%f, pf2=%f", *pf1, *pf2 );

	ASSERT_S            ( math::fdEPS != 0.f );
	logging::Msg        ( "Epsilon is: '%0.*f'", 8, math::fdEPS );
}
} // namespace fpu

} // namespace inex
