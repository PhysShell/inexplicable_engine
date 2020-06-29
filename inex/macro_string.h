#ifndef MACRO_STRING_H_INCLUDED
#	define MACRO_STRING_H_INCLUDED

#define		_QUOTE( x )		#x
#define		QUOTE( x )		_QUOTE( x )
#define		__FILE__LINE__	"***" __FILE__ "*** [" QUOTE( __LINE__ ) "]: "
#define		NOTE( x )		message( x )
#define		TODO( x )		message( __FILE__LINE__"\n"       \
							" -------------------------------------------------\n" \
							"|  TODO :   " #x "\n" \
							" -------------------------------------------------\n" )
#define		todo( x )		message( __FILE__LINE__" TODO :   " #x "\n" )

#endif // #ifndef MACRO_STRING_H_INCLUDED
