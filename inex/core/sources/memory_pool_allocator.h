////////////////////////////////////////////////////////////////////////////
//	Created 	: 16.01.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MEMORY_POOL_ALLOCATOR_H_INCLUDED
#	define MEMORY_POOL_ALLOCATOR_H_INCLUDED

#	include "memory_base_allocator.h"
#   include <malloc.h>

namespace inex {
namespace memory {

#	if INEX_PLATFORM_WINDOWS
#		define MALLOC_SIZE( x )	_msize( x )
#	elif INEX_PLATFORM_LINUX // #ifINEX_PLATFORM_WINDOWS
#		define MALLOC_SIZE( x ) malloc_usable_size( x )
#	endif // #if INEX_PLATFORM_WINDOWS

template < class allocator_type >
struct allocator_wrapper : private allocator_type
{
	typedef		allocator_type			super;
	pvoid		malloc			( size_t const size )
				{
					size_t * pointer_size	= static_cast< size_t * >( super::malloc_impl( size + sizeof( size_t ) ) );
					return					*pointer_size = size, pointer_size + 1;		// skip head
				}

	void		free			( pvoid pointer )
				{
					super::free_impl		( static_cast< size_t * >( pointer ) - 1 );	// pass head
				}
}; // struct allocator_wrapper

#	if !INEX_USE_CRT_MEMORY_ALLOCATOR

// there's basically one pool of const size allocated, and after it's finished it frees all the memory.
// template < u64 size = 65536u, u64 alignment = sizeof ( pvoid ) >
class pool_allocator : public base_allocator
{
public:
				        pool_allocator			( );
				        ~pool_allocator			( )												{	finalize( ) ;	}

    virtual size_t      fragmented_size			( ) const override								{	return 0;	}
    virtual size_t      total_size				( ) const override								{	return 0;	}
	virtual size_t      allocated_size			( ) const override								{	return MALLOC_SIZE( m_arena );	}

	virtual void	    finalize				( );
    virtual void        initialize				( pvoid arena, size_t const size, pcstr id );
    virtual void	    free_impl				( pvoid ap );
    virtual pvoid	    malloc_impl				( u32 size );
			void		dump_memory_statistics  ( ) const;

    template < typename T >
    inline  T*          malloc_impl				( u32 size )									{   return reinterpret_cast< T* >( malloc_impl( size ) ); }

    template < typename T >
    inline  void        free_impl				( T*& pointer )									{   free_impl( reinterpret_cast< pvoid& >( pointer ) ); }
private:
            pvoid		on_malloc				( unsigned nu );
private:
	pvoid		m_arena;

    memory_monitor      m_monitor;
private:


}; // class pool_allocator

#	else
class crt_allocator;
typedef crt_allocator	pool_allocator
#	endif

} // namespace memory
} // namespace inex

#endif // #ifndef MEMORY_POOL_ALLOCATOR_H_INCLUDED
