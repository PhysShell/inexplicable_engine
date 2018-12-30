////////////////////////////////////////////////////////////////////////////
//	Created 	: 29.12.2018
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef FS_UTILS_H_INCLUDED
#	define FS_UTILS_H_INCLUDED

/**
 * For implementing other functionality,
 * remove such members in path_string
 * cuz they're causing cross-including stuff
**/

namespace inex {
namespace fs {
	//bool    is_system_directory ( pcstr const file_path_raw );
	//bool    is_directory_by_path ( pcstr const file_path );
	bool	exists ( pcstr const file_path_raw )	{	return	detail::exists( file_path_raw );		}
	//bool	exists ( path_string const& file_path )	{	return	detail::exists( file_path.c_str( ) );	}
} // namespace fs
} // namespace inex

#endif // #ifndef FS_UTILS_H_INCLUDED