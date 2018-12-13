#ifndef MACRO_DECLARATIONS_H_INCLUDED
#	define MACRO_DECLARATIONS_H_INCLUDED


#define IE_DEBUG_WAIT       do { char ch; std::cin >> ch; } while( 0 )
#define IE_SCST( a, b )     static_cast< a >( b )
#define	IE_CCALL	        __cdecl
#define IC                  inline
#define	ie_pure_interface	__interface

#define IE_DECLARE_PURE_VIRTUAL_DESTRUCTOR( name ) virtual ~name( ) { } = 0;

// mark as deprecated providing specific warning
#define IE_DEPRECATED(msg)	[ [ deprecated( #msg ) ] ]
// mark as deprecated providing built-in warning
#define IE_DEPRECATED_D		[ [ deprecated ] ]

#endif // #ifndef MACRO_DECLARATIONS_H_INCLUDED
