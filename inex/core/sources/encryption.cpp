#include "pch.h"

#include "encryption.h"

#define CRC_POLYNOM         ( 0xedb88320 );

namespace inex {
namespace encryption {

static  u32                 polynom_values      [ 256 ];

/***
* void initialize_crc32(void)
*   - reversed algorithm computation of polynom values for each bit
****************************************************/
void    initialize_crc32 ( )
{
    for ( u32 i = 0; i <= 0xffu; ++i )
    {
        polynom_values[ i ] = i;
        for ( u32 j = 8; j > 0u; --j )
        {
            if ( polynom_values[ i ] & 1 )      { polynom_values[ i ] = ( polynom_values[ i ] >> 1 ) ^ CRC_POLYNOM; }
            else                                { polynom_values[ i ] >>= 1;                                        }
        }
    }
}

/***
* u32 crc32(pvoid const pointer, u32 length)
*   - reversed crc32 algorithm
* Entry:
*   - pointer:  address of buffer to get the control sum for
*   - lenght:   length of buffer
* Exit:
*   - crc32 hash for buffer 'pointer'
****************************************************/
u32     crc32 ( pvoid const pointer, u32 length )
{
    u32 crc         = 0xffffffff;
    s8* buffer      = static_cast< s8* >( pointer );

    while( length-- )
    {
        crc = polynom_values[ (crc ^ *buffer++ ) & 0xff ] ^ ( crc >> 8 );
    }

    // reverse the reversed
    crc             = ~crc;
    return          crc;

}

void	initialize ( )
{
	initialize_crc32	( );
}

} // namespace encryption
} // namespace inex
