#ifndef FS_PATH_STRING_INCLUDED_H_INCLUDED
#   define FS_PATH_STRING_INCLUDED_H_INCLUDED

namespace inex {
namespace core {
namespace fsmgr {

inline
path_string::path_string ( ) :
    m_string_value  { 0 }
{
}

inline
path_string::path_string ( const char* const file_path_raw )
{
    strcpy                  ( m_string_value, file_path_raw );
}

inline
path_string::path_string ( path_string const& rhs )
{
    strcpy                  ( m_string_value, rhs.m_string_value );
}

inline
void path_string::append ( const char* const file_path_raw )
{
    strcpy              ( m_string_value, file_path_raw );
}

inline
const char* const path_string::c_str ( ) const
{
    return              m_string_value;
}

inline
void    path_string::operator / ( const char* const file_path_raw )
{
    // assert strrchr is zero
    strcpy              ( strrchr( m_string_value, '/' ) + 1, file_path_raw );
}


} // namespace fsmgr
} // namespace core
} // namespace inex

#endif // #ifndef FS_PATH_STRING_INCLUDED_H_INCLUDED