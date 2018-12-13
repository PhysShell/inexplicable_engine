#ifndef FS_DIRECTORY_ENTRY_INLINE_H_INCLUDED
#   define FS_DIRECTORY_ENTRY_INLINE_H_INCLUDED

namespace inex {
namespace core {
namespace fsmgr {

inline
path_string&    directory_entry::path ( )
{
    return              m_file_path;
}

inline
path_string const&    directory_entry::path ( ) const
{
    return              m_file_path;
}

inline
directory_entry&    directory_entry::operator = ( directory_entry const& rhs )
{
    ASSERT_S( 0 );
}

inline
void    directory_entry::append ( const char* const file_path_raw )
{
    m_file_path.append              ( file_path_raw );
}

inline
directory_entry::directory_entry ( ) :
    m_file_path     ( )
{
}

inline
directory_entry::directory_entry ( directory_entry const& rhs ) :
    m_file_path     ( rhs.m_file_path )
{
}

inline
directory_entry::directory_entry ( const char* const file_path_raw ) :
    m_file_path     ( file_path_raw )
{
}

} // namespace fsmgr
} // namespace core
} // namespace inex
#endif // #ifndef FS_DIRECTORY_ENTRY_INLINE_H_INCLUDED
