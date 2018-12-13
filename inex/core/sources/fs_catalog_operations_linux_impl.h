#ifndef FS_CATALOG_OPERATIONS_LINUX_IMPL_H_INCLUDED
#   define FS_CATALOG_OPERATIONS_LINUX_IMPL_H_INCLUDED

#   include <dirent.h>

#   include <sys/types.h>
#   include <sys/stat.h>
#   include <unistd.h>


namespace inex {
namespace core {
namespace fsmgr {

namespace detail {
    struct directory_iterator_impl;
} // namespace detail

#   if IE_PLATFORM_LINUX

namespace detail {

struct directory_iterator_impl
{
    DIR*    m_directory;
    //dirent  m_directory_entry;
    dirent* m_entry_pointer;
    size_t  m_value_returned;
}; // struct directory_iterator_impl

inline
bool    is_system_directory ( const char* const file_path_raw )
{
    return              * ( file_path_raw + strlen( file_path_raw ) - 1 ) == '.';
}


typedef struct stat      file_status;
inline
file_status     read_file_attributes ( const char* const file_path )
{
    file_status file_attributes;
    if ( stat ( file_path, &file_attributes ) )
    {
        printf          ( "Error statting %s: %s\n", file_path, strerror( errno ) );
    }

    return              file_attributes;
}

inline
bool    is_directory_by_path ( const char* const file_path )
{
    return              S_ISDIR( read_file_attributes( file_path ).st_mode );
}

inline
bool    is_directory ( const directory_iterator_impl* impl_representation )
{
    // d_type may not be supported in some UNIX OS'
    return          impl_representation->m_entry_pointer->d_type & DT_DIR;
}

inline
const char*     entry_name ( const directory_iterator_impl* impl_representation )
{
    // std::cout           << "Entry name:\t" << impl_representation->m_directory_entry.d_name << '\n';
    return              impl_representation->m_entry_pointer->d_name;
}

inline
const char* const    file_path_raw_c_str ( directory_iterator_impl* impl_representation )
{
    return              impl_representation->m_entry_pointer->d_name;
}

inline
bool    open_directory ( directory_iterator_impl* impl_representation, const char* const file_path_raw )
{
    impl_representation->m_directory               = opendir( file_path_raw );
    if ( impl_representation->m_directory == nullptr )
    {
        printf              ( "Error opening ( open_directory proc ) %s: %s\n", file_path_raw, strerror( errno ) );
        exit                ( EXIT_FAILURE );
        return              0;
    }


    //printf                  ( "Directory ( %p ) '%s' opened\n", impl_representation, file_path_raw );
    return                  1;
}

inline
void    close_directory ( directory_iterator_impl* impl_representation )
{
    if ( !impl_representation )
    {
        printf              ( "Directory ALREADY closed\n" );
        return              ;
    }

    //printf              ( "Directory '%p' closed\n", impl_representation );
    closedir            ( impl_representation->m_directory );

 }

inline
bool    read_next_entry ( directory_iterator_impl* impl_representation )
{
    // readdir returned m_value_returned.

    impl_representation->m_entry_pointer    =
        ( impl_representation->m_entry_pointer = readdir( impl_representation->m_directory) );

    // printf              ( "New entry found '%p' \"%s\"\n", impl_representation, impl_representation->m_directory_entry.d_name );

    return              impl_representation->m_entry_pointer;
}

} // namsepace detail
} // namespace fsmgr
} // namespace core
} // namespace inex

#   endif // if IE_PLATFORM_LINUX

#endif // #ifndef FS_CATALOG_OPERATIONS_LINUX_IMPL_H_INCLUDED
