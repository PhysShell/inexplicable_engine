#ifndef SHARED_OBJECT_H_INCLUDED
#   define SHARED_OBJECT_H_INCLUDED

namespace inex {
namespace memory {

template < typename T >
class intrusive_ptr
{
    typedef intrusive_ptr< T >      self_type;
    typedef T*                      pointer;
    typedef T                       element_type;
public:
                            intrusive_ptr   ( );
                            intrusive_ptr   ( pointer const&, bool = 1 );
                            intrusive_ptr   ( self_type const& );
                            ~intrusive_ptr  ( );

            intrusive_ptr&  operator =      ( self_type const& );
            intrusive_ptr&  operator =      ( pointer );
            element_type&   operator *      ( ) const;
            const pointer&  operator ->     ( ) const;
            pointer&        operator ->     ( ) const;
                            operator bool   ( ) {   return m_data;  }
            bool            operator !      ( ) {   return !m_data; }
            
            pointer&        get             ( );
            const pointer&  get             ( ) const;
            void            swap            ( self_type& );  
private:
    pointer m_data;
}; // class intrusive_ptr

template < typename T >
class shared_object 
{
public:
    typedef shared_object < T >     self_type;
    typedef T*                      pointer;
    typedef T                       element_type;
// to make static member which look for memory leaks ( very simple )
public:
                        shared_object   ( );
                        shared_object   ( self_type const& owner );
    explicit            shared_object   ( pointer const data );
                        shared_object   ( self_type&& ) =   delete;
                        ~shared_object  ( ); 

    size_t              owners          ( ) const;
    bool                unique          ( ) const;
    void                reset           ( pointer const data );

    explicit            operator bool   ( )
                        {
                            return      m_data;
                        }

    pointer const       get             ( );
    const pointer const get             ( ) const;
    // m_data should be const TYPE to const operator * version to be called
    element_type const& operator *      ( ) const;
    element_type&       operator *      ( );

private:
    size_t          decrement       ( );
    void            release         ( );
    void            increment       ( );

private:
    size_t* m_owners;
    pointer m_data;
}; // class shared_object

//-----------------------------------------------------------------------------------
// shared_object outer operators
//-----------------------------------------------------------------------------------
template < typename T >
bool	operator == ( shared_object< T > const& left,	shared_object< T > const& right );

} // namespace memory
} // namespace inex

#	include "memory_shared_object_inline.h"

#endif // #ifndef SHARED_OBJECT_H_INCLUDED