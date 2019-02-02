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
    
public:
                    base_allocator  ( );
    virtual         ~base_allocator ( )         {                       }
            void    initialize      ( pvoid arena, size_t const size, pcstr id );
            void    finalize        ( );

            pvoid   malloc_impl     ( size_t const size /* add declaration for debug */ ); 
            void    free_impl       ( pvoid pointer );
    
    inline  bool    initialized     ( ) const   {   return m_arena;     }
    inline	pcstr	arena_id		( ) const   {   return m_arena_id;  }
    virtual size_t  fragmented_size ( ) const = 0;
    virtual size_t  total_size      ( ) const = 0;
    virtual size_t  allocated_size  ( ) const = 0;

protected:
    inline  size_t  needed_size     ( size_t const size ) const   {   return size; /* + caption */  }

private:
    pvoid   m_arena;
    pvoid   m_arena_end;
    pcstr	m_arena_id;

}; // class base_allocator

} // namespace ui
} // namespace memory

#endif // #ifndef MEMORY_BASE_ALLOCATOR_H_INCLUDED