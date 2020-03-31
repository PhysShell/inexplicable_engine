////////////////////////////////////////////////////////////////////////////
//	Created 	: 17.01.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MEMORY_GENERAL_ALLOCATOR_H_INCLUDED
#	define MEMORY_GENERAL_ALLOCATOR_H_INCLUDED

#	include <inex/utils.h>
#	include "memory_base_allocator.h"

namespace inex {
namespace memory {
class general_allocator : public memory::base_allocator
{
private:
	typedef alignment_type dummy;
	union header
	{
		struct
		{
			union header *ptr;	/*  ,   */
			u32 size;			/*    */
		} s;
		dummy dummy;			/*    */
	};
	typedef union header header_type;

public:
				        general_allocator	( );
				        ~general_allocator	( )                     { finalize( ) ; }
    
    virtual size_t      fragmented_size     ( ) const override		{	return 0;	}
    virtual size_t      total_size          ( ) const override		{	return 0;	}
	virtual size_t      allocated_size      ( ) const override		{	return 0;	}

	virtual void	    finalize		    ( );
    virtual void        initialize          ( pvoid arena, size_t const size, pcstr id );
    virtual void	    free_impl		    ( pvoid ap );
    virtual pvoid	    malloc_impl		    ( u32 size );

private:
            header_type* on_malloc          (unsigned nu);
private:
	header_type*		m_arena;
	header_type*		m_arena_end;
    header_type*        m_helper;

}; // class general_allocator

} // namespace memory
} // namespace inex

#endif // #ifndef MEMORY_GENERAL_ALLOCATOR_H_INCLUDED
