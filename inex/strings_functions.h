////////////////////////////////////////////////////////////////////////////
//	Created 	: 04.04.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef STRINGS_FUNCTIONS_H_INCLUDED
#   define STRINGS_FUNCTIONS_H_INCLUDED

namespace inex {
namespace strings {

// str family usually tend to be slower than printf family
inline u64      strlen  ( pcstr const source )									{   return  ( source ) ? snprintf( nullptr, 0, "%s", source ) + 1 : 0;											}
inline pstr     strncpy ( pstr destination, pcstr const source, u64 size )		{   u64 copied = snprintf( destination, size, "%s", source ); return  ( copied ) ? destination : nullptr;		}
inline u32		length	( pcstr string )										{	return ( u32 )strlen( string );																				}
inline s32		compare	( pcstr left, pcstr right )								{	return strcmp( left, right );																				}
inline bool		equals	( pcstr left, pcstr right )								{	return ! compare( left, right );																			}
inline pcstr	tolower	( pcstr const source )								
				{
					u32 length			= inex::strings::length( source );
					pstr result			= inex::memory::ie_allocate< char >( length );
					for ( u32 i = 0; i < length; ++i )
					{
						result[ i ]		-= ( result[ i ] >= 'A' && result[ i ] <= 'Z') ? ('A' - 'a') : 0;
					}

					return				result;
				}
} // namespace strings
} // namespace inex

#endif // #ifndef STRINGS_FUNCTIONS_H_INCLUDED
