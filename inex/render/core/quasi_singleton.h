#ifndef QUASI_SINGLETON_H_INCLUDED
#	define QUASI_SINGLETON_H_INCLUDED

#	include <inex/utils.h>

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

template < class T >
class quasi_singleton : details::noncopyable
{
public:
				quasi_singleton	( );
				~quasi_singleton( );
	static T *	pointer 		( );
	static T &	reference 		( );
	
private:
	static T *	m_instance;
} // class quasi_singleton

} // namespace inex

template < class T >
T *	inex::quasi_singleton< T >::m_instance	= 0;

inline template < class T >
inex::quasi_singleton< T >::quasi_singleton ( )
{
	VERIFY			( !m_instance );
	m_instance 		= 	static_cast_checked< T * >( this );
}

inline template < class T >
inex::quasi_singleton< T >::~quasi_singleton ( )
{
	VERIFY 			( m_instance );
	m_instance 		= 	nullptr;
}

inline template <class T>
T&	inex::quasi_singleton< T >::reference ( )
{
	VERIFY			( m_instance );
	return 			* m_instance;
}

inline template <class T>
T *	inex::quasi_singleton< T >::pointer ( )
{
	VERIFY			( m_instance );
	return 			m_instance;
}

#endif // #ifndef QUASI_SINGLETON_H_INCLUDED
