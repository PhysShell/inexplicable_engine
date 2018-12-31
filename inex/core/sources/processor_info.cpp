#include "stdafx.h"
#include "processor_info.h"
#include "cpuid_internal.h"

namespace inex {
namespace threading {

void	aquire_processor_information ( )
{
	s32 registers_information[ 4 ]	= { };
	// read vendor string
	detail::cpuid_fill( registers_information, static_cast< s32 >( 0x80000000 ) );

	s8 vendor[ 13 ]					= { 0 };
    *( reinterpret_cast< s32* >( vendor ) )		= registers_information[ 1 ]; // EBX
    *( reinterpret_cast< s32* >( vendor ) + 1 ) = registers_information[ 3 ]; // EDX
    *( reinterpret_cast< s32* >( vendor ) + 2 ) = registers_information[ 2 ]; // ECX
    * ( vendor + 12 )				= 0;

	s8 brand[ 0x40 ];
	u32 extended_information			=  static_cast< u32 >( registers_information[ 0 ] );
	for ( u32 i = 0x80000000; i <= extended_information; ++i )
	{
		detail::cpuid_fill     		( registers_information, static_cast< s32 >( i ) );
		switch ( i )
		{
			case 0x80000002: memcpy ( brand,		registers_information, sizeof( registers_information ) ); break;
			case 0x80000003: memcpy ( brand + 16,	registers_information, sizeof( registers_information ) ); break;
			case 0x80000004: memcpy ( brand + 32,	registers_information, sizeof( registers_information ) ); break;
		}
	}

	detail::cpuid_fill( registers_information, 1 ); // read cpu features
    string128 features_available { 0 };
    if ( registers_information[ 2 ] & ( 1 << 0 ) )
	{
		strcat( features_available, "SSE3" );
	}

    if ( registers_information[ 2 ] & ( 1 << 9 ) )
	{
		strcat( features_available,", SSSE3" );
	}

    if ( registers_information[ 2 ] & ( 1 << 19 ) )
	{
		strcat( features_available,", SSE4.1" );
	}

    if ( registers_information[ 2 ] & ( 1 << 20 ) )
	{
		strcat( features_available, ", SSE4.2" );
	}

    if ( registers_information[ 3 ] & ( 1 << 0 ) )
	{
		strcat( features_available,", FPU" );
	}

    if ( registers_information[ 3 ] & ( 1 << 25 ) )
	{
		strcat( features_available,", SSE" );
	}

    if ( registers_information[ 3 ] & ( 1 << 26 ) )
	{
		strcat( features_available,", SSE2" );
	}

    if ( registers_information[ 3 ] & ( 1 << 28 ) )
	{
		strcat( features_available,", HTT" );
	}

    if ( registers_information[ 3 ] & ( 1 << 23 ) )
	{
		strcat( features_available, ", MMX" );
	}

    logging::Msg( "* Detected CPU: %s [%s]", brand, vendor );
    logging::Msg( "* CPU Features: %s", features_available );
    logging::Msg( "* CPU Cores: %d\n", ( registers_information[ 1 ] >> 16 ) & 0xFF );
}

} // namespace threading
} // namespace inex
