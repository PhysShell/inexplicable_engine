#ifndef FS_DIRECTORY_ITERATORS_INLINE_H_INCLUDED
#   define FS_DIRECTORY_ITERATORS_INLINE_H_INCLUDED

#	if ( INEX_PLATFORM_WINDOWS )
#		include	"fs_catalog_operations_win_impl.h"
#	elif ( INEX_PLATFORM_LINUX ) // #if ( INEX_PLATFORM_WINDOWS )
#		include	"fs_catalog_operations_linux_impl.h"
#	else // #if ( INEX_PLATFORM_WINDOWS )
#		error please define your platform here
#	endif // #if ( INEX_PLATFORM_WINDOWS )

namespace inex {
namespace fs {

//-----------------------------------------------------------------------------------
// class directory_iterator
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
// initializations
//-----------------------------------------------------------------------------------

inline
directory_iterator::directory_iterator ( ) :
    m_impl      ( ),
    m_end       ( 1 )
{
}

inline
directory_iterator::directory_iterator ( directory_iterator const& rhs ) :
    m_impl          ( rhs.m_impl ),
    m_end           ( rhs.m_end )
{
    m_entry.append  ( rhs.m_entry.path( ).c_str( ) );
    detail::open_directory( m_impl.get( ), rhs.m_entry.path( ).c_str( ) );
    operator ++     ( );
}

inline
directory_iterator::directory_iterator ( const char* const file_path_raw ) :
    m_entry     ( file_path_raw ),
    m_impl      ( memory::ie_new< detail::directory_iterator_impl > ( ) ),
    m_end       ( 0 )
{
    detail::open_directory	( m_impl.get( ), m_entry.path( ).c_str( ) );
    operator ++				( );

}

//-----------------------------------------------------------------------------------
// operations
//-----------------------------------------------------------------------------------

inline
bool    directory_iterator::operator != ( directory_iterator const& iterator ) const
{
    return              m_end != iterator.m_end;
}

//-----------------------------------------------------------------------------------
// accessors
//-----------------------------------------------------------------------------------

inline
directory_entry const&  directory_iterator::operator * ( ) const
{
    return              m_entry;
}

inline
directory_entry&  directory_iterator::operator * ( )
{
    return              m_entry;
}

//-----------------------------------------------------------------------------------
// iterators
//-----------------------------------------------------------------------------------

inline
directory_iterator const&   begin ( directory_iterator const& iterator )
{
    return              iterator;
}

inline
directory_iterator  end ( directory_iterator const& )
{
    return              directory_iterator( );
}

//-----------------------------------------------------------------------------------
// class recursive_directory_iterator
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
// initializations
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// operations
//-----------------------------------------------------------------------------------

inline
bool    recursive_directory_iterator::operator != ( recursive_directory_iterator const& iter ) const
{
    return                          m_end != iter.m_end;
}

//-----------------------------------------------------------------------------------
// accessors
//-----------------------------------------------------------------------------------

inline
directory_entry const&  recursive_directory_iterator::operator * ( ) const
{
    return                          m_entry;
}

//-----------------------------------------------------------------------------------
// iterators
//-----------------------------------------------------------------------------------

inline
recursive_directory_iterator const&	begin ( recursive_directory_iterator const& iter ) noexcept
{
	return			iter;
}

inline
recursive_directory_iterator const	end ( recursive_directory_iterator const& ) noexcept
{
	return			recursive_directory_iterator( );
}

} // namespace fs
} // namespace inex

#endif // #ifndef FS_DIRECTORY_ITERATORS_INLINE_H_INCLUDED
