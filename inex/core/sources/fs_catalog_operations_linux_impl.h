#ifndef FS_CATALOG_OPERATIONS_LINUX_IMPL_H_INCLUDED
#   define FS_CATALOG_OPERATIONS_LINUX_IMPL_H_INCLUDED

#   include <dirent.h>

#   include <sys/types.h>
#   include <sys/stat.h>
#   include <unistd.h>


namespace inex {
namespace fs {
namespace detail {

struct directory_iterator_impl
{
    DIR*    m_directory;
    //dirent  m_directory_entry;
    dirent* m_entry_pointer;
    size_t  m_value_returned;
}; // struct directory_iterator_impl

typedef struct stat      file_status;

inline
bool    is_system_directory ( pcstr const file_path_raw )
{
    return              * ( file_path_raw + strlen( file_path_raw ) - 1 ) == '.';
}

inline
bool	exists ( pcstr const file_path_raw )
{
    file_status         temp;
	return              stat( file_path_raw, &temp ) == -1;
}

inline
file_status     read_file_attributes ( pcstr const file_path )
{
    file_status file_attributes;
    ASSERT_D( stat ( file_path, &file_attributes ) == 0, "Error statting %s: %s\n", file_path, strerror( errno ) );
    return              file_attributes;
}

inline
bool    is_directory_by_path ( pcstr const file_path )
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
pstr    entry_name ( const directory_iterator_impl* impl_representation )
{
        return              impl_representation->m_entry_pointer->d_name;
}

inline
pstr    file_path_raw_c_str ( directory_iterator_impl* impl_representation )
{
    return              impl_representation->m_entry_pointer->d_name;
}

inline
void    open_directory ( directory_iterator_impl* impl_representation, pcstr const file_path_raw )
{
    impl_representation->m_directory               = opendir( file_path_raw );
    ASSERT_D(   impl_representation->m_directory != nullptr,
                "Error opening ( open_directory proc ) %s: %s\n", 
                file_path_raw, 
                strerror( errno ) );}

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
    return              impl_representation->m_entry_pointer;
}

} // namsepace detail
} // namespace fs
} // namespace inex

#endif // #ifndef FS_CATALOG_OPERATIONS_LINUX_IMPL_H_INCLUDED
