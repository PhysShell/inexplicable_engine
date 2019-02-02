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

class general_allocator : public base_allocator
{
public:
    virtual void    initialize      ( pvoid arena, size_t const size, pcstr id ) override;
    virtual size_t  fragmented_size ( ) const override		{	return 0;	}
    virtual size_t  total_size      ( ) const override		{	return 0;	}
	virtual size_t  allocated_size  ( ) const override		{	return 0;	}
}; // class general_allocator

} // namespace memory
} // namespace inex

#endif // #ifndef MEMORY_GENERAL_ALLOCATOR_H_INCLUDED