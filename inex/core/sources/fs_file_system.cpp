#include "stdafx.h"
#include "fs_file_system.h"
#include "fs_file_system_internal.h"
#include <inex/stl_extensions.h>
#include "fs_ini_file.h"
//#include <inex/macro_compiler.h>

#ifdef IE_FILESYSTEM_SUPPORTED
#   include <experimental/filesystem>
#endif  // #ifdef IE_FILESYSTEM_SUPPORTED

#include <set>
#include "ie_memory.h"
#include "fs_directory_iterators.h"
//#include "fs_manager.h"


//#include "_utils.h"

namespace inex {
namespace core {
namespace fsmgr {

using inex::core::log::Msg;

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
        // we can use destructor of memory_mapped_file
        // to avoid this
        //Msg("Deleting address: %file_path, size %d", &(*I), (*I).size);
        const_cast< memory_mapped_file& >( *it ).close( );
    }
}

void    wchar_to_char ( pstr dest, wchar_t const* src, size_t sz )
{
	size_t i			= 0;
    //wchar_t wc;
	for ( wchar_t wide/*, i = 0*/; i < sz ; ++i )
    {
		wide			= src[ i ];
		dest[ i ]		= char( wide );
	}

	dest[ sz ]			= 0;

    //IE_DEBUG_WAIT;

}

// place slash in ie_core.cpp in _initialize in FS
//#define FS_WHEEL
#ifdef FS_WHEEL
pstr	util ( pcstr file_path )
{
    pstr n			= memory::ie_allocate< char >( strlen( file_path ) + 1 );

    for ( u32 i = { 0 }; i < strlen( file_path ); ++i )
	{
        if ( isalpha( file_path[ i ] ) )
		{
            n[ i ]	= file_path[ i ];
		}
	}

    return 			n;
}
#endif // #ifdef FS_WHEEL

void	initialize	( pcstr dir )
{
// when testing our fs-wheel

#ifndef IE_FILESYSTEM_SUPPORTED
    Msg( "Initializing Custom File System..." );

    char data_directoty	[ IE_MAX_PATH ] { 0 };

    strcpy              ( data_directoty, dir );
//#if IE_PLATFORM_WINDOWS
//    strcpy              ( data_directoty + strlen( data_directoty ) , "\\*" );
//#else // #if IE_PLATFORM_WINDOWS
//    strcpy              ( data_directoty + strlen( data_directoty ) , "/" );
//#endif // #if IE_PLATFORM_WINDOWS

//  Msg                 ( "Dir is: %s", data_directoty );
//	recursive_directory_iterator rdi( data_directoty );

    for ( recursive_directory_iterator  it			( data_directoty ),
										end_it	= 	recursive_directory_iterator( ); // don't do just E( )...
										it 		!= 	end_it;
										++it )
    {
        if ( ( * it ).path( ).is_directory( ) )
        {
            continue;
        }

        Msg( "Loading memory_mapped_file: %s", ( * it ).path( ).c_str( ) );
        files.insert    ( memory_mapped_file( ( * it ).path( ).c_str( ) ) );
    }


    Msg( "FS: %d files cached", files.size( ) );
#else   // #ifdef IE_FILESYSTEM_SUPPORTED
    // dir was once gamedata/, but if this slash doesn't matter
    // i just leave it at that
    namespace   std_fs				        = 	std::experimental::filesystem;
	typedef     std_fs::path::value_type    	path_type;

    Msg( "Initializing STD File System..." );

#ifdef FS_WHEEL
// dir doesn't have to have slash at the end
#   ifdef __GNUC__
        pstr n			= 	util( dir );
        ASSERT_D( std_fs::exists( std_fs::path{ n } ), "Data directory '%s' isn't found", n );
        memory::ie_delete		( n ); // never called...
#   else // #ifdef __GNUC__
        ASSERT_D( std_fs::exists( std_fs::path{ dir } ), "Data directory %s isn't found", dir );
#   endif // #ifdef __GNUC__
#else // #ifdef FS_WHEEL
    ASSERT_D( std_fs::exists( std_fs::path{ dir } ), "Data directory '%s' isn't found", dir );
#endif // #ifdef FS_WHEEL
	for ( auto const& it : std_fs::recursive_directory_iterator( dir ) )
	{
		if ( std_fs::is_regular_file( it ) )
		{
			std_fs::path file_path 					= 	{ it };
			const path_type* platform_type_file_path= 	file_path.c_str( );

#ifdef IE_PLATFORM_WINDOWS
			size_t file_path_length					= 	wcslen( platform_type_file_path );
			pstr file_path_string					= 	memory::ie_allocate< char >( file_path_length + 1 );

			// If I have to delete my wheel in the future...
			//wcstombs(file_path_string,platform_type_file_path,file_path_length);
			//file_path_string[file_path_length-1]=0;
									// there were IE_MAX_PATH
			wchar_to_char			( file_path_string, platform_type_file_path, file_path_length );
#   define platform_type_file_path file_path_string
#endif // #ifdef IE_PLATFORM_WINDOWS

			//memory_mapped_file* f			=create_file(platform_type_file_path);
			files.insert			( memory_mapped_file{ platform_type_file_path } );


// 1.create temp memory_mapped_file in constructor
// 2.use move semantics to initialize new 'memory_mapped_file' object in fileset
// 3.call destructor of temp memory_mapped_file, which has nothing to delete (all pointers are 0)
			/*
			MAYBE, WE CAN JUST USE ERASE() TO DELETE ELEMS INSTEAD OF CALLING FILE::CLOSE()???
				test it
			memory_mapped_file f;
			files.insert(f);
			memory_mapped_file_iterator I=files.cbegin();
			Msg	("F address: %file_path, f in files: %file_path", &f, &(*I));
			*/
			Msg( "Loading file: %s", platform_type_file_path );

			memory::ie_delete  		( platform_type_file_path );
#ifdef IE_PLATFORM_WINDOWS
#   undef platform_type_file_path
#endif // #ifdef IE_PLATFORM_WINDOWS
		}
	}

	Msg( "FS: %d files cached", files.size( ) );
#endif  // #ifdef IE_FILESYSTEM_SUPPORTED
    /*here're two ways of how to read memory_mapped_file
	 load memory_mapped_file into the virtual memory and then read
	 line-by-line*/



	 //ini_file   ifile	{    };
	 //ifile.load			( "System.ltx" );
	 //std::cout << ifile.r_float( "m_smt", "flt" );

 //   string128 buf{};
	//reader*rdr	= r_open("gamedata/engine.log");

	//while(!rdr->eof()) {
	//	rdr->r_string(buf,sizeof(buf));
 //       std::cout<<buf<<'\n';
	//}

	//r_close		( rdr );
//
//
//
//	r_close		(rdr);
 //   memory::dump_memory_contents();
	//reader* rdr = r_open("gamedata/engine.log");
	//rdr->r_stringZ(0,0);
    //r_close(rdr);

    //or read from memory_mapped_file already loaded into the memory
//	memory_mapped_file_iterator I=files.begin();
//	reader rdr	= {(char*)MapViewOfFile((*I).m_mapped_file, FILE_MAP_READ, 0,0,0), (*I).size};
//    while(!rdr.eof()) {
//        rdr.r_string(buf,sizeof(buf));
//        std::cout<<buf<<'\n';
//    }

}

#pragma todo( "i really should change reader to virtual reader since it creates only those" )

fs::reader*		r_open ( pcstr path )
{
	//reader *r	=nullptr;
	Msg( "* FS: Download %s", path );
	return			( memory::ie_new< fs::virtual_file_reader >( path ) );
}

void	r_close	( fs::reader*& rdr )
{

	//ASSERT_S( dynamic_cast< fs::virtual_file_reader* >( rdr ) );
	memory::ie_delete( rdr );
}

} // namespace fsmgr
} // names core
} // namespace inex
