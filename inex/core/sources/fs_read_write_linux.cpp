#include "stdafx.h"

#if IE_PLATFORM_LINUX
#	include "fs_read_write.h"

#   include <sys/mman.h>
#   include <fcntl.h>
#   include <sys/stat.h>
#   include <unistd.h>

namespace inex {
namespace core {
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

	if ( !( sz < ( tgt_size - 1 ) ) )
	{
		std::cout 		<< "Dest string's less than needed\n";
		exit			( 666 );
	}

    //std::cout
    //char ch; std::cin >> ch;

	//ASSERT_D( sz < ( tgt_size - 1 ), "Dest string's less than needed." );

	strncpy				( dest, src, sz );
	dest    [ sz ]		= 0;

    //std:: cout          << dest << "\n";
}

void reader::r_stringZ ( pstr dest, size_t tgt_size )
{
    ( void )dest;
	( void )tgt_size;
}

virtual_file_reader::virtual_file_reader ( pcstr rhs )
{

    m_file_descriptor           = open( rhs, O_RDONLY, 0 );
    if ( m_file_descriptor < 0 )
    {
        std::cerr   << "fileMappingCreate - open failed, fname =  "
                    << rhs
                    << ", "
                    << strerror( errno )
                    << std::endl;

        return;
    }

    struct stat st;
    if ( fstat( m_file_descriptor, &st ) < 0 )
    {
        std::cerr   << "fileMappingCreate - fstat failed, fname = "
                    << rhs
                    << ", "
                    << strerror( errno )
                    << std::endl;

        ::close       ( m_file_descriptor );
        return;
    }

    m_size          = st.st_size;

    m_data         =
        ( pstr )mmap(
            nullptr,
            m_size,
            PROT_READ,
            MAP_PRIVATE,
            m_file_descriptor,
            0
        );


    if ( m_data == MAP_FAILED )
    {
        std::cerr << "fileMappingCreate - mmap failed, fname = " << rhs << ", " << strerror( errno ) << std::endl;
        ::close                   ( m_file_descriptor );
        return;
    }

    ::close               ( m_file_descriptor );

    // std::cout                   << length( );

    // for ( pstr p = ( pstr )pointer( ); *p; ++p )
    // {
    //     std::cout               << *p;
    // }

    // std::cout                   << '\n';

}

virtual_file_reader::~virtual_file_reader ( )
{
	/*
	#ifdef FS_DEBUG
        unregister_file_mapping	(m_data,m_size);
    #endif // DEBUG*/

    munmap              ( m_data, m_size );

    //mapping             = nullptr;


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
#ifdef __GNUC__
			strerror( errno )
#else // #ifdef __GNUC__
			_sys_errlist[ errno ]
#endif // #ifdef __GNUC__
	, file_name );
	}
}


} // namespace fs
} // names core
} // namespace inex
#endif // #if IE_PLATFORM_LINUX
