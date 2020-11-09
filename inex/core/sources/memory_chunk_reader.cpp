#include "pch.h"
#include "memory_chunk_reader.h"

namespace inex {
namespace memory {

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
	INEX_UNREFERENCED_PARAMETERS( dest, tgt_size );
}

void file_writer::w ( pcstr src )
{
	fputs				( src, m_file );
	s32 success			= fflush ( m_file ); // returns 0 if successful
	VERIFY				( 0 == success);
}

void file_writer::close	( )
{
	fclose				( m_file );
	m_file			= 	nullptr;
}

u32 reader::advance_term_string ( )
{
	u32	sz			= { };
	pstr src		= static_cast< pstr >( m_data + m_pos );
	while ( !eof( ) && * src != '\n' ) {
		++m_pos;
		++sz;
		++src;
	}
	// 'cuz m_pos points to '\n' and it causes breaking in the first while-loop
	if ( m_pos < m_size ) {
		++m_pos;
	}

	return			sz;
}

file_writer::file_writer( pcstr file_name ) :
    m_file	( fopen( file_name, "w" ) )
{
#ifdef __GNUC__
#	define	errno_platform 			strerror( errno )
#else // #ifdef __GNUC__
#	define	errno_platform 			_sys_errlist[ errno ]
#endif // #ifdef __GNUC__

	ASSERT_D( m_file, "Couldn't open '%s'. %s.", file_name, errno_platform );

#undef		errno_platform
}

} // namespace memory
} // namespace inex