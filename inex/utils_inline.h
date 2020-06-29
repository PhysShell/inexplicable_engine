#ifndef UTILS_INLINE_H_INCLUDED
#	define UTILS_INLINE_H_INCLUDED

#   include "utils.h"
#   include <inex/core/sources/ie_memory.h>

#   define TEMPLATE_SPECIALIZATION         template < typename data_type >
#   define stack_specialized               stack< data_type >

namespace inex {

TEMPLATE_SPECIALIZATION
inline
stack_specialized::~stack ( )
{
    // save pointer to the last
    Node* node			= m_last;

    while ( node )
	{
        // update the end
        m_last  		= m_last->previous;
        memory::ie_delete( node );
        node   		 	= m_last;
    }
}

TEMPLATE_SPECIALIZATION
inline
void    stack_specialized::push ( data_type const& rhs )
{
    Node* node			= memory::ie_new< Node >( );
    node->value     	= rhs;

    if ( !m_first )
	{
        m_first         = node;
        node->previous  = nullptr;
    }
	else
	{
        node->previous  = m_last;
    }

    m_last          	= node;
}

TEMPLATE_SPECIALIZATION
inline
void     stack_specialized::pop ( )
{
    if ( m_last == m_first )
	{
        memory::ie_delete( m_first );
        m_first = m_last = nullptr;
        return;
    }

    Node* node			= m_last;
    m_last          	= m_last->previous;

    memory::ie_delete	( node );
    node 				= nullptr;
}

TEMPLATE_SPECIALIZATION
inline
stack_specialized::stack ( ) :
	m_first				( nullptr ),
	m_last				( nullptr )
{
}

TEMPLATE_SPECIALIZATION
inline
bool    stack_specialized::is_empty ( ) const
{
    return				!m_first;
}

TEMPLATE_SPECIALIZATION
inline
data_type&	stack_specialized::back ( )
{
    return				m_last->value;
}

} // namespace inex

#undef              TEMPLATE_SPECIALIZATION
#undef              stack_specialized
#endif // #ifndef UTILS_INLINE_H_INCLUDED
