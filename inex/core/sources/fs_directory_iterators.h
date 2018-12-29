#ifndef FS_DIRECTORY_ITERATORS_H_INCLUDED
#   define FS_DIRECTORY_ITERATORS_H_INCLUDED

#if ( IE_PLATFORM_WINDOWS )
#	include	"fs_catalog_operations_win_impl.h"
#elif ( IE_PLATFORM_LINUX ) // #if ( IE_PLATFORM_WINDOWS )
#	include	"fs_catalog_operations_linux_impl.h"
#else // #if ( IE_PLATFORM_WINDOWS )
#	error please define your platform here
#endif // #if ( IE_PLATFORM_WINDOWS )

#   include <inex/utils.h>
#   include "memory_shared_object.h"
#   include "fs_path_string.h"
#   include "fs_directory_entry.h"

namespace inex {
namespace core {
namespace fsmgr {

class directory_iterator
{
    typedef path_string                 value_type;
    typedef std::ptrdiff_t              difference_type;
    typedef const path_string*          pointer;
    typedef path_string const&          reference;
//  typedef std::input_iterator_tag     iterator_category;

public:
	//-----------------------------------------------------------------------------------
	// initializations
	//-----------------------------------------------------------------------------------
                        directory_iterator	            ( );
    explicit            directory_iterator	            ( path_string const& file_path_string );
    explicit            directory_iterator	            ( const char* const file_path_raw );
                        directory_iterator& operator =  ( directory_iterator const& )  =   delete;
                // can be default, too
                        directory_iterator	            ( directory_iterator const& iter );
                        //directory_iterator	            ( directory_iterator& iter );
                        //directory_iterator	            ( directory_iterator&& rvalue) = default;
                        ~directory_iterator	            ( ) = default;

    //-----------------------------------------------------------------------------------
	// operations
	//-----------------------------------------------------------------------------------
	bool		        operator !=	                    ( directory_iterator const& iter ) const;
	directory_iterator&	operator ++	                    ( );
//  bool                is_directory                    ( ) const;

	//-----------------------------------------------------------------------------------
	// accessors
	//-----------------------------------------------------------------------------------
	directory_entry const&  operator *	                    ( ) const;
    directory_entry&        operator *	                    ( ) ;

private:
    /* no need impl, could just call detail::function in function */
    memory::shared_object< detail::directory_iterator_impl > m_impl;
    directory_entry											m_entry;
    bool													m_end;
}; // class directory_iterator


//-----------------------------------------------------------------------------------
// recursive_directory_iterator
//-----------------------------------------------------------------------------------

/* TODO:
 * copy, move ctors; operator =
 * get rid of file_path
*/
class recursive_directory_iterator
{
public:
    typedef recursive_directory_iterator        self_type;
public:
	//-----------------------------------------------------------------------------------
	// initializations
	//-----------------------------------------------------------------------------------
												recursive_directory_iterator	        ( ) :
                                                    m_end           ( 1 )
                                                {
                                                }

    explicit									recursive_directory_iterator	        ( path_string const& file_path );
    explicit									recursive_directory_iterator	        ( const char* const file_path_raw );
    //                                            recursive_directory_iterator            ( self_type&& rvalue )  = delete;
												// can be default, too
												recursive_directory_iterator	        ( self_type const& iter );
				recursive_directory_iterator&   operator =								( self_type const& )  = delete;

												~recursive_directory_iterator	        ( ) { }

	//-----------------------------------------------------------------------------------
	// operations
	//-----------------------------------------------------------------------------------
			bool								operator !=								( recursive_directory_iterator const& iter ) const;
			recursive_directory_iterator&		operator ++								( );
			directory_entry const&  			operator *								( ) const;

private:
	//-----------------------------------------------------------------------------------
	// private
	//-----------------------------------------------------------------------------------
			void								read_subdirectories						( const char* const file_path_raw );
private:
    struct file_info
    {
        char                                        m_p         [ IE_MAX_PATH ];
    }; // struct file_info


    directory_entry											m_entry;
	utils::stack< file_info >								m_directories;
    memory::shared_object< detail::directory_iterator_impl > m_impl;
    bool													m_end;
}; // class recursive_directory_iterator

} // namespace fsmgr
} // namespace core
} // namespace inex

#   include "fs_directory_iterators_inline.h"
#endif // #ifndef FS_DIRECTORY_ITERATORS_H_INCLUDED
