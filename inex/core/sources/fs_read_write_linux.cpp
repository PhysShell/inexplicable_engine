#include "stdafx.h"

#include "fs_read_write.h"

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

namespace inex {
namespace fs {

reader::reader ( ) :
	m_data	( nullptr ),
	m_pos	( 0 ),
	m_size	( 0 )
{
}

reader::reader (pvoid data, size_t size) :
	m_data	{ static_cast< pstr >( data ) },
	m_pos	( 0 ),
	m_size	{ size }
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
	pstr    src			= 	static_cast< pstr >( m_data + m_pos );
	u32		sz			= 	advance_term_string( );

	ASSERT_D( sz < ( tgt_size - 1 ), "Dest string's less than needed." );

	strncpy				( dest, src, sz );
	dest    [ sz ]		= 0;
}

void reader::r_stringZ ( pstr dest, size_t tgt_size )
{
    ( void )dest;
	( void )tgt_size;
}

virtual_file_reader::virtual_file_reader ( pcstr rhs )
{
    m_file_descriptor           = open( rhs, O_RDONLY, 0 );
    ASSERT_D( m_file_descriptor, "Couldn't open file '%s'. %s.", rhs, strerror( errno ) );
    struct stat st;
    ASSERT_D( fstat( m_file_descriptor, &st ) > 0, "Couldn't read attributes of '%s'. %s", rhs, strerror( errno ) );

    m_size          = st.st_size;
    m_data          = ( pstr )mmap(
            nullptr,
            m_size,
            PROT_READ,
            MAP_PRIVATE,
            m_file_descriptor,
            0
        );

    ASSERT_D( m_data != MAP_FAILED, "Couldn't map '%s'. %s.", rhs, strerror( errno ) );
}

virtual_file_reader::~virtual_file_reader ( )
{
	/*
	#ifdef FS_DEBUG
        unregister_file_mapping	(m_data,m_size);
    #endif // DEBUG*/

    munmap              ( m_data, m_size );

    //mapping             = nullptr;


	//logging::Msg( "*! virtual_file_reader destructor called, addr: %p, sz: %d", this, sizeof( *this ) );

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
    ASSERT_D( 0 != m_file, "Couldn't open '%s'. %s.", file_name, strerror( errno ) );
}

} // namespace fs
} // namespace inex