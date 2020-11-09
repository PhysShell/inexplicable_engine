#include "pch.h"


#include "fs_file_system_internal.h"

namespace inex {
namespace fs {

# if INEX_PLATFORM_LINUX

memory_mapped_file::memory_mapped_file ( pcstr rhs )
{
    int descriptor              = open( rhs, O_RDONLY, 0 );
    ASSERT_S                    ( descriptor > 0 );
    struct stat                 file_status;
    ASSERT_S                    ( fstat( descriptor, &file_status ) >= 0 );

    size_t file_size            = ( size_t )file_status.st_size;
    pstr data                   = ( pstr )mmap(
            nullptr,
            file_size,
            PROT_READ,
            MAP_PRIVATE,
            descriptor,
            0
        );

    ASSERT_S                    ( data != MAP_FAILED );

    m_file_descriptor           = descriptor;
    m_size                      = file_size;
    m_data                      = data;
}

memory_mapped_file::memory_mapped_file ( memory_mapped_file&& rvalue ) :
    m_data              ( rvalue.m_data ),
    m_size              ( rvalue.m_size ),
    m_file_descriptor   ( rvalue.m_file_descriptor )
{
	rvalue.m_data               = nullptr;
	rvalue.m_size				= 0;
    rvalue.m_file_descriptor    = 0;
}

void    memory_mapped_file::close (  )
{
    munmap              ( m_data, m_size );
    ::close               ( m_file_descriptor );
    m_data              = nullptr;
    //free                ( mapping );
    //mapping             = nullptr;
}

# endif // #if INEX_PLATFORM_LINUX

# if INEX_PLATFORM_WINDOWS


memory_mapped_file::memory_mapped_file ( pcstr name ) :
    m_file_raw_pointer	( CreateFile( name, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) ),
    m_mapped_file     	( CreateFileMapping( m_file_raw_pointer, 0, PAGE_READONLY, 0, 0, 0 ) ),
    m_size        		( GetFileSize( m_file_raw_pointer, 0 ) )
{
	ASSERT_S	( m_file_raw_pointer != INVALID_HANDLE_VALUE );

	ASSERT_D	( m_mapped_file != INVALID_HANDLE_VALUE, "Error MMFile: '%s'", name );
	
	m_data		= static_cast< pstr >( MapViewOfFile( m_mapped_file, FILE_MAP_READ, 0, 0, 0 ) );
}

memory_mapped_file::memory_mapped_file ( memory_mapped_file&& file ) :
    m_file_raw_pointer	( file.m_file_raw_pointer ),
    m_size				( file.m_size ),
    m_mapped_file     	( file.m_mapped_file )
{

	file.m_file_raw_pointer	= file.m_mapped_file = nullptr;
	file.m_size				= 0;
}

void	memory_mapped_file::close ( )
{
	// ie_delete		(path);
	CloseHandle					( m_mapped_file );
	m_mapped_file			=	nullptr;
	CloseHandle					( m_file_raw_pointer );
	m_file_raw_pointer		=	nullptr;
	//Msg("Deleting (close()) address: %p", this);
}

#endif // #if INEX_PLATFORM_WINDOWS

} // namespace fs
} // namespace inex
