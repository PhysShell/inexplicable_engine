#include "stdafx.h"


#include "fs_file_system_internal.h"

namespace inex {
namespace core {
namespace fsmgr {

# if IE_PLATFORM_LINUX



memory_mapped_file::memory_mapped_file ( pcstr rhs )
{
    int fd          = open( rhs, O_RDONLY, 0 );
    if ( fd < 0 )
    {
        std::cerr   << "fileMappingCreate - open failed, fname =  "
                    << rhs
                    << ", "
                    << strerror( errno )
                    << std::endl;

        exit        ( 1 );
    }

    struct stat st;
    if ( fstat( fd, &st ) < 0 )
    {
        std::cerr   << "fileMappingCreate - fstat failed, fname = "
                    << rhs
                    << ", "
                    << strerror( errno )
                    << std::endl;

        ::close       ( fd );
        exit        ( 1 );
    }

    size_t fsize        = ( size_t )st.st_size;
    char* data         =
        ( char* )mmap(
            nullptr,
            fsize,
            PROT_READ,
            MAP_PRIVATE,
            fd,
            0
        );

    if ( data == MAP_FAILED )
    {
        std::cerr << "fileMappingCreate - mmap failed, fname = " << rhs << ", " << strerror(errno) << std::endl;
        ::close                   ( fd );
        exit        ( 1 );
    }

    m_file_descriptor           = fd;
    m_size                      = fsize;
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

# endif // #if IE_PLATFORM_LINUX

# if IE_PLATFORM_WINDOWS


memory_mapped_file::memory_mapped_file ( pcstr name ) :
    m_file_raw_pointer	( CreateFile( name, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) ),
    m_mapped_file     	( CreateFileMapping( m_file_raw_pointer, 0, PAGE_READONLY, 0, 0, 0 ) ),
    m_size        		( GetFileSize( m_file_raw_pointer, 0 ) )
{
	//m_file_raw_pointer	=CreateFile(name,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	ASSERT_S( m_file_raw_pointer != INVALID_HANDLE_VALUE );
	//size	    =GetFileSize(m_file_raw_pointer,0);
	// 4 & 5 parameters are 0 cuz I don't want to change memory_mapped_file's size, just read it
	m_mapped_file	    = CreateFileMapping( m_file_raw_pointer, 0, PAGE_READONLY, 0, 0, 0 );
	//ASSERT_S	(INVALID_HANDLE_VALUE!=m_mapped_file);
	//Msg("Creating (constructor) address: %p", this);
}

memory_mapped_file::memory_mapped_file ( memory_mapped_file&& file ) :
    m_file_raw_pointer	( file.m_file_raw_pointer ),
    m_size				( file.m_size ),
    m_mapped_file     	( file.m_mapped_file )
{
	//Msg("Creating (move) address: %p, from %p", this, &file);
	//m_file_raw_pointer	=file.m_file_raw_pointer;
	//m_mapped_file		=file.m_mapped_file;
	//size		=file.size;
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

#endif // #if IE_PLATFORM_WINDOWS

} // namespace fsmgr
} // names core
} // namespace inex
