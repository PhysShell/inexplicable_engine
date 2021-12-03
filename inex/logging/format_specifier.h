////////////////////////////////////////////////////////////////////////////
//	Created 	: 03.12.2021
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_LOGGING_FORMAT_SPECIFIER_H_INCLUDED
#   define INEX_LOGGING_FORMAT_SPECIFIER_H_INCLUDED

#	include <inex/utils.h>

namespace inex {
namespace logging {

enum format_specifier_enum
{
	format_specifier_unset,
	format_specifier_thread_id,
	format_specifier_initiator,
	format_specifier_time,
	format_specifier_verbosity,
	format_specifier_message,
	format_specifier_separator,
	format_specifier_count,	
};

typedef fixed_vector< format_specifier_enum, format_specifier_count >	format_specifier_list;
typedef int 	format_index_container	[ format_specifier_count ];
typedef bool 	format_enabled_container[ format_specifier_count ];
typedef string512														format_string_type;

class format_specifier : private detail::nonassignable, private detail::noncopyable
{
public:
			format_specifier		( format_specifier_enum specifier );
			format_specifier		( format_specifier const & left, format_specifier const & right );
	
	void 	fill_specifier_list		( format_specifier_list & list, format_string_type * out_format_string ) const;
	
private:
	format_specifier const * 		m_left;
	format_specifier const * 		m_right;
	
	format_specifier_enum			m_specifier;
}; // format_specifier

struct format_separator : format_specifier
{
	format_separator				( pcstr separator ) :
		format_specifier( format_specifier_separator ),
		separator		( separator )
	{
	}
	
	string128						separator;
} // struct format_separator

inline
format_specifier	operator + 		( format_specifier const & left, format_specifier const & right )
{
	return 								format_specifier( left, right );
}


} // namespace logging
} // namespace inex

#endif // #ifndef INEX_LOGGING_FORMAT_SPECIFIER_H_INCLUDED
