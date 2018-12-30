#include "stdafx.h"
#include "processor_info.h"
#include "cpuid_internal.h"

namespace inex {
namespace threading {

u32 max_cpuid_level;
char vendor[ 12 ]; // not ASCIIZ !
u32 model, brand, feat0, feat1;

void	cpuid1 ( )
{
#ifdef _MSC_VER
#	pragma message ( "NO CPUID for MSVC" )
#else // #ifdef _MSC_VER
    u32 eax, ebx, ecx, edx;

    asm volatile
    (
        "movl $0, %%eax\n\t"
        "cpuid\n\t"
        : "=a"( eax ),"=b"( ebx ),"=c"( ecx ),"=d"( edx )
    );

    max_cpuid_level = eax;

    for ( int i = 0; i < 4; ++i)
	{
		vendor[ 0 + i ] = char( ( ebx >> ( 8 * i ) ) & 0xFF );
	}

    for ( int i = 0; i < 4; ++i)
	{
		vendor[ 4 + i ]	= char( ( edx >> ( 8 * i ) ) & 0xFF );
	}

    for ( int i = 0; i < 4; ++i)
	{
        vendor[ 8 + i ] = char( ( ecx >> ( 8 * i ) ) & 0xFF );
	}

    asm volatile
    (
        "movl $1,%%eax\n\t"
        "cpuid\n\t"
        :"=a"( eax ),"=b"( ebx ),"=c"( ecx ),"=d"( edx )
    );

    model			= eax;
    brand			= ebx;
    feat0			= ecx;
    feat1			= edx;
#endif // #ifdef _MSC_VER
}

void	get_cpu_feats  ( )
{
#ifdef _MSC_VER
    logging::Msg( "* CPU Features: %s", "Unknown Processor" );
    logging::Msg( "* CPU Cores: %d\n", 0 );
#else // #ifdef _MSC_VER
    cpuid1( );
    string128 fts { 0 };

    if ( feat0 & ( 1 << 0 ) )
	{
		strcat( fts, "SSE3" );
	}

    if ( feat0 & ( 1 << 9 ) )
	{
		strcat( fts,", SSSE3" );
	}

    if ( feat0 & ( 1 << 19 ) )
	{
		strcat( fts,", SSE4.1" );
	}

    if ( feat0 & ( 1 << 20 ) )
	{
		strcat( fts, ", SSE4.2" );
	}

    if ( feat1 & ( 1 << 0 ) )
	{
		strcat( fts,", FPU" );
	}

    if ( feat1 & ( 1 << 25 ) )
	{
		strcat( fts,", SSE" );
	}

    if ( feat1 & ( 1 << 26 ) )
	{
		strcat( fts,", SSE2" );
	}

    if ( feat1 & ( 1 << 28 ) )
	{
		strcat( fts,", HTT" );
	}

    if ( feat1 & ( 1 << 23 ) )
	{
		strcat( fts, ", MMX" );
	}

    logging::Msg( "* threading Features: %s", fts );
    logging::Msg( "* threading Cores: %d\n", ( brand >> 16 ) & 0xFF );
#endif // #ifdef _MSC_VER
}
} // namespace threading
} // namespace inex
