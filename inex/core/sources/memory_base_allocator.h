////////////////////////////////////////////////////////////////////////////
//	Created 	: 16.01.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MEMORY_BASE_ALLOCATOR_H_INCLUDED
#	define MEMORY_BASE_ALLOCATOR_H_INCLUDED

#	include <inex/utils.h>

namespace inex {
namespace memory {

class base_allocator : 	private detail::nonassignable,
						private detail::noncopyable
{
public:
                    base_allocator  ( );
    virtual         ~base_allocator ( )         {                       }
    virtual void    initialize      ( pvoid arena, size_t const size, pcstr id );
    virtual void    finalize        ( );

    virtual pvoid   malloc_impl     ( u32 size /* add declaration for debug */ );
    virtual void    free_impl       ( pvoid pointer );

    // inline  bool    initialized     ( ) const   {   return m_arena;     }
    // inline	pcstr	arena_id		( ) const   {   return m_arena_id;  }
    virtual size_t          fragmented_size ( ) const = 0;
    virtual size_t          total_size      ( ) const = 0;
    virtual size_t          allocated_size  ( ) const = 0;

protected:
    // inline  size_t  needed_size     ( size_t const size ) const   {   return size; /* + caption */  }
    // inline  pvoid   ensure_alignment( );

protected:

    typedef ptrdiff_t       alignment_type;
	static constexpr
            size_t const    alignment_value = sizeof ( alignment_type );
    // pvoid   m_arena;
    // pvoid   m_arena_end;
    pcstr	m_arena_id;

private:


}; // class base_allocator

} // namespace memory
} // namespace inex

#endif // #ifndef MEMORY_BASE_ALLOCATOR_H_INCLUDED
