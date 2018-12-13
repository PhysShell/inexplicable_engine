#include "stdafx.h"

#if IE_PLATFORM_WINDOWS

#include "processor_info.h"
//#	include "_cpuid_internal.h"
#ifndef IE_PURE_GNUC
#   include <intrin.h>
#endif // #ifdef IE_PURE_GNUC

namespace inex {
namespace core {
namespace CPU {

// We need to use GCC when it's not WINDOWS
// and VC++ if it is.
void	print_cpu_info ( )
{
#ifndef IE_PURE_GNUC
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

       // Interpret CPU brand string and cache information.
        if ( i == 0x80000002 )
		{
            memcpy  	( brand, proc_info, sizeof( proc_info ) );
        }
		else if ( i == 0x80000003 )
		{
            memcpy  	( brand + 16, proc_info, sizeof( proc_info ) );
        }
		else if ( i == 0x80000004 )
		{
            memcpy  	( brand + 32, proc_info, sizeof( proc_info ) );
        }
    }

    //CPUInfo[0]=CPUInfo[1]=CPUInfo[2]=CPUInfo[3]=0;
    // Get vendor
    char vendor[ 13 ] =	{ 0 };
    __cpuid         	( proc_info, 0 );
	// notation *( reinterpret_cast< s32* >( vendor ) )
	// is the equivalent of
	// ( reinterpret_cast< s32* >( vendor ) )[ 0 ]
    *( reinterpret_cast< s32* >( vendor ) )		= proc_info[ 1 ]; // EBX
    *( reinterpret_cast< s32* >( vendor ) + 1 ) = proc_info[ 3 ]; // EDX
    *( reinterpret_cast< s32* >( vendor ) + 2 ) = proc_info[ 2 ]; // ECX


    vendor[ 12 ]	=	0;
    log::Msg( "* Detected CPU: %s [%s]", brand, vendor );
#else // #ifndef IE_PURE_GNUC
    log::Msg( "* Detected CPU: unavailable due to IE_PURE_GNUC" );
#endif // #ifndef IE_PURE_GNUC
}

} // namespace CPU
} // namespace core
} // namespace inex
#endif //#if IE_PLATFORM_WINDOWS


