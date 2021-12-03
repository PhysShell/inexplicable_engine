////////////////////////////////////////////////////////////////////////////
//	Created 	: 03.12.2021
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_UNINITIALIZED_REFERENCE_H_INCLUDED
#	define INEX_UNINITIALIZED_REFERENCE_H_INCLUDED

#	include <inex/utils.h>
#	include <inex/debug/pointer_cast.h>

namespace inex {

// typical use: static objects that has no lifetime limit and live until process is destroyed
// typical memory occupation: BSS and DATA segments
template < class Class >
class uninitialized_reference : public detail::nonassignable, public detail::noncopyable
{
public:
	inline					uninitialized_reference	( ) :
		m_initialized			( 0 ),
		m_construction_started	( 0 ),
		m_variable				( ( Class & ) m_static_memory)
	{
	}
	
	inline Class * 			operator ->				( )			{ VERIFY( m_initialized ); return & m_variable; }
	inline Class &			operator *				( )			{ VERIFY( m_initialized );	return m_variable;	}
	inline Class const * 	operator ->				( ) const	{ VERIFY( m_initialized ); return & m_variable;	}
	inline Class const &	operator *				( ) const 	{ VERIFY( m_initialized );	return m_variable;	}
	
	inline Class * 			c_pointer				( )			{ VERIFY( m_initialized ); return & m_variable;	}
	inline Class const *	c_pointer				( ) const 	{ VERIFY( m_initialized ); return & m_variable;	}
	
	inline Class * 			operator + 				( Class * )	{ VERIFY( m_initialized ); threading::interlocked_exchange( m_initialized, 1 ); return & m_variable; }
	inline 					operator Class			( )			{ return m_variable; }
	inline 					operator Class const &	( ) const 	{ return m_variable; }
	
	inline bool 			initialized				( ) const	{ return m_initialized != 0; }
	inline bool 			should_initialize		( )
	{
		if ( threading::interlocked_exchange( m_construction_started, 1 ) == 1 )
		{
			while ( !m_initialized ) { ; }
			return 				false;
		}
		
		return 					true;
	}
	
	inline Class * 			construction_memory		( )
	{
		VERIFY					( ! m_initialized );
		return					::inex::pointer_cast< Class * >( m_static_memory );
	}
	
	inline void 			destroy 				( )
	{
		VERIFY					( m_initialized );
		m_vaiable.~Class 		( );
		m_initialized		=	false;
	}
}

private:
	//__forceinline__ void	ensure_initialization	( )			{ VERIFY( m_initialized ); }
	
private:
	byte INEX_DEFAULT_ALIGN		m_static_memory[ sizeof ( Class ) ];
	Class & 					m_variable;
	threading::atomic32_type 	m_initialized;
	threading::atomic32_type 	m_construction_started;

} // namespace inex

#	define INEX_CONSTRUCT_REFERENCE(uninitialized_ref, Class) 												\
		uninitialized_ref + new ( uninitialized_ref.construction_memory() ) Class

#	define INEX_CONSTRUCT_REFERENCE_MT_SAFE(uninitialized_ref, Class)										\
		( uninitialized_ref.initialized() || !uninitialized_ref.should_initialize() )	?					\
			nullptr : uninitialized_ref + new ( uninitialized_ref.construction_memory() ) Class

#	define INEX_CONSTRUCT_REFERENCE_BY_PREDICATE_MT_SAFE(uninitialized_ref, construction_predicate)			\
		( uninitialized_ref.initialized() || !uninitialized_ref.should_initialize() )	?					\
			nullptr : uninitialized_ref + construction_predicate(uninitialized_ref.construction_memory())

#	define INEX_DESTROY_REFERENCE(uninitialized_ref)														\
		uninitialized_ref.destroy();

#endif // #ifndef INEX_UNINITIALIZED_REFERENCE_H_INCLUDED
