#ifndef STL_EXTENSIONS_H_INCLUDED
#	define STL_EXTENSIONS_H_INCLUDED

#include <vector>
#include <inex/core/sources/ie_memory.h>
template <typename T>
class ie_vector :
	public std::vector< T, std::allocator< T > >
{
public:
	typedef 	T				type;
	typedef 	T&				reference;
	typedef 	T const&		const_reference;
	typedef 	std::vector< T >inherited;
public:
	// use the constructors from vector (under the Vec name);
	using std::vector< T, std::allocator< T > >::vector;
	reference			operator [ ]	( int i );		// range check
	const_reference		operator [ ]	( int i ) const;	// range check const objects
}; // class ie_vector

//template	<>
//class	ie_vector<char>	: public std::vector<char, std::allocator<char>> {
//private:
//	//typedef			char		T;
//	typedef		size_t		    size_type;
//	typedef 	std::vector<char, std::allocator<char>> inherited;
//public:
//	using		inherited::vector;
//
//	IC			char&			operator[]	(int i)
//                                {
//                                    return std::vector<char>::at(i);
//                                }
//
//	IC			const char&		operator[]	(int i)	const
//                                {
//                                    return std::vector<char>::at(i);
//                                }
//};


template <typename T>
class ie_allocator
{
public:
	/*
	typedef	T					value_type;
	typedef	value_type*			pointer;
	typedef	const value_type*	const_pointer;
	typedef	value_type&			reference;
	typedef	const value_type&	const_reference;
	typedef	std::size_t			size_type;
	typedef	std::ptrdiff_t		difference_type;
	*/

	typedef	T			value_type;
	typedef	T*			pointer;
	typedef	const T*	const_pointer;
	typedef	T&			reference;
	typedef	T const&	const_reference;
	typedef	size_t		size_type;
	typedef	std::ptrdiff_t	difference_type;

public:
	template <class U>
	struct rebind
	{
		typedef ie_allocator< U > other;
	}; // struct rebind

public:
	// allocate also initializes, and deallocate also destroys
	// to make it simpler. but these have to be decoupled when working on container

	// also, optional parameters in alloc and dealloc are for high-performace allocators
	// that means, "not for this one" :-)

	// If you have an allocator class A1, the corresponding allocator class for a different value
	// type is
	//typename A1::template rebind<X2>::other

	 pointer			address				( reference x ) const 				{ return &x; 				}
	 const_pointer		address				( const_reference x ) const			{ return &x; 				};
											// for some reason, nullptr doesn't fit here, so use an ought
	 pointer			allocate			( size_type n, const_pointer = 0 )	{ return inex::memory::ie_allocate< value_type >( n ); }
	 void				deallocate			( pointer p, size_type = 0 ) 		{ std::free( p ); 			}
	 void				construct			( pointer p, value_type const& x )	{ new ( p ) value_type( x );}
	 void				finalize				( pointer p )						{ p->~value_type( ); 		}
	//	 size_type			max_size		() const { return (~0u); }

	 size_type			max_size			( ) const 							{ return (static_cast<size_type>(0) - static_cast<size_type>(1)) / sizeof(value_type); }

						ie_allocator		( ) 								{	 }
						ie_allocator		( ie_allocator const& )				{	 }
						~ie_allocator		( ) 								{ 	 }

	template< class U >	ie_allocator		( ie_allocator< U > const& ) 		{ 	 }

private:
	// should not be called
	void 				operator =			( ie_allocator const& );
}; // class ie_allocator

template<>
class ie_allocator< void >
{
	typedef void        value_type;
	typedef void*       pointer;
	typedef const void* const_pointer;

	template <class U>
	struct rebind
	{
	  typedef ie_allocator< U > other;
	}; // struct rebind
}; // class ie_allocator< void >
// return that all specializations of this allocator are interchangeable
template < class T1, class T2 >
inline
bool	operator == ( 	ie_allocator< T1 > const&,
						ie_allocator< T2 > const& ) noexcept
{
	return 1;
}


template < class T1, class T2 >
inline
bool	operator != ( 	ie_allocator< T1 >const&,
						ie_allocator< T2 > const& ) noexcept
{
	return 0;
}


#define ie_list std::list
#define ie_deque std::deque
#define ie_stack std::stack
#define ie_set std::set
#define ie_multiset std::multiset
#define ie_map std::map
#define ie_hash_map std::hash_map
#define ie_multimap std::multimap
#define ie_string std::string

// stl extensions
#define DEFINE_SET_PRED( T, N, P, I )	typedef     ie_set< T, P > N;\
										typedef     N::iterator I

#define DEFINE_SET( T, N, I )	        typedef     ie_set< T > N;\
										typedef     N::iterator I

#define DEF_VECTOR( N, T )			    typedef 	ie_vector< T > N; \
										typedef 	N::iterator N##_it

#define DEFINE_VECTOR( T, N, I )	    typedef 	ie_vector< T >N;\
										typedef 	N::iterator I

//// string(char)
//typedef		std::basic_string<char, std::char_traits<char>, ie_allocator<char> >	ie_string;


#include "stl_extensions_inline.h"

#endif // #ifndef STL_EXTENSIONS_H_INCLUDED
