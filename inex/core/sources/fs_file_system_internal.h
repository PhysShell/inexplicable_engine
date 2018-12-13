#ifndef FS_FILE_SYSTEM_INTERNAL_H_INCLUDED
#	define FS_FILE_SYSTEM_INTERNAL_H_INCLUDED

namespace inex {
namespace core {
namespace fsmgr {

struct memory_mapped_file
{
public:
# if IE_PLATFORM_WINDOWS
    pvoid   m_file_raw_pointer;
	pvoid   m_mapped_file;
    size_t  m_size;
#elif IE_PLATFORM_LINUX
    int             m_file_descriptor;
    size_t          m_size;
    char*           m_data;
#endif // # if IE_PLATFORM_WINDOWS

public:
					memory_mapped_file	( ) :
					#if IE_PLATFORM_WINDOWS
						m_file_raw_pointer	{ },
						m_mapped_file		{ },
						m_size				{ }
                    #elif IE_PLATFORM_LINUX
                        m_file_descriptor   ( ),
                        m_size              ( ),
                        m_data              ( )
                    #endif // # if IE_PLATFORM_WINDOWS
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
	inline bool operator( ) ( memory_mapped_file const& f1, memory_mapped_file const& f2) const
				{
					return ( f1.m_size < f2.m_size ) ? 1 : 0;
				}
}; // struct memory_mapped_file_predicate

//IC bool operator<(const memory_mapped_file& f1, const memory_mapped_file& f2)
//{
//	return f1.size<f2.size?1:0;
//}

} // namespace fsmgr
} // names core
} // namespace inex

#endif // #ifndef FS_FILE_SYSTEM_INTERNAL_H_INCLUDED
