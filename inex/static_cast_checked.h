#pragma once
namespace inex {

template < typename destination_type, typename source_type >
inline destination_type static_cast_checked	( source_type const & source )
{
	return			( static_cast< destination_type >( source ) );
}

template < typename destination_type, typename source_type >
inline destination_type static_cast_checked	( source_type & source )
{
	return			( static_cast< destination_type >( source ) );
}

} // namespace inex