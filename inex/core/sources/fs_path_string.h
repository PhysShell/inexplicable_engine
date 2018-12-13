#ifndef FS_PATH_STRING_H_INCLUDED
#   define FS_PATH_STRING_H_INCLUDED

namespace inex {
namespace core {
namespace fsmgr {

class path_string
{
// create define for this
public:
//	static const s8	separator		=				FS_SEPARATOR;
public:
									path_string		( );
    explicit    					path_string		( const char* const file_path_raw );
									path_string		( path_string const& rhs );
									~path_string	( ) =   default;

                void                operator /      ( const char* const file_path_raw );

				const char* const	c_str           ( )  const;
                const char* const   file_name       ( ) const
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
                void                append          ( const char* const file_path_raw );

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

} // namespace fsmgr
} // namespace core
} // namespace inex

#   include "fs_path_string_inline.h"

#endif // #ifndef FS_PATH_STRING_H_INCLUDED
