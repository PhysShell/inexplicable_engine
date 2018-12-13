#include "stdafx.h"

#include "ie_debug.h"

namespace inex {
namespace core {
namespace debug {

using inex::core::log::Msg;

void	aquire_macros ( pcstr 	file,
						u32 	line,
						pcstr 	func,
						pcstr 	expr )
{
	Msg( "File: %s", file );
    Msg( "Line: %d", line );
    Msg( "Method: %s", func );
}

pcstr	error2string ( u32 code )
{
	pcstr result					= 0;
	static string1024 desc_storage;

	//if(0==result)
	//{
#if IE_PLATFORM_WINDOWS
		FormatMessage( 	FORMAT_MESSAGE_FROM_SYSTEM,
						0,
						code,
						0,
						desc_storage,
						sizeof( desc_storage ) - 1,
						0
					);
		result						=	desc_storage;
	//}
#endif // #if IE_PLATFORM_WINDOWS
	return				 				result;

}

void	fatal ( pcstr 	file,
				u32 	line,
				pcstr 	func,
				pcstr 	expr,
				pcstr 	format,
				...
			)
{
    static	critical_section	crit_section	;
			scope_locker		lock			{ crit_section };

    Msg( "\nAssertion failed!\n"
		"File:\t\t\t%s", file );
    Msg( "Line:\t\t\t%d", line );
    Msg( "Method:\t\t\t%s", func );
    Msg( "Expression:\t\t%s", expr );

    if ( format )
	{
        va_list	mark;
        string2048 buf;
        va_start			( mark, format );
        int sz			=
#if IE_PLATFORM_WINDOWS
        _vsnprintf
#else
        vsnprintf
#endif // #if IE_PLATFORM_WINDOWS
        ( buf, sizeof( buf ) - 1,format, mark ); buf[ sizeof( buf ) - 1] = 0;
        //strcat			( buf,"\n" );
        va_end				( mark );
        if(sz)
		{
			Msg ( "Description:\t%s", buf );
		}
    }
	else
	{
        log::put_string("Description:\t<no description>\n");
    }

	exit            		( 1 );
}

} // namespace debug
} // names core
} // namespace inex
