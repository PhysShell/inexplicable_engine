#ifndef SHARED_OBJECT_H_INCLUDED
#   define SHARED_OBJECT_H_INCLUDED

#   define INEX_USE_CRITICAL_SECTIONS_IN_SHARED_OBJECT

namespace inex {
namespace memory {

template < typename T >
class shared_object 
{
public:
    typedef shared_object < T >     self_type;
// to make static member which look for memory leaks ( very simple )
public:
	//-----------------------------------------------------------------------------------
	// initializations
	//-----------------------------------------------------------------------------------
                    shared_object   ( );
                    shared_object   ( self_type const& owner );
    explicit        shared_object   ( T* const data );
                    shared_object   ( self_type&& ) =   delete;
                    ~shared_object  ( ); 

	//-----------------------------------------------------------------------------------
	// operations
	//-----------------------------------------------------------------------------------
    size_t          owners          ( ) const;
    bool            unique          ( ) const;
    void            reset           ( T* const data );

    explicit        operator bool   ( )
                    {
                        return      m_data;
                    }

	//-----------------------------------------------------------------------------------
	// accessors
	//-----------------------------------------------------------------------------------
    T* const        get             ( );
    const T* const  get             ( ) const;
    // m_data should be const TYPE to const operator * version to be called
    T const&        operator *      ( ) const;
    T&              operator *      ( );

private:
	//-----------------------------------------------------------------------------------
	// private
	//-----------------------------------------------------------------------------------
    size_t          decrement       ( );
    void            release         ( );
    void            increment       ( );

private:
    size_t* m_owners;
    T*      m_data;
}; // class shared_object

//-----------------------------------------------------------------------------------
// shared_object outer operators
//-----------------------------------------------------------------------------------
template < typename T >
bool	operator == ( shared_object< T > const& lhs,	shared_object< T > const& rhs );

} // namespace memory
} // namespace inex

#	include "memory_shared_object_inline.h"

#endif // #ifndef SHARED_OBJECT_H_INCLUDED