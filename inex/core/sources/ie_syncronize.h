#ifndef INEX_SYNCRONIZE_H_INCLUDED
#	define INEX_SYNCRONIZE_H_INCLUDED

#	include <inex/os_include.h>

#	if INEX_PLATFORM_WINDOWS
#		define CS_INIT( x ) 	InitializeCriticalSection   ( x )
#		define CS_DEL( x )	    DeleteCriticalSection       ( x )
#		define CS_ENTER( x )	EnterCriticalSection        ( x )
#		define CS_LEAVE( x )	LeaveCriticalSection        ( x )
#		define CS_OBJ	        CRITICAL_SECTION
#	elif INEX_PLATFORM_LINUX		// #if INEX_PLATFORM_WINDOWS 
#		define CS_INIT( x ) 	pthread_mutex_init          ( x, nullptr )
#		define CS_DEL( x )	    pthread_mutex_destroy       ( x )
#		define CS_ENTER( x )	pthread_mutex_lock          ( x )
#		define CS_LEAVE( x )	pthread_mutex_unlock        ( x )
#		define CS_OBJ	        pthread_mutex_t
#	endif // #if INEX_PLATFORM_WINDOWS

//#ifdef DEBUG
//#   define PROFILE_CRITICAL_SECTIONS
//#endif // #ifdef DEBUG

// if profile critical section, add a pcstr member in class
// to see which critical section it's applied to
// also, we need macro strings!

// Desc: Simple wrapper for critical section
namespace inex {
namespace threading {

class critical_section
{
public:
    inline      critical_section	( ) : m_cs( )    {   CS_INIT( &m_cs );  }
    inline      ~critical_section	( )              {   CS_DEL( &m_cs );   }
    inline  void enter				( )             {   CS_ENTER( &m_cs ); }
    inline  void leave				( )				{   CS_LEAVE( &m_cs ); }
private:
    CS_OBJ  m_cs;
}; // class critical_section

template <
    class locker,
    void ( locker::*en )( )		= &locker::enter,
    void ( locker::*le )( )		= &locker::leave
>
class scoped_lock
{
public:
    inline	explicit	scoped_lock	( locker& lock ) :
								m_lock		( lock )
						{
							( m_lock.*en )( );
						}

    inline      		~scoped_lock   ( )
						{
							( m_lock.*le )( );
						}
private:
    locker&	m_lock;
}; // class scoped_lock

typedef scoped_lock< critical_section > scope_locker;

} // namespace threading
} // namespace inex

#endif // INEX_SYNCRONIZE_H_INCLUDED
