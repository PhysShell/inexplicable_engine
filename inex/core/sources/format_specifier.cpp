#include "pch.h"
#include <inex/logging/format_specifier.h>

inex::logging::format_specifier		format_thread_id	( format_specifier_thread_id );
inex::logging::format_specifier		format_initiator	( format_specifier_initiator );
inex::logging::format_specifier		format_time			( format_specifier_time );
inex::logging::format_specifier		format_verbosity	( format_specifier_verbosity );
inex::logging::format_specifier		format_message		( format_specifier_message );


inex::logging::format_specifier::format_specifier			( format_specifier_enum specifier ) :
	m_specifier	( specifier ),
	m_left		( nullptr ),
	m_right		( nullptr )
{
}

inex::logging::format_specifier::format_specifier 			( format_specifier const & left, format_specifier const & right ) :
	m_specifier	( format_specifier_unset ),
	m_left		( & left ),
	m_right		( & right )
{
}

void 	inex::logging::format_specifier::fill_specifier_list ( format_specifier_list & list, format_string_type * out_format_string ) const
{
	if ( m_left )
	{
		format_string_type					left_string;
		m_left->fill_specifier_list			( list, & left_string );
		format_string_type					right_string;
		m_right->fill_specifier_list		( list, & right_string );
		* out_format_string				=	left_string;
		* out_format_string				+=	right_string;
	}
	else
	{
		if ( m_specifier != format_specifier_separator )
		{
			list.push_back					( m_specifier );
			* out_format_string			=	"%s";
		}
		else
		{
			format_separator const * const this_pointer	=	static_cast< format_separator const * >( this );
			* out_format_string			=	this_pointer->separator;
		}
	}
}
