#ifndef SHARED_OBJECT_H_INCLUDED
#   define SHARED_OBJECT_H_INCLUDED

#   define IE_USE_CRITICAL_SECTIONS_INSHARED_OBJECT_TEMPLATE

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


#define	TEMPLATE_SPECIALIZATION	template < typename T >
#define	SHARED_OBJECT_TEMPLATE shared_object< T >

TEMPLATE_SPECIALIZATION
inline
SHARED_OBJECT_TEMPLATE::shared_object ( ) :
    m_owners    ( nullptr ),
    m_data      ( nullptr )
{	/* printf (	"+\tDEFAULT ctor:\t %p\n"
				"\tm_data:\t\t %p\n\tm_owners:\t\t%d\n", 
                this,
                m_data,
                m_owners ? *m_owners : 0 ); */
}

TEMPLATE_SPECIALIZATION
inline
SHARED_OBJECT_TEMPLATE::shared_object ( T* const data ) :
    m_owners    ( new size_t ( 1 ) ),
    m_data      ( data )
{
/* 	printf (	"+\tDATA ctor:\t %p\n"
				"\tm_data:\t\t %p\n\tm_owners:\t\t%d\n", this, m_data, *m_owners );
 */
}

TEMPLATE_SPECIALIZATION
inline
SHARED_OBJECT_TEMPLATE::shared_object ( SHARED_OBJECT_TEMPLATE const& owner ) :
    m_data      ( owner.m_data ),
    m_owners    ( owner.m_owners )
{
/*     if ( !owner.m_owners )
    {
        printf          ( "no OWNERS COPY ctor has\n" );
        getchar         ( );
    } */

    increment         ( );

/*  	printf (	"+\tCOPY ctor:\t %p\n"
				"\tm_data:\t\t %p\n\tm_owners:\t\t%d\n", this, m_data, *m_owners );   
 */}

TEMPLATE_SPECIALIZATION
inline
SHARED_OBJECT_TEMPLATE::~shared_object ( )
{
    if ( !m_data )
    {
        /* printf  ( "theres nothing to delete!\n" ); */
        return ;
    }

    if ( decrement( ) < 1 )
    {
/*         printf (	"-\tDTOR FREE:\t %p\n"
            "\tm_data:\t\t %p\n\tm_owners:\t\t%d\n", this, m_data, *m_owners );   
 */        release ( );
    }
    else
    {
 /*        printf (	"-\tDTOR REF_DEC:\t %p\n"
            "\tm_data:\t\t %p\n\tm_owners:\t\t%d\n", this, m_data, *m_owners );   
  */   }
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
        /* std::cout << "NULLPTR PASSED\n"; */
        release ( );
        return              ;
    }

    if ( !m_owners )
    {
        /* printf  ( "no owners, allocate.\n" ); */
        m_owners            = new size_t ( 1 );
        m_data              = data;
    }
    else if ( unique( ) )
    {
        /* printf  ( "unique owner, reset.\n" ); */
        delete              m_data;
        m_data              = data;
    }
    else
    {
        /* printf  ( "many owner, decrement and reset.\n" ); */
        decrement           ( );
        m_owners            = new size_t ( 1 );
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
    /* printf ( "releasing DATA: %p\n", m_data ); */
    delete              m_data;
    delete              m_owners;
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
T* const    SHARED_OBJECT_TEMPLATE::get ( )
{
    return              m_data;
}

TEMPLATE_SPECIALIZATION
inline
const T* const  SHARED_OBJECT_TEMPLATE::get ( ) const
{
    return              m_data;
}

#undef	TEMPLATE_SPECIALIZATION
#undef	SHARED_OBJECT_TEMPLATE

#endif // #ifndef SHARED_OBJECT_H_INCLUDED