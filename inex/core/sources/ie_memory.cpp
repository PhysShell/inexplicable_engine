#include "pch.h"

#include "ie_memory.h"
#include <iostream>
#include <vector>
#include <memory>

namespace inex {
namespace memory {

void	preinitialize ( )
{
}

//#define DEBUG_MEMORY_MANAGER

void    initialize ( )
{
    // it's 16 in linux
    //STATIC_ASSERT ( INEX_ALIGNOF( long double ) != 8, "WTF" );
}

// GCC's typeid string needs to be demangled first
// to get readable string
	using logging::Msg;
#ifdef __GNUG__
#   include <cxxabi.h>
#   include <stdlib.h>

pstr	dem_typeid ( pcstr type )
{
    s32	status;
    pstr rname;
    rname			= abi::__cxa_demangle( type, 0, 0, &status );
    return 			rname;
}
#else // #ifdef __GNUG__
pstr	dem_typeid ( pcstr type )
{
	size_t len			{ strlen( type ) + 1 };
    pstr rname			{ };
    rname			= 	static_cast< pstr >( std::malloc( len ) );
	strcpy				( rname, type );
    rname[ len - 1 ]= 	0;

    return  		rname;
}
#endif // #ifdef __GNUG__

struct memory_entity
{
    pstr	type_name;
    pvoid   address;
}; // struct memory_entity

static	std::vector< memory_entity > memory_contents	= { };
using	memory_debug_iterator							= std::vector< memory_entity >::iterator;

void    memory_register_pointer ( pvoid pointer, pcstr type )
{
    //_mdbg_info      tmp;
    //tmp.ptr         =P;
    //tmp.str         =dem_typeid(type);
    memory_contents.push_back	( { dem_typeid( type ), pointer } );

    //Msg( "*Alloc: %s, addr %p", memory_contents.back( ).type_name, memory_contents.back( ).address );

}

void    memory_unregister_pointer ( pvoid pointer )
{

    if ( memory_contents.empty( ) )
	{
		//Msg( "empty" );
		return;
	}

    memory_debug_iterator			it		= memory_contents.begin( );
    memory_debug_iterator			end_it	= memory_contents.end( );

#pragma TODO( "DON'T write msg when debugging log's file writer\ncuz after destructor call it's not operating anymore" )

	//Msg( "looking for: %p", P );

	for ( ; it != end_it; ++it )
	{
		//Msg( "*memory: Type: %s, addr: %p. elements %d", ( *I ).str, ( *I ).ptr, mdbg.size( ) );
        if ( ( *it ).address == pointer )
		{
			//Msg( "*Dealloc: Type: %s, addr: %p", ( *it ).type_name, ( *it ).address );
			break;
        }
    }

	//ASSERT_S( P != nullptr );

    ASSERT_D(	it != end_it,
				"Possibly double-delete of %p"
                "(unregistered entry!)",
				pointer );

    std::free				( ( *it ).type_name );
    memory_contents.erase	( it );
}
void    memory_check_pointer ( )
{
    //static_assert(0,"NOT YET SUPPORTED");
}


//DEBUG_MEMORY_MANAGER
//

// name is for MEMDBG
pvoid	memory_allocate ( size_t size, pcstr name )
{
    pvoid pointer		= std::malloc(size);
    ASSERT_D( pointer, "Out of memory. Memory request: %d K", size );
	if ( name )
	{
		memory_register_pointer	( pointer, name );
	}

	return			    pointer;
}

void   memory_free ( pvoid  pointer )
{
    memory_unregister_pointer( pointer );
    std::free           	( pointer );
}

void	finalize ( )
{
    if ( memory_contents.size( ) > 1 )
	{
        Msg( "! Something hasn't been deleted!" );
            // this '+1' is log file so we skip it
            // it's released the last
        for ( 	memory_debug_iterator	it	= 	memory_contents.begin( ) + 1;
										it 	!= 	memory_contents.end( );
										++it )
		{
            Msg( "!Type: %s, addr: %p",( *it ).type_name,( *it ).address );
            std::free( ( *it ).type_name );
// can't have clear() in the end of method, because currently
// log's pointer is not released and will be at the very end
// of core::finalize.
		}

		memory_contents.clear( );
    }
	else
	{
        Msg(	"All memory has been successfully released!\n"
				"If engine crashes after this line, you forgot to comment Msg in memory_unregister_pointer!" );
    }


}

void	dump_memory_contents ( )
{
    Msg( "---------------global memory stats---------------" );
    for ( memory_debug_iterator it	= memory_contents.begin( );
								it	!= memory_contents.end( );
								++it )
	{
        Msg( "Type: %s, addr: %p", ( * it).type_name, ( * it).address );
    }

    Msg( "---------------global memory stats---------------" );
}
} // namespace memory
} // namespace inex
