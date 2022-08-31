#include "pch.h"
#include "fs_file_system.h"
#include "fs_file_system_internal.h"
#include <inex/stl_extensions.h>
#include "fs_ini_file.h"

#ifdef INEX_STD_FILESYSTEM_SUPPORTED
#	ifdef INEX_PLATFORM_WINDOWS
#		if _MSVC_LANG < 201703L
#			include <experimental/filesystem>
#		else
#			include <filesystem>
#		endif // #if _MSVC_LANG < 201703L
#	elif INEX_PLATFORM_LINUX
#		if __cplusplus < 201703L
#			include <experimental/filesystem>
#		else
#			include <filesystem>
#		endif // #if _MSVC_LANG < 201703L
#	endif // #ifdef INEX_PLATFORM_WINDOWS
#endif  // #ifdef INEX_STD_FILESYSTEM_SUPPORTED

#include <set>
#include <ctime>
#include "ie_memory.h"
#include "fs_directory_iterators.h"
#include <inex/fs_utils.h>
//#include "fs_manager.h"

namespace inex {
namespace fs {

using inex::logging::Msg;

namespace {
 DEFINE_SET_PRED	( 	memory_mapped_file,
						memory_mapped_file_set,
						memory_mapped_file_predicate,
						memory_mapped_file_iterator
					);
 memory_mapped_file_set	 files;
} // namespace

void    finalize ( )
{
    for ( memory_mapped_file_iterator 	it		= 	files.begin( ),
										end_it	= 	files.end( );
										it		!=	end_it;
										++it )
	{
        const_cast< memory_mapped_file& >( * it ).close( );
    }
}

void    wchar_to_char ( pstr dest, wchar_t const * src, size_t sz )
{
	size_t i			= 0;

	for ( wchar_t wide; i < sz ; ++i ) {
		wide			= src[ i ];
		dest[ i ]		= char( wide );
	}

	dest[ sz ]			= 0;
}

void	initialize	( pcstr dir )
{
// when testing our fs-wheel
#undef INEX_STD_FILESYSTEM_SUPPORTED

#ifndef INEX_STD_FILESYSTEM_SUPPORTED
    Msg( "- [fs]\t: initializing custom fs..." );
	ASSERT_D( !fs::exists( dir ), "Directory '%s' was not found. Check if it exists.", dir );

	clock_t start_initializing			=			clock( );

    for ( recursive_directory_iterator  it			( dir ),
										end_it	= 	recursive_directory_iterator( );
										it 		!= 	end_it;
										++it )
    {
        if ( is_directory( ( * it ).path( ).c_str( ) ) || is_system_catalog( ( *it ).path( ).c_str( ) ) )
            continue;

        //files.insert    ( memory_mapped_file( ( * it ).path( ).c_str( ) ) );
		files.emplace					( ( * it ).path( ).c_str( ) );
        Msg								( "- [fs][info]\t: loading \"%s\"", ( * it ).path( ).c_str( ) );
        
    }

	clock_t end_initializing			=	clock( ) - start_initializing ;
#else   // #ifdef INEX_STD_FILESYSTEM_SUPPORTED
    namespace   std_fs				        = 	std::experimental::filesystem;
	typedef     std_fs::path::value_type    	path_type;

    Msg( "- [fs]\t: initializing std fs..." );

    ASSERT_D( std_fs::exists( std_fs::path{ dir } ), "Data directory '%s' isn't found", dir );
	clock_t start_initializing			=			clock( );
	for ( auto const & it : std_fs::recursive_directory_iterator( dir ) )
	{
		if ( std_fs::is_regular_file( it ) )
		{
			std_fs::path file_path 					= 	{ it };
			const path_type* platform_type_file_path= 	file_path.c_str( );

#if INEX_PLATFORM_WINDOWS
			size_t file_path_length					= 	wcslen( platform_type_file_path );
			pstr file_path_string					= 	memory::ie_allocate< char >( file_path_length + 1 );

			wchar_to_char			( file_path_string, platform_type_file_path, file_path_length );
#   define platform_type_file_path file_path_string
#endif // #ifdef INEX_PLATFORM_WINDOWS
			files.insert			( memory_mapped_file{ platform_type_file_path } );
			Msg( "Loading file: %s", platform_type_file_path );
#if INEX_PLATFORM_WINDOWS
			memory::ie_delete  		( platform_type_file_path );
#   undef platform_type_file_path
#endif // #ifdef INEX_PLATFORM_WINDOWS
		}
	}
	clock_t end_initializing			=	clock( ) - start_initializing ;
#endif  // #ifdef INEX_STD_FILESYSTEM_SUPPORTED

    Msg				( "fs: %d files cached. initializing time:\t%f sec\n", files.size( ), ( double )end_initializing / CLOCKS_PER_SEC );
}
memory::reader *	r_open ( pcstr path )
{
	//reader *r	=nullptr;
	Msg				( "- [fs][info]\t: loading \"%s\"", path );
	return			( memory::ie_new< memory::virtual_file_reader >( path ) );
}

void	r_close	( memory::reader *& rdr )
{
	memory::ie_delete( rdr );
}

} // namespace fs
} // namespace inex
