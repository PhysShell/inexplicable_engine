////////////////////////////////////////////////////////////////////////////
//	Created 	: 04.04.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef STRINGS_FUNCTIONS_H_INCLUDED
#   define STRINGS_FUNCTIONS_H_INCLUDED

namespace inex {
namespace strings {

// str family usually tend to be slower than printf family
inline u64      strlen  ( pcstr const source )                                {   return  ( source ) ? snprintf( nullptr, 0, "%s", source ) + 1 : 0;                                        }
inline pstr     strncpy ( pstr destination, pcstr const source, u64 size )    {   u64 copied = snprintf( destination, size, "%s", source ); return  ( copied ) ? destination : nullptr;     }

} // namespace strings
} // namespace inex

#endif // #ifndef STRINGS_FUNCTIONS_H_INCLUDED
