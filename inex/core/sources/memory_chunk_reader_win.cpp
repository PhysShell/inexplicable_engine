#include "pch.h"

#include "memory_chunk_reader.h"
#include <errno.h>

namespace inex {
namespace memory {

virtual_file_reader::virtual_file_reader ( pcstr name ) :
    m_file_raw_pointer		( CreateFile( name, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) )
    //m_size        ( GetFileSize(m_file_raw_pointer, NULL) ),
    //m_mapped_file     ( CreateFileMapping(m_file_raw_pointer,0,PAGE_READONLY,0, m_size, 0) )
{

	ASSERT_D		( INVALID_HANDLE_VALUE != m_file_raw_pointer, "File doesn't exist. Check '%s'", name );
	m_size			=	GetFileSize( m_file_raw_pointer, NULL );
	m_mapped_file	=
		CreateFileMapping (
			m_file_raw_pointer,
			0,
			PAGE_READONLY,
			0,
			m_size,
			0
		);

	ASSERT_S		( INVALID_HANDLE_VALUE != m_mapped_file );
	m_data		=	static_cast< pstr >( MapViewOfFile( m_mapped_file, FILE_MAP_READ, 0, 0, 0 ) );

	/*
	#ifdef FS_DEBUG
	register_file_mapping	(m_data,m_size,cFileName);
#endif // DEBUG
	*/
}

virtual_file_reader::~virtual_file_reader ( )
{
	/*
	#ifdef FS_DEBUG
        unregister_file_mapping	(m_data,m_size);
    #endif // DEBUG*/

	UnmapViewOfFile	( static_cast< pvoid >( m_data ) );
	CloseHandle		( m_mapped_file );
	CloseHandle		( m_file_raw_pointer );

}

} // namespace memory
} // namespace inex
