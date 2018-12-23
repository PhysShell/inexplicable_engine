#ifndef FS_CATALOG_OPERATIONS_WIN_IMPL_H_INCLUDED
#	define FS_CATALOG_OPERATIONS_WIN_IMPL_H_INCLUDED

#   if IE_PLATFORM_WINDOWS

namespace inex {
namespace core {
namespace fsmgr {

namespace detail {
    struct directory_iterator_impl;
} // namespace detail



namespace detail {

struct directory_iterator_impl
{
	WIN32_FIND_DATA	m_directory;
	pvoid			m_entry_pointer;
}; // struct directory_iterator_impl

inline
bool    is_system_directory ( const char* const file_path_raw )
{
    return              * ( file_path_raw + strlen( file_path_raw ) - 1 ) == '.';
}

inline 
bool	exists ( pcstr const file_path_raw )
{
	return              ::GetFileAttributes( file_path_raw ) == -1;
}

inline
DWORD     read_file_attributes ( const char* const file_path )
{
    return              ::GetFileAttributes( file_path );
}

inline
bool    is_directory_by_path ( const char* const file_path )
{
    return              FILE_ATTRIBUTE_DIRECTORY & ::GetFileAttributes( file_path );
}

inline
bool    is_directory ( const directory_iterator_impl* impl_representation )
{
    // d_type may not be supported in some UNIX OS'
    return          impl_representation->m_directory.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

inline
const char*     entry_name ( const directory_iterator_impl* impl_representation )
{
    // std::cout           << "Entry name:\t" << impl_representation->m_directory_entry.d_name << '\n';
    return              impl_representation->m_directory.cFileName;
}

inline
const char* const    file_path_raw_c_str ( directory_iterator_impl* impl_representation )
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

		ASSERT_D			( impl_representation->m_entry_pointer,
								"Error opening ( open_directory proc ) %s: %s",
								file_path_raw, strerror( errno ) );


    //inex::core::log::Msg    ( "Directory ( %p ) '%s' opened", impl_representation, file_path_raw );
    return                  1;
}

inline
void    close_directory ( directory_iterator_impl* impl_representation )
{
    if ( !impl_representation )
    {
        //inex::core::log::Msg              ( "Directory ALREADY closed" );
        return              ;
    }

	//inex::core::log::Msg	( "Directory '%p' closed", impl_representation );
    FindClose				( impl_representation->m_entry_pointer );

 }

inline
bool    read_next_entry ( directory_iterator_impl* impl_representation )
{
    // readdir returned m_value_returned.

    //inex::core::log::Msg	( "New entry found '%p' \"%s\"", impl_representation, impl_representation->m_directory.cFileName );

    return               FindNextFile( impl_representation->m_entry_pointer,
						&impl_representation->m_directory );
}

} // namsepace detail
} // namespace fsmgr
} // namespace core
} // namespace inex

#   endif // if IE_PLATFORM_WINDOWS

#endif // #ifndef FS_CATALOG_OPERATIONS_WIN_IMPL_H_INCLUDED