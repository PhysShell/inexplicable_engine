////////////////////////////////////////////////////////////////////////////
//	Created 	: 29.12.2018
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef FS_UTILS_H_INCLUDED
#	define FS_UTILS_H_INCLUDED

#	if ( INEX_PLATFORM_WINDOWS )
#		include	"fs_catalog_operations_win_impl.h"
#	elif ( INEX_PLATFORM_LINUX ) // #if ( INEX_PLATFORM_WINDOWS )
#		include	"fs_catalog_operations_linux_impl.h"
#	else // #if ( INEX_PLATFORM_WINDOWS )
#		error please define your platform here
#	endif // #if ( INEX_PLATFORM_WINDOWS )

namespace inex {
namespace fs {
	// INEX_API
	inline
	bool    is_directory ( pcstr const file_path )
	{		return			detail::is_directory_by_path( file_path );	}

	inline
	bool	is_system_catalog ( pcstr const file_path )
	{		 return         detail::is_system_directory( file_path );	}
	
	inline
	bool	exists ( pcstr const file_path_raw )
	{		return			detail::exists( file_path_raw );			}
	//make it in 
	//bool	exists ( path_string const& file_path )	{	return	detail::exists( file_path.c_str( ) );	}
} // namespace fs
} // namespace inex

#endif // #ifndef FS_UTILS_H_INCLUDED