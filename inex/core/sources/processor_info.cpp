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
        if ( registers_information[ 3 ] & ( 1 << 24 ) )
        {
#if defined( _MSC_VER )
// #	define __try try
#	define __catch( x ) __except( x )
#else
#   define EXCEPTION_EXECUTE_HANDLER ...
// #	define __catch( x ) __catch
#endif // #if defined( _MSC_VER )
            __try
            {
                // using SSE instruction
				# if defined( __GNUC__ )
                __asm__ ("xorps %xmm0, %xmm1");
				# elif defined( _MSC_VER )  && !INEX_PLATFORM_WINDOWS_64 // #if defined( __GNUC__ )
__asm {
				xorps xmm1, xmm0
}
				# endif // #if defined( __GNUC__ )
		        strcat( features_available,", SSE" );
            }
            __catch ( EXCEPTION_EXECUTE_HANDLER ) { }
        }
	}

    if ( registers_information[ 3 ] & ( 1 << 26 ) )
	{
        __try
        {
                // using SSE2 instruction
				# if defined( __GNUC__ )
                __asm__ ("xorpd %xmm0, %xmm1");
				# elif defined( _MSC_VER )  && !INEX_PLATFORM_WINDOWS_64 // #if defined( __GNUC__ )
__asm {
				xorpd xmm1, xmm0
}
				# endif // #if defined( __GNUC__ )
                strcat( features_available,", SSE2" );
		}
		__catch ( EXCEPTION_EXECUTE_HANDLER ) { }
	}

    if ( registers_information[ 3 ] & ( 1 << 28 ) )
	{
		strcat( features_available,", HTT" );
	}

    if ( registers_information[ 3 ] & ( 1 << 23 ) )
	{
		strcat( features_available, ", MMX" );
	}

    u32 is_amd  =   0,  edx_reg     = 0;
	# if defined ( __GNUC__ )
    __asm (
        "movl $0x80000000h, %%eax\n\t"
        "cpuid\n\t"
        "cmp $0x80000000h, %%eax\n\t"
        "jc notamd\n\t"
        //      or 8000000 ???
        "movl  $0x80000001h, %%eax\n\t"
        "cpuid\n\t"
        "movl %%edx, %[edx]\n\t"
        "movl  $1, %[amd]\n\t"
        "notamd:\n\t"
        : [ edx ] "+m"( edx_reg ), [ amd ] "+m" ( is_amd )
    );
	# elif defined ( _MSC_VER ) && !_WIN64 // #if defined ( __GNUC__ )
__asm {
		xor			eax , eax
		cpuid
		cmp			eax , 0
		jc			notamd
		mov			eax , 1
		cpuid
		mov			edx_reg , edx
		mov			is_amd , 1
		notamd:
}
	# else // #if defined ( __GNUC__ )
	if ( !strcmp( "AuthenticAMD", ( const char * )vendor ) )	is_amd		= 1;
	# endif // #if defined ( __GNUC__ )

    // logging::Msg( "* AMD proc detected... %d %d", is_amd, edx_reg );

    if ( 0 != is_amd )
    {
        logging::Msg( "* AMD proc detected..." );
        if (    registers_information[ 3 ] & ( 1 << 23 ) &&
                edx_reg & ( 1 << 31 ) )
        {
            // seems like 3Dnow stopped existing in 2010+ amd procs
            logging::Msg( "\t* 3DNow!\n" );
        }
    }

    logging::Msg( "* Detected CPU: %s [%s]", brand, vendor );
    logging::Msg( "* CPU Features: %s", features_available );
    logging::Msg( "* CPU Cores: %d\n", ( registers_information[ 1 ] >> 16 ) & 0xFF );
    logging::Msg( "* Architecture detected: %s\n", ARCHITECTURE_STRING );
}

} // namespace threading
} // namespace inex
