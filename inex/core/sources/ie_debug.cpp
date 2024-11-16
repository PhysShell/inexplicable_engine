#include "pch.h"
#include "ie_debug.h"
#include "ie_memory.h"
#include <inex/core/engine.h>
#include <inex/threading_functions.h>
#include <inex/core/sources/log_callback.h>
#include <stdlib.h>

//#if INEX_PLATFORM_LINUX
//#       include <X11/Xlib.h>
//#endif // #if INEX_PLAFTOFM_LINUX

//#define s_PRIMARY   "PRIMARY"
//#define s_CLIPBOARD "CLIPBOARD"

// typedef u64 Atom;
// struct Display;
// struct Window;

// Atom targets_atom, text_atom, UTF8, XA_ATOM = 4, XA_STRING = 31;
// static Atom     get_atom                                ( Display *, const pstr );

// static Window * s_window;
// static Display * s_display                       =       NULL;
static inex::core::debug::engine *      s_core_engine	            =	 NULL;
static inex::debug::log_callback		s_log_callback              = NULL;
static inex::threading::atomic32_value_type s_log_disable_counter   = 0;

inex::debug::log_callback	inex::debug::get_log_callback	( )
{
	return									s_log_disable_counter ? nullptr : s_log_callback;
}

inex::debug::log_callback	inex::debug::set_log_callback	( log_callback const & callback )
{
	log_callback const previous_callback	=	s_log_callback;
	s_log_callback							=	callback;
	return									previous_callback;
}

void	inex::debug::disable_log_callback	( )
{
	inex::threading::interlocked_increment					( &s_log_disable_counter );
}

void	inex::debug::enable_log_callback	( )
{
    inex::threading::interlocked_decrement					( &s_log_disable_counter );
}

