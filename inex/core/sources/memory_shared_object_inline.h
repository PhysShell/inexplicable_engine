#ifndef MEMORY_SHARED_OBJECT_INLINE_H_INCLUDED
#	define  MEMORY_SHARED_OBJECT_INLINE_H_INCLUDED

namespace inex {
namespace memory {

#	define	TEMPLATE_SPECIALIZATION	template < typename T >
#	define	SHARED_OBJECT_TEMPLATE shared_object < T >
#   define  INTRUSIVE_PTR_TEMPLATE intrusive_ptr < T >

TEMPLATE_SPECIALIZATION
inline
INTRUSIVE_PTR_TEMPLATE::intrusive_ptr ( ) :
    m_data      ( nullptr )
{
}

TEMPLATE_SPECIALIZATION
inline
INTRUSIVE_PTR_TEMPLATE::intrusive_ptr ( pointer const& raw_pointer, bool add_reference = 1  ) :
    m_data      ( raw_pointer )
{
    if ( raw_pointer && add_reference )
    {
    // http://doc.crossplatform.ru/boost/1.37.0/doc/html/boost/interprocess/intrusive_ptr.html#id2906626-bb
    }
}

TEMPLATE_SPECIALIZATION
inline
SHARED_OBJECT_TEMPLATE::shared_object ( ) :
    m_owners    ( nullptr ),
    m_data      ( nullptr )
{
}

TEMPLATE_SPECIALIZATION
inline
SHARED_OBJECT_TEMPLATE::shared_object ( pointer const data ) :
    m_owners    (  memory::ie_new< size_t > ( 1u ) ),
    m_data      ( data )
{ 
}

TEMPLATE_SPECIALIZATION
inline
SHARED_OBJECT_TEMPLATE::shared_object ( SHARED_OBJECT_TEMPLATE const& owner ) :
    m_data      ( owner.m_data ),
    m_owners    ( owner.m_owners )
{
    increment         ( );
 }

TEMPLATE_SPECIALIZATION
inline
SHARED_OBJECT_TEMPLATE::~shared_object ( )
{
    if ( !m_data )
    {
        return ;
    }

    if ( decrement( ) < 1 )
    {
         release ( );
    }
}

TEMPLATE_SPECIALIZATION
inline
T const&  SHARED_OBJECT_TEMPLATE::operator * ( ) const
{
    return              *m_data;
}

TEMPLATE_SPECIALIZATION
inline
void  SHARED_OBJECT_TEMPLATE::reset ( T* const data )
{
#   pragma message ( "review this one" )
    if ( !data )
    {
        release ( );
        return              ;
    }

    if ( !m_owners )
    {
        m_owners            = memory::ie_new< size_t > ( 1u );
        m_data              = data;
    }
    else if ( unique( ) )
    {
        memory::ie_delete	( m_data );
        m_data              = data;
    }
    else
    {
        decrement           ( );
        m_owners            = memory::ie_new< size_t > ( 1u );
        m_data              = data;
    }
}

TEMPLATE_SPECIALIZATION
inline
T&  SHARED_OBJECT_TEMPLATE::operator * ( )
{
    return              *m_data;
}

TEMPLATE_SPECIALIZATION
inline
void  SHARED_OBJECT_TEMPLATE::release ( )
{
     //LOGGER ( "releasing DATA: %p\n", m_data ); 
	
    memory::ie_delete	( m_data );
    memory::ie_delete	( m_owners);
    m_owners            = nullptr;
    m_data              = nullptr;
}

TEMPLATE_SPECIALIZATION
inline
size_t  SHARED_OBJECT_TEMPLATE::owners ( ) const
{
    return              m_owners ? *m_owners : 0;
}

TEMPLATE_SPECIALIZATION
inline
bool    SHARED_OBJECT_TEMPLATE::unique ( ) const
{
    return              *m_owners == 1;
}

TEMPLATE_SPECIALIZATION
inline
void    SHARED_OBJECT_TEMPLATE::increment ( )
{
    ++                  *m_owners;
}

TEMPLATE_SPECIALIZATION
inline
size_t  SHARED_OBJECT_TEMPLATE::decrement ( )
{
    return              --*m_owners;
}

TEMPLATE_SPECIALIZATION
inline
typename SHARED_OBJECT_TEMPLATE::pointer const    SHARED_OBJECT_TEMPLATE::get ( )
{
    return              m_data;
}

TEMPLATE_SPECIALIZATION
inline
const typename SHARED_OBJECT_TEMPLATE::pointer const  SHARED_OBJECT_TEMPLATE::get ( ) const
{
    return              m_data;
}

#undef	TEMPLATE_SPECIALIZATION
#undef	SHARED_OBJECT_TEMPLATE
#undef  INTRUSIVE_PTR_TEMPLATE


} // namespace memory
} // namespace inex

#endif // #ifndef MEMORY_SHARED_OBJECT_INLINE_H_INCLUDED