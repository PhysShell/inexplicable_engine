#ifndef MACRO_DECLARATIONS_H_INCLUDED
#	define MACRO_DECLARATIONS_H_INCLUDED

/*
* PATH_MAX is ambigiously defined in some implementations.
* So better not use it. And by using SetCurrentDirectory for
* each directory we can avoid 260 char limitation in Win.
* Just to be aware of max path, define it.
*/
#	define INEX_MAX_PATH	260

#	define INEX_DEBUG_WAIT       do { char ch; std::cin >> ch; } while( 0 )
#	define INEX_SCST( a, b )     static_cast< a >( b )
#	define INEX_CCALL				__cdecl
#	define IC                  inline
#	define	ie_pure_interface	__interface

#	define INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR( name ) virtual ~name( ) =0 { } 

// mark as deprecated providing specific warning
#	define INEX_DEPRECATED(msg)	[ [ deprecated( #msg ) ] ]
// mark as deprecated providing built-in warning
#	define INEX_DEPRECATED_D		[ [ deprecated ] ]

#endif // #ifndef MACRO_DECLARATIONS_H_INCLUDED
