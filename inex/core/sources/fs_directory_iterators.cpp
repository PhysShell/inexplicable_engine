#include "stdafx.h"
#include "fs_directory_iterators.h"

namespace inex {
namespace fs {

//-----------------------------------------------------------------------------------
// class directory_iterator
//-----------------------------------------------------------------------------------

directory_iterator&     directory_iterator::operator ++ ( )
{
    VERIFY( !m_end );

    if ( !detail::read_next_entry ( m_impl.get( ) ) )
    {
        /* printf  ( "read_next_entry returned false\n" ); */
        m_end                           = 1;
        detail::close_directory         ( m_impl.get( ) );

        return                          *this;
    }
    //else
    m_entry.path( ).operator /          ( detail::file_path_raw_c_str( m_impl.get( ) ) );

    return                              *this;
}

//-----------------------------------------------------------------------------------
// class recursive_directory_iterator
//-----------------------------------------------------------------------------------

recursive_directory_iterator::recursive_directory_iterator ( const char* const file_path_raw ) :
    m_end               ( 1 ),
    m_directories       ( ),
    m_entry             ( file_path_raw )
{
    read_subdirectories ( m_entry.path( ).c_str( ) );
    if ( m_directories.is_empty( ) )
    {
        /* printf          ( "NO directories found!\n" ); */
        return          ;
    }


	//logging::Msg( "dirs:\n" );
	//while ( !m_directories.is_empty( ) )
	//{
	//	logging::Msg( "%s\n", m_directories.back( ).m_p );
	//	m_directories.pop( );
	//}

	
    m_impl.reset        ( memory::ie_new< detail::directory_iterator_impl >( ) );
    m_end               = 0;
    m_entry.append      ( m_directories.back( ).m_p );
#if IE_PLATFORM_WINDOWS
	m_entry.path( ) /	( "*" );
	//LOGGER( "%s", m_entry.path( ).c_str( ) );
#endif // IE_PLATFORM_WINDOWS
    detail::open_directory  ( m_impl.get( ), m_entry.path( ).c_str( ) );
#if IE_PLATFORM_WINDOWS
	m_entry.path( ).disappend_star( );
#endif // IE_PLATFORM_WINDOWS
    operator            ++ ( );
}

recursive_directory_iterator&   recursive_directory_iterator::operator ++ ( )
{
    VERIFY                            ( !m_end );
    bool end_of_catalog                 ;
    end_of_catalog                      = !detail::read_next_entry ( m_impl.get( ) );

    if ( !end_of_catalog )              m_entry.path( ) / ( detail::entry_name( m_impl.get( ) ) );
    else                                m_directories.pop           ( );

    if ( end_of_catalog )
    {
        if ( m_directories.is_empty( ) )
        {
            m_end                       = 1;
            detail::close_directory     ( m_impl.get( ) );
        }
        else
        {
            detail::close_directory     ( m_impl.get( ) );
            m_entry.append              ( m_directories.back( ).m_p );
#if IE_PLATFORM_WINDOWS
			m_entry.path( ) /	( "*" );
#endif // IE_PLATFORM_WINDOWS
            detail::open_directory      ( m_impl.get( ), m_entry.path( ).c_str( ) );
 #if IE_PLATFORM_WINDOWS
			m_entry.path( ).disappend_star( );
#endif // IE_PLATFORM_WINDOWS
			operator ++                 ( );
        }
    }
    else if ( m_entry.path( ).is_system_catalog( ) )
    {
        operator ++                     ( );
    }

    return                              *this;
}

void    recursive_directory_iterator::read_subdirectories ( const char* const file_path_raw )
{
    directory_iterator  current             ( file_path_raw );
    file_info           file_path_to_stack  ;
    char                next_subdirectory   [ IE_MAX_PATH ] { 0 };

    strcpy              ( next_subdirectory, file_path_raw );
    strcpy              ( file_path_to_stack.m_p, file_path_raw );

    if ( m_directories.is_empty( ) )
    {
        m_directories.push( file_path_to_stack );
    }

    for ( ; current != end( current ); ++current )
    {
        if ( ( * current ).path( ).is_system_catalog( ) )
        {
            continue;
        }

        strcpy                  ( next_subdirectory, ( *current ).path( ).c_str( ) );
	
		if ( ( *current ).path( ).is_directory( ) )
        {
            strcat              ( next_subdirectory, "/" );
            strcpy              (   file_path_to_stack.m_p,
                                    strcat( next_subdirectory, "*" ) );
            m_directories.push  ( file_path_to_stack );
            read_subdirectories ( next_subdirectory );
        }
    }
}

} // namespace fs
} // namespace inex
