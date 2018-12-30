#ifndef FS_CATALOG_OPERATIONS_WIN_IMPL_H_INCLUDED
#	define FS_CATALOG_OPERATIONS_WIN_IMPL_H_INCLUDED

namespace inex {
namespace fs {

namespace detail {

struct directory_iterator_impl
{
	WIN32_FIND_DATA	m_directory;
	pvoid			m_entry_pointer;
}; // struct directory_iterator_impl

inline
bool    is_system_directory ( pcstr const file_path_raw )
{
    return              * ( file_path_raw + strlen( file_path_raw ) - 1 ) == '.';
}

inline 
bool	exists ( pcstr const file_path_raw )
{
	return              ::GetFileAttributes( file_path_raw ) == -1;
}

inline
DWORD     read_file_attributes ( pcstr const file_path )
{
    return              ::GetFileAttributes( file_path );
}

inline
bool    is_directory_by_path ( pcstr const file_path )
{
    return              FILE_ATTRIBUTE_DIRECTORY & ::GetFileAttributes( file_path );
}

inline
bool    is_directory ( const directory_iterator_impl* impl_representation )
{
    return          impl_representation->m_directory.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

inline
pcstr     entry_name ( const directory_iterator_impl* impl_representation )
{
    return              impl_representation->m_directory.cFileName;
}

inline
pcstr    file_path_raw_c_str ( directory_iterator_impl* impl_representation )
{
    return              impl_representation->m_directory.cFileName;
}

inline
bool    open_directory ( directory_iterator_impl* impl_representation, const char* const file_path_raw )
{
	ASSERT_D( ( strchr( file_path_raw, '*' ) ), "Append '*' to '%s' before opening", file_path_raw );

    impl_representation->m_entry_pointer			=
		FindFirstFile(
			file_path_raw,
			&impl_representation->m_directory
		);

	ASSERT_D			(	impl_representation->m_entry_pointer,
							"Error opening ( open_directory proc ) %s: %s",
							file_path_raw, strerror( errno ) );

    return              1;
}

inline
void    close_directory ( directory_iterator_impl* impl_representation )
{
    if ( !impl_representation )
    {
		return              ;
    }

    FindClose				( impl_representation->m_entry_pointer );

 }

inline
bool    read_next_entry ( directory_iterator_impl* impl_representation )
{
    return               FindNextFile(	impl_representation->m_entry_pointer,
										&impl_representation->m_directory );
}

} // namsepace detail
} // namespace fs
} // namespace inex

#endif // #ifndef FS_CATALOG_OPERATIONS_WIN_IMPL_H_INCLUDED