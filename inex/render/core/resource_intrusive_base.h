#pragma once

#include <inex/types.h>

namespace inex {
namespace render {

class resource_intrusive_base //: private boost::noncopyable
{
public:
			inline			resource_intrusive_base	( );

	template < typename T >
	static	inline void		destroy					( T const* instance );

public:
	u32	mutable				m_reference_count;
};

inline resource_intrusive_base::resource_intrusive_base	( ) :
	m_reference_count							( 0 )
{
}

template < typename T >
inline void resource_intrusive_base::destroy			( T const* const instance )
{
	instance->T::destroy_impl	( );
}

} // namespace render
} // namespace inex