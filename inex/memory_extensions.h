////////////////////////////////////////////////////////////////////////////
//	Created 	: 30.10.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MEMORY_EXTENSIONS_H_INCLUDED
#	define MEMORY_EXTENSIONS_H_INCLUDED

#   include <memory>

#define INEX_DEFAULT_ALIGN_SIZE					8
#define INEX_DEFAULT_ALIGN						INEX_FORCE_ALIGNMENT( INEX_DEFAULT_ALIGN_SIZE )

namespace inex {
namespace memory {
	
constexpr u32 KiB	= 1024u;
constexpr u32 MiB	= KiB * KiB;
//enum { Kb = u32( 1024 ), Mb = 1024 * Kb };

} // namespace memory
} // namespace inex

#endif // #ifndef MEMORY_EXTENSIONS_H_INCLUDED