#include "stdafx.h"

#if IE_PLATFORM_LINUX
#	include "processor_info.h"

namespace inex {
namespace core {
namespace CPU {
// We need to use GCC when it's not WINDOWS
// and VC++ if it is.
void	print_cpu_info ( )
{
//	FILE* hand;
//    char outstr     [ IE_MAX_PATH ];
//	pstmp tmp;
//
//    outstr[ IE_MAX_PATH - 1] =0;
//    hand			= 	popen( "cat /proc/cpuinfo | grep name", "r" );
//
//    if ( 0 == hand )
//	{
//        Msg( "Can't open /proc/cpuinfo! See _cpuid.cpp" );
//	}
//
//   fgets            	( outstr, FILENAME_MAX - 1, hand );
//
//   if ( 0 == ( tmp = strchr( outstr, ':' ) ) )
//   {
//        Msg( "Unrecognized /proc/cpuinfo format! See _cpuid.cpp" );
//        fclose      	( hand );
//#pragma message ( " TO make CPPcheck happy " )
//		return;
//    }
//
//   ++tmp;



// Don't see a point in this code. What is it for???
//   if(tmp == NULL)
//   {puts("Damn, format /proc/cpuinfo unrecognized");
//   fclose(hand);
//   return -2;}
//
//   tmp++;
//
//   if(tmp == NULL)
//   {puts("Damn, format /proc/cpuinfo unrecognized");
//   fclose(hand);
//   return -2;}
 //  fclose           	( hand );
   log::Msg( "* Detected CPU: %s", "" );
   log::Msg( "* CPU Features: read in procinfo" );
  // Msg("* CPU cores: \n");
}
} // namespace CPU
} // namespace core
} // namespace inex

#endif // #if IE_PLATFORM_LINUX
