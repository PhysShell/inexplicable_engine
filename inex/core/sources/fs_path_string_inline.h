#ifndef FS_PATH_STRING_INCLUDED_H_INCLUDED
#   define FS_PATH_STRING_INCLUDED_H_INCLUDED

namespace inex {
namespace fs {

inline
path_string::path_string ( ) :
    m_string_value  { 0 }
{
}

inline
path_string::path_string ( pcstr const file_path_raw )
{
    strcpy                  ( m_string_value, file_path_raw );
}

inline
path_string::path_string ( path_string const& rhs )
{
    strcpy                  ( m_string_value, rhs.m_string_value );
}

inline
void path_string::append ( pcstr const file_path_raw )
{
    strcpy              ( m_string_value, file_path_raw );
}

inline
pcstr const path_string::c_str ( ) const
{
    return              m_string_value;
}

inline
void    path_string::operator / ( pcstr const file_path_raw )
{
	pstr p				= strrchr( m_string_value, '/' );
	ASSERT_D( p, "Couldn't find enclosing '/'. Check '%s'.", m_string_value );
    strcpy              ( p + 1, file_path_raw );
}


} // namespace fs
} // namespace inex

#endif // #ifndef FS_PATH_STRING_INCLUDED_H_INCLUDED