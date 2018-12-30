#include "stdafx.h"

#include "processor_info.h"
//#	include "_cpuid_internal.h"
#ifndef __GNUC__
#   include <intrin.h>
#endif // #ifdef INEX_PURE_GNUC

namespace inex {
namespace threading {

// We need to use GCC when it's not WINDOWS
// and VC++ if it is.
void	print_cpu_info ( )
{
#ifndef INEX_PURE_GNUC
   // Get extended ids.
   s32 proc_info[ 4 ]	=	{ };
   __cpuid          	( 	proc_info,
							static_cast< s32 >( 0x80000000 ) );

   u32 ext_info			= 	static_cast< u32 >( proc_info[ 0 ] );

   // Get the information associated with each extended ID.
   char brand[ 0x40 ] = { 0 };
   for ( u32 i = 0x80000000; i <= ext_info; ++i )
   {
		__cpuid     	( proc_info, static_cast< s32 >( i ) );
		switch ( i )
		{
			case 0x80000002: memcpy ( brand, proc_info, sizeof( proc_info ) ); break;
			case 0x80000003: memcpy ( brand + 16, proc_info, sizeof( proc_info ) ); break;
			case 0x80000004: memcpy ( brand + 32, proc_info, sizeof( proc_info ) ); break;
		}
    }

    char vendor[ 13 ] =	{ 0 };
    __cpuid         	( proc_info, 0 );
    *( reinterpret_cast< s32* >( vendor ) )		= proc_info[ 1 ]; // EBX
    *( reinterpret_cast< s32* >( vendor ) + 1 ) = proc_info[ 3 ]; // EDX
    *( reinterpret_cast< s32* >( vendor ) + 2 ) = proc_info[ 2 ]; // ECX

    vendor[ 12 ]	=	0;
    logging::Msg( "* Detected CPU: %s [%s]", brand, vendor );
#else // #ifndef INEX_PURE_GNUC
    logging::Msg( "* Detected CPU: Unknown Processor" );
#endif // #ifndef INEX_PURE_GNUC
}

} // namespace threading
} // namespace inex