namespace inex {
namespace core {
namespace debug {

//static void XCopy(Atom selection, unsigned char * text, int size) {
	// XEvent event;
	// Window owner;
	// XSetSelectionOwner (s_display, selection, s_window, 0);
	// if (XGetSelectionOwner (s_display, selection) != s_window) return;
	// while (1) {
        //         XNextEvent (s_display, &event);
	// 	switch (event.type) {
        //                 case SelectionRequest: {
	// 		        if (event.xselectionrequest.selection != selection) break;
	// 		        XSelectionRequestEvent * xsr = &event.xselectionrequest;
	// 		        XSelectionEvent ev = {0};
	// 		        int R = 0;
	// 		        ev.type = SelectionNotify, ev.display = xsr->display, ev.requestor = xsr->requestor,
	// 		        ev.selection = xsr->selection, ev.time = xsr->time, ev.target = xsr->target, ev.property = xsr->property;
	// 		        if (ev.target == targets_atom) R = XChangeProperty (ev.display, ev.requestor, ev.property, XA_ATOM, 32,
	// 				PropModeReplace, (unsigned char*)&UTF8, 1);
	// 		        else if (ev.target == XA_STRING || ev.target == text_atom)
	// 			        R = XChangeProperty(ev.display, ev.requestor, ev.property, XA_STRING, 8, PropModeReplace, text, size);
	// 		        else if (ev.target == UTF8)
	// 			        R = XChangeProperty(ev.display, ev.requestor, ev.property, UTF8, 8, PropModeReplace, text, size);
	// 		        else ev.property = None;
	// 		        if ((R & 2) == 0) XSendEvent (s_display, ev.requestor, 0, 0, (XEvent *)&ev);
	// 		        break;
        //                 }
	// 		case SelectionClear:
	// 		        return;
	// 	}
	// }
//}

void    initialize ( inex::core::debug::engine * engine  )
{
    // this actually needs to be in window_wrapper, not here
//     pstr display_name   = NULL;
//     s_display           = XOpenDisplay( display_name );
//     ASSERT_D            ( s_display, "X11 display '%s' opening", XDisplayName( display_name ) );
}

void    postinitialize ( )
{
    // testing
// targets_atom        = XInternAtom( s_display, "TARGETS", 0);
// text_atom           = XInternAtom(s_display, "TEXT", 0);
// UTF8                = XInternAtom(s_display, "UTF8_STRING", 1);

// if (UTF8 == None)   UTF8 = XA_STRING;
// Atom selection      = XInternAtom(s_display, "CLIPBOARD", 0);

//     XCopy( selection, ( u8 * ) "TEST CLIPBOARD COPY", sizeof ( "TEST CLIPBOARD COPY" ) );
}

void    finalize ( )
{
//     XCloseDisplay       ( s_display );
//     s_display           = NULL;
}

//void    print_stuff0 ( Display* display, Atom atom)
//{
//     Window              win;
//     pstr                window_name;
//     pstr                atom_name;

//     atom_name           = XGetAtomName( display, atom );

//     if ( ( win = XGetSelectionOwner( display, atom ) ) != None )
//     {
//         XFetchName      ( display, win, &window_name) ;
//         LOGGER          ("'%s' (WM_NAME of %ld) owns selection of '%s' atom.", window_name, win, atom_name );
//         XFree           ( window_name) ;
//     }
//     else
//         LOGGER          ("No body owns selection `%s`", atom_name );

//}

// Atom    get_atom ( Display * display, const pstr atom )
// {
//     Atom a;

//     a                   = XInternAtom( display, atom, True );
//     ASSERT_D            ( a == None, "atom '%s' doesn't exist", atom );

//     return              a;
//}

using logging::Msg;

void    set_primary_clipboard_contents ( pcstr text )
{

}

void	aquire_macros ( pcstr 	file,
						u32 	line,
						pcstr 	func,
						pcstr 	expr )
{
	Msg( "File: %s", file );
    Msg( "Line: %d", line );
    Msg( "Method: %s", func );
}

void swap( pstr a, pstr b) {
    int temp = *a;
    *a = *b; 
    *b = temp;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap((str+start), (str+end));
        start++;
        end--;
    }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = 0;
        str[i] = 0;
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = 0; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

void	fatal ( pcstr 	file,
				u32 	line,
				pcstr 	func,
				pcstr 	expr,
				pcstr 	format,
				...
			)
{
    static	threading::critical_section	crit_section	;
			threading::scope_locker		lock			{ crit_section };




        Msg( "\nAssertion failed!\n"
		"File:\t\t\t%s", file );
    Msg( "Line:\t\t\t%d", line );
    Msg( "Method:\t\t\t%s", func );
    Msg( "Expression:\t\t%s", expr );

    if ( format )
	{
        string2048 buf;
        va_list	mark;

        va_start			( mark, format );
        int sz			=
#if INEX_PLATFORM_WINDOWS
        _vsnprintf
#else
        vsnprintf
#endif // #if INEX_PLATFORM_WINDOWS
        ( buf, sizeof( buf ) - 1,format, mark ); buf[ sizeof( buf ) - 1] = 0;
        //strcat			( buf,"\n" );
        va_end				( mark );
        if( sz ) {
			Msg 			( "Description:\t%s", buf );
		}
    } else
	{
        logging::put_string		( "Description:\t<no description>\n" );
    }

	logging::put_string			( "***\nStack Dump:\n***\n" );
	dump_call_stack_trace	    ( );
	memory::dump_memory_contents( );

/*
#if INEX_PLATFORM_LINUX
    Display *   d;
    Window      w;
    XEvent      e;
    int         s;

    d = XOpenDisplay(NULL);
    if ( !d ) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | ButtonPressMask );

    XStoreName      ( d, w, "UNHANDLED EXCEPTION" );
    XMapWindow(d, w);

    for ( ; ; )
    {
        pcstr const string      = "FIX ME";
        XNextEvent  (d, &e);
        if ( e.type == Expose )
        {
                // XFillRectangle (d, w, DefaultGC(d, s), 20, 20, 10, 10);
                XDrawString    (d , w, DefaultGC( d, s ), 10, 50, string, sizeof( string ) - 1);
        }

        if ( e.type == ButtonPressMask )
                break;
    }

    //XFreeGC         ( d,  gc );
    XDestroyWindow  ( d, w );
    XCloseDisplay   ( d );
#endif // #if INEX_PLATFORM_LINUX
*/

// 	if ( s_display )
//     {
//         finalize            ( );
//         exit                ( 2 );
//     }

	exit            		( 1 );
}

} // namespace debug
} // namespace core
} // namespace inex
