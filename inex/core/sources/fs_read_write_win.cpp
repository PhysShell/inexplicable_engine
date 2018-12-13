#include "stdafx.h"

#if IE_PLATFORM_WINDOWS
#	include "fs_read_write.h"
#	include <errno.h>

namespace inex {
namespace core {
namespace fs {

reader::reader ( ) :
	m_data	( nullptr ),
	m_pos	( 0 ),
	m_size	( 0 )
{
}

reader::reader (pvoid _data, size_t _size) :
	m_data	{ static_cast< pstr >( _data ) },
	m_pos	{ },
	m_size	{ _size }
{
}

u32 reader::advance_term_string ( )
{
	// char 10 is new line, char 13 is carriage return
	u32	sz			= { };
	pstr src		= static_cast< pstr >( m_data + m_pos );
	while ( !eof( ) && *src != '\n' )
	{
		++m_pos;
		++sz;
		++src;
	}
	// 'cuz m_pos points to '\n' and it causes
	// breaking in the first while-loop
	if ( m_pos < m_size )
	{
		++m_pos;
	}

	return			sz;
}

void reader::r_string ( pstr dest, size_t tgt_size )
{
	pstr src			= 	static_cast< pstr >( m_data + m_pos );
	u32		sz			= 	advance_term_string( );
	ASSERT_D( sz < ( tgt_size - 1 ), "Dest string's less than needed." );

	strncpy					( dest, src, sz );
	dest[ sz ]			= 	0;
}

void reader::r_stringZ ( pstr dest, size_t tgt_size )
{
    ( void )dest;
	( void )tgt_size;
}

virtual_file_reader::virtual_file_reader ( pcstr name ) :
    m_file_raw_pointer		( CreateFile( name, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) )
    //m_size        ( GetFileSize(m_file_raw_pointer, NULL) ),
    //m_mapped_file     ( CreateFileMapping(m_file_raw_pointer,0,PAGE_READONLY,0, m_size, 0) )
{

	//m_file_raw_pointer	=CreateFile(cFileName,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	ASSERT_D		( INVALID_HANDLE_VALUE != m_file_raw_pointer, "File doesn't exist. Check '%s'", name );
	m_size		=	GetFileSize( m_file_raw_pointer, NULL );
	m_mapped_file	=
		CreateFileMapping(
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



	//log::Msg( "*! virtual_file_reader destructor called, addr: %p, sz: %d", this, sizeof( *this ) );

}

void file_writer::w ( pcstr src )
{
	fputs				( src, m_file );
	ASSERT_S( !fflush( m_file ) );
}

void file_writer::close	( )
{
	fclose				( m_file );
	m_file			= 	nullptr;
}



file_writer::file_writer( pcstr file_name ) :
    m_file	( fopen( file_name, "w" ) )
{
	if ( 0 == m_file )
	{
		printf("error %s (opening file %s)\n",
#ifdef IE_PURE_GNUC
			strerror( errno )
#else // #ifdef IE_PURE_GNUC
			_sys_errlist[ errno ]
#endif // #ifdef IE_PURE_GNUC
	, file_name );
	}
}

//void read_file(const file* f)
//{
//	ASSERT_S(f!=0);
//	u8* m_data =(u8*)MapViewOfFile(f->m_mapped_file, FILE_MAP_READ, 0,0,0);
//	reader* rdr = ie_new<reader>(m_data, (size_t)100500);
//	//virtual_file_reader vf {n};
//	rdr->r_stringZ(0,0);
//	ie_delete   (rdr);
//}

} // namespace fs
} // names core
} // namespace inex
#endif // #if IE_PLATFORM_WINDOWS
