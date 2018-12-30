#ifndef FS_PATH_STRING_H_INCLUDED
#   define FS_PATH_STRING_H_INCLUDED

namespace inex {
namespace fs {

class path_string
{
// create define for this
public:
//	static const s8	separator		=				FS_SEPARATOR;
public:
									path_string		( );
    explicit    					path_string		( pcstr const file_path_raw );
									path_string		( path_string const& rhs );
									~path_string	( ) =   default;

                void                operator /      ( pcstr const file_path_raw );

				pcstr const	c_str           ( )  const;

				#if IE_PLATFORM_WINDOWS
				void				disappend_star	( )
									{
										u32 string_length		= strlen ( m_string_value );
										//inex::core::logging::Msg( "path before:\t%s\n", m_string_value );
										ASSERT_S( * ( m_string_value + string_length ) != '*'  );
										* ( m_string_value + string_length - 1  )	= 0;
										//inex::core::logging::Msg( "path after:\t%s\n", m_string_value );
									}
				#endif // #if IE_PLATFORM_WINDOWS

                pcstr const   file_name       ( ) const
                {
                    const char* substring;
                    if ( !( substring = strrchr( m_string_value, '/') ) )
                    {
                        printf                  ( "sshit occured with\n%s\n", m_string_value );
                        getchar                 ( );
                        return                  nullptr;
                    }

                    if ( * (substring + 1 ) == 0 )
                    {
                        printf                  ( "dumb / at end of %s\n", m_string_value );
                        for ( ; * (substring ) != '/'; --substring )
                            ;
                        printf                  ( "real filename: %s\n", m_string_value );
                    }

                    return                      ++substring;
                }

				pcstr 				absolute        ( )  const;
                void                append          ( pcstr const file_path_raw );

                bool                is_directory    ( ) const
                                    {
                                        return      detail::is_directory_by_path( m_string_value );
                                    }
private:
	//-----------------------------------------------------------------------------------
	// private
	//-----------------------------------------------------------------------------------
				path_string&		operator =      ( path_string const& rhs )  =   delete;

                bool                is_system_catalog ( ) const
                                    {
                                        return          detail::is_system_directory( m_string_value );
                                    }
private:
    friend class recursive_directory_iterator;
	char	m_string_value          [ IE_MAX_PATH + 1 ];
}; // class path_string

} // namespace fs
} // namespace inex

#   include "fs_path_string_inline.h"

#endif // #ifndef FS_PATH_STRING_H_INCLUDED
