#ifndef FS_FILE_SYSTEM_INTERNAL_H_INCLUDED
#	define FS_FILE_SYSTEM_INTERNAL_H_INCLUDED

namespace inex {
namespace fs {

struct INEX_CORE_API memory_mapped_file
{
public:
# if INEX_PLATFORM_WINDOWS
    pvoid			m_file_raw_pointer;
	pvoid			m_mapped_file;
#elif INEX_PLATFORM_LINUX
    s32             m_file_descriptor;
#endif // # if INEX_PLATFORM_WINDOWS

    size_t          m_size;
    pstr			m_data;

public:
					memory_mapped_file	( ) :
					#if INEX_PLATFORM_WINDOWS
						m_file_raw_pointer	{ },
						m_mapped_file		{ },
						m_size				{ }
                    #elif INEX_PLATFORM_LINUX
                        m_file_descriptor   ( ),
                        m_size              ( ),
                        m_data              ( )
                    #endif // # if INEX_PLATFORM_WINDOWS
					{
					}

explicit			memory_mapped_file  	( pcstr name );
//it seems to be a VC++ bug that forces us to define copy ctor
#ifdef _MSC_VER
explicit			memory_mapped_file		( memory_mapped_file const& ) { }
#endif //#ifdef _MSC_VER
explicit    		memory_mapped_file 		( memory_mapped_file&& file );

			void    close   				( );
}; // struct memory_mapped_file

struct memory_mapped_file_predicate
{
	bool operator( ) ( memory_mapped_file const& left, memory_mapped_file const& right) const
	{
		return ( left.m_size < right.m_size ) ? 1 : 0;
	}
}; // struct memory_mapped_file_predicate

} // namespace fs
} // namespace inex

#endif // #ifndef FS_FILE_SYSTEM_INTERNAL_H_INCLUDED
