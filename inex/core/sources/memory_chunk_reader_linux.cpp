#include "pch.h"

#include "memory_chunk_reader.h"

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

namespace inex {
namespace memory {

virtual_file_reader::virtual_file_reader ( pcstr rhs )
{
    m_file_descriptor= open( rhs, O_RDONLY, 0 );
    ASSERT_D		( m_file_descriptor, "Couldn't open file '%s'. %s.", rhs, strerror( errno ) );

	struct stat st;
    ASSERT_D		( !fstat( m_file_descriptor, &st ) > 0, "Couldn't read attributes of '%s'. %s", rhs, strerror( errno ) );

    m_size          = st.st_size;
    m_data          = ( pstr )mmap( nullptr, m_size, PROT_READ, MAP_PRIVATE, m_file_descriptor, 0 );
    ASSERT_D		( m_data != MAP_FAILED, "Couldn't map '%s'. %s.", rhs, strerror( errno ) );
}

virtual_file_reader::~virtual_file_reader ( )
{
	/*
	#ifdef FS_DEBUG
        unregister_file_mapping	(m_data,m_size);
    #endif // DEBUG*/

    munmap              ( m_data, m_size );

    //mapping             = nullptr;

}

} // namespace memory
} // namespace inex
