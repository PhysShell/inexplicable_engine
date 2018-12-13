#include "stdafx.h"

#include <inex/engine/ie_engine.h>
#include <inex/stl_extensions_vector.h>

#include <iostream>
// for dx11
//#include <d3d11.h>

// i don't produce debugging symbols in both projects
// to reduce their size


int main( int argc, pstr* argv )
{
    using namespace inex::core::log;

    //_initialize();

    //Msg("some text");

    //char ch1;std::cin>>ch1;
    //_destroy();
	//lol::file_writer* log11=new lol::file_writer("log.log");

	//log11->w		("some str\n");
	//log11->w		("new str 123");

	//delete log11;

	//inex::engine::engine en{argc, argv};
	//ASSERT_S(1==1);


   //inex::core::CFileSystem ie_FS	={};
   //auto it = ie_FS.files.begin();

   	//inex::core::reader* r = ie_FS.r_open("engine.log");
	//r->r_stringZ(0,0);
	//ie_FS.r_close(r);

    //u8* data =(u8*)MapViewOfFile((*it).m_mapped_file, FILE_MAP_READ, 0,0,0);
   	//inex::core::reader r(data,0);
	//r.r_stringZ(0,0);

	inex::engine::engine en{ argc, argv };
   // auto it = ie_FS.files.begin();
    //inex::core::read_file(&(*it));

	Msg( "sz ptr: %u", sizeof ( pvoid ) );
	//read_file(0);

    char ch;
	std::cin >> ch;

   	return 0;
} //
