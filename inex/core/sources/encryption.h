////////////////////////////////////////////////////////////////////////////
//	Created 	: 06.04.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_ENCRYPTION_H_INCLUDED
#	define INEX_ENCRYPTION_H_INCLUDED

#include "pch.h"

#include "encryption.h"

namespace inex {
namespace encryption {

void	initialize			( );

void    initialize_crc32    ( );
u32     crc32               ( pvoid const pointer, u32 length );

#pragma todo( "compile-time constexpr for const strings" )

// static  u32                 predefined_polynoms [ 256 ] =
// {
//     0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
//     0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
//     0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
//     0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
//     0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
//     0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
//     0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
//     0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
//     0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
//     0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
//     0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
//     0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
//     0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
//     0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
//     0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
//     0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d
// };

/***
* constexpr u32 crc32(const pstr string)
*   - recursive reversed compile-time crc32 algorithm
* Entry:
*   - string:  compile-time allocated string
* Exit:
*   - crc32 hash for buffer 'string'
****************************************************/
// constexpr
// u32     crc32 ( const pstr string )
// {
//     u32 crc         = 0xffffffff;
//     pstr buffer     = const_cast< pstr >( string );

//     while( length-- )
//     {
//         crc = predefined_polynoms[ (crc ^ *buffer++ ) & 0xff ] ^ ( crc >> 8 );
//     }

//     // reverse the reversed
//     return          crc;    
// }
} // namespace encryption
} // namespace inex


#endif //#ifndef INEX_ENCRYPTION_H_INCLUDED
