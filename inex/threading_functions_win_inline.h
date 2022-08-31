////////////////////////////////////////////////////////////////////////////
//	Created 	: 02.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef THREADING_FUNCTIONS_WIN_INLINE_H_INCLUDED
#   define THREADING_FUNCTIONS_WIN_INLINE_H_INCLUDED

#	include <inex/core/sources/ie_memory.h>

#pragma intrinsic(_InterlockedCompareExchange,		\
				  _InterlockedCompareExchange64,	\
				  _InterlockedExchange,				\
				  _InterlockedIncrement,			\
				  _InterlockedDecrement,			\
				  _InterlockedAnd,					\
				  _InterlockedOr,					\
				  _InterlockedXor,					\
				  _InterlockedExchangeAdd			\
				 )

#if defined ( INEX_PLATFORM_WINDOWS_64 )
#	pragma intrinsic(_InterlockedExchangePointer)
#	define INEX_INTERLOCKED_EXCHANGE_POINTER(a,b)			_InterlockedExchangePointer(a,b)
#	define INEX_INTERLOCKED_COMPARE_EXCHANGE_POINTER(a,b,c)	_InterlockedCompareExchangePointer(&a,b,c)
#else // #if INEX_PLATFORM_WINDOWS_64
#	define INEX_INTERLOCKED_EXCHANGE_POINTER(a,b)			(atomic_ptr_value_type)_InterlockedExchange( (atomic32_type*)(a), *(atomic32_value_type const*)(&b) )
#	define INEX_INTERLOCKED_COMPARE_EXCHANGE_POINTER(a,b,c)	(atomic_ptr_value_type)_InterlockedCompareExchange( ( atomic32_type* )&a, *(atomic32_value_type const*)&b, *(atomic32_value_type const*)&c )
#endif // #if INEX_PLATFORM_WINDOWS_64

namespace inex {
namespace threading {

INEX_CORE_API
inline
atomic32_value_type		interlocked_increment			( atomic32_value_type * value )
{
	return							InterlockedIncrement( value );
}

INEX_CORE_API
inline
atomic32_value_type		interlocked_decrement			( atomic32_value_type * value )
{
	return 							InterlockedDecrement( value );
}

//INEX_THREADING_INLINE
INEX_CORE_API
inline
atomic32_value_type 	interlocked_exchange			( atomic32_type& target, atomic32_value_type value )
{
	return							_InterlockedExchange( &target, value );
}

INEX_CORE_API
inline
atomic_ptr_value_type	interlocked_exchange_pointer	( atomic_ptr_type& target, atomic_ptr_value_type const value )
{
	return							INEX_INTERLOCKED_EXCHANGE_POINTER( &target, value );
}

INEX_CORE_API
inline
atomic_ptr_value_type interlocked_compare_exchange_pointer( atomic_ptr_type& target, atomic_ptr_value_type const exchange, atomic_ptr_value_type const comperand )
{
	return							INEX_INTERLOCKED_COMPARE_EXCHANGE_POINTER(target, exchange, comperand);
}

inline
u32					current_thread_id						(  )
{
	return 							GetCurrentThreadId( );
}

inline
void				yield									( u32 ms )
{
	if ( ms )
	{
		Sleep						( ms );
		return;
	}
	
	if ( SwitchToThread() )
		return;
	
	Sleep							( 0 );
}


inline
u64						clock_cycle_count				( )					{	return 0;	}

inline
u64						clock_cycle_per_second			( )					{	return 0;	}

inline
u64						cache_line_size					( )
{
    DWORD line_size                                    = 0;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION * buffer   = nullptr;

    if ( ( GetLogicalProcessorInformation( buffer, & line_size ) == FALSE ) && ( GetLastError( ) == ERROR_INSUFFICIENT_BUFFER ) )
    {
        buffer = memory::ie_allocate< SYSTEM_LOGICAL_PROCESSOR_INFORMATION >( line_size );

        if (buffer == nullptr)
        {
            LOGGER( "buffer allocation of '%d' bytes failed", line_size );
        }
        else if (GetLogicalProcessorInformation(buffer, & line_size) != FALSE)
        {
            for ( DWORD i = 0; i < line_size; ++i )
            {
                if ( buffer[ i ].Relationship == RelationCache )
                {
                    line_size                   = buffer[i].Cache.LineSize;
                    break;
                }
            }
        }
        else
        {
            LOGGER( "error occured during collecting cache line info: '%s'", GetLastError( ) ); 
        }

        memory::ie_delete                       ( buffer );
    }

	return                                      line_size;
}

} // namespace threading
} // namespace inex

#endif // #ifndef THREADING_FUNCTIONS_WIN_INLINE_H_INCLUDED
