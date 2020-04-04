#ifndef FS_INI_FILE_H_INCLUDED
#	define FS_INI_FILE_H_INCLUDED

#   include <vector>
#   include <inex/math_float3.h>

// I should be using shared memory, buf for now, I don't
namespace inex {
namespace ini {

class INEX_CORE_API ini_file
{
	struct item
	{
		pstr first;
		pstr second;
	}; // struct item

	using section_contents					= std::vector< item >;
	using section_contents_iterator			= section_contents::iterator;
	using section_contents_const_iterator	= section_contents::const_iterator;

	struct section
	{
		pstr				name;
		section_contents	data;
	}; // struct section

	using root					= std::vector< section* >;
	using root_iterator			= root::iterator;
	using root_const_iterator	= root::const_iterator;

	root	m_contents;

public:
        // we should also pass reader* to Load....
	void		load		( pcstr name );
    section*	r_section   ( pcstr sect ) const;
	s32			r_s32		( pcstr sect, pcstr key ) const;
    u32         r_u32       ( pcstr sect, pcstr key ) const;
	float		r_float		( pcstr sect, pcstr key ) const;
    math::float3 r_float3   ( pcstr sect, pcstr key ) const;
	pcstr		r_string   	( pcstr sect, pcstr key ) const;
				~ini_file	( );
}; // class ini_file

} // names ini
} // namespace inex
#endif //#ifndef FS_INI_FILE_H_INCLUDED


