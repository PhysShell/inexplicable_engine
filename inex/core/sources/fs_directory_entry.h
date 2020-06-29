#ifndef FS_DIRECTORY_ENTRY_H_INCLUDED
#   define FS_DIRECTORY_ENTRY_H_INCLUDED

namespace inex {
namespace fs {

class directory_entry
{
public:
                                    directory_entry     ( );
                                    directory_entry     ( directory_entry const& rhs );
                                    directory_entry     ( const char* const file_path_raw );
                                    ~directory_entry    ( ) =   default;

    directory_entry&                operator =          ( directory_entry const& rhs );

    path_string&                    path                ( );
    path_string const&              path                ( ) const;

    void                            append              ( const char* const );
private:
    path_string     m_file_path;
    /***
     * Provide file status when required explicitly only cuz it's expensive
    ***/
}; // class directory_entry

} // namespace fs
} // namespace inex

#   include "fs_directory_entry_inline.h"
#endif // #ifndef FS_DIRECTORY_ENTRY_H_INCLUDED
