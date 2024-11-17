#ifndef HW_WRAPPER_BASE_GL4_LINUX_XLIB_H_INCLUDED
#	define HW_WRAPPER_BASE_GL4_LINUX_XLIB_H_INCLUDED

#	include <X11/X.h>
#	include <X11/Xlib.h>
#	include <GL/gl.h>
#	include <GL/glext.h>
#	include <GL/glx.h>


#	include <inex/render/gl4/gl4_extensions.h>
#	include <inex/render/core/quasi_singleton.h>

namespace inex {
namespace render {

class hw_wrapper_context;

class context_manager : public quasi_singleton< context_manager >
{
public:
	inline void make_current 	( hw_wrapper_context * context );
	inline void create			( u32 const x, u32 const y )
	{
		NOT_IMPLEMENTED	( );
	}
	
}; // class context_manager

struct hw_wrapper_context
{
public:
	hw_wrapper_context ( ) { ; }
	~hw_wrapper_context( ) { ; }
	
	inline void create( u32 const x, u32 const y )
	{
		//VERIFY 				( m_context == 0 );
		//LOGGER 				( "- [hw-wrapper][info]\t: requesting '%d' bytes to store context... " );
		//m_context		= 	inex::memory::ie_new< gl_context >( );
		//LOGGER 				( "\t\t\t\t... successfully allocated at '%p'", m_context );
		display 		= 	XOpenDisplay( NULL );
		ASSERT_D			( display, "Xlib error: Cannot connect to X server" );

		root			=	DefaultRootWindow( display );
		visual_info		= 	glXChooseVisual( display, 0, attributes );
		ASSERT_D			( visual_info, "Xlib error: No appropriate visual found" );
		LOGGER				( "- [hw-wrapper][info]\t: glx visual '%p' selected", ( pvoid ) visual_info->visualid );

		color_map		=
			XCreateColormap (
				display,
				root,
				visual_info->visual,
				AllocNone
			);

		window_attributes.colormap	= color_map;
		window_attributes.event_mask = ExposureMask | KeyPressMask;

		window 			=
			XCreateWindow (
				display,
				root,
				0,
				0,
				600,
				600,
				0,
				visual_info->depth,
				InputOutput,
				visual_info->visual,
				CWColormap | CWEventMask,
				&window_attributes
			 );

		XSelectInput		( display, window, KeyPressMask | KeyReleaseMask );
		XMapWindow			( display, window );
		//set_window_title	( "demo build" );
		
		//XStoreName		( display, window, window_name );
		context		= glXCreateContext( display, visual_info, NULL, GL_TRUE );
		
		if(context == NULL)
			ASSERT_S( !"Failed to open GLFW window.\n");
	}
	
public: // temporary
	Display *				display;
	Window                  root;
	GLint                   attributes[ 5 ] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	XVisualInfo *			visual_info;
	Colormap                color_map;
	XSetWindowAttributes    window_attributes;
	Window                  window;
	GLXContext              context;
	XWindowAttributes       x_window_attributes;
	XEvent                  x_event;
}; // struct hw_wrapper_context

class hw_wrapper_base //: boost::noncopyable
{
public:
	hw_wrapper_base	( );

	// remove inline
	void create	( u32 const x, u32 const y, pcstr const window_title )
	{
		m_context->create									( x, y );
		//context_manager::reference( ).make_context_current	( m_context );
		//VERIFY												( initialize_extensions( ) );
	}
	
	void destroy ( )
	{
		VERIFY					( m_context != 0 );
		//glXMakeCurrent			( display, None, NULL );
		//glXDestroyContext		( display, context );
		//XDestroyWindow			( display, window);
		//XCloseDisplay			( display );
		//inex::memory::ie_delete	( m_context );
	}

	pvoid					render_device ( ) const		{ NOT_IMPLEMENTED ( ); return 0; }
	hw_wrapper_context *	context	( ) const			{ NOT_IMPLEMENTED ( ); return m_context; }

protected:

	//HINSTANCE 			m_hd3d;		//	hD3D
	//IDirect3D9* 			m_d3d;		//	pD3D	//	D3D
	hw_wrapper_context *	m_context;	//	pDevice	//	render device
	//pvoid 					m_device;

	//ID3DRenderTargetView*	m_base_rt;	//	pBaseRT
	//ID3DDepthStencilView*	m_base_zb;	//	pBaseZB

	//UINT					m_dev_adapter;	//	DevAdapter
	//D3DDEVTYPE			m_dev_type;		//	DevT
	//D3DPRESENT_PARAMETERS	m_dev_pparams;	//	DevPP
	
private:
	//inline void set_window_title ( pcstr const value ) { VERIFY( value ); XStoreName( display, window, value ); };
}; // class hw_wrapper_base

inline hw_wrapper_base::hw_wrapper_base ( ) /*:
	m_hd3d(0),
	m_d3d(0),
	m_device(0),
	m_base_rt(0),
	m_base_zb(0),
	m_dev_adapter(0),
	m_dev_type(D3DDEVTYPE_FORCE_DWORD)*/
{
	/*memory::zero(&m_dev_pparams, sizeof(m_dev_pparams));*/
}

inline void context_manager::make_current ( hw_wrapper_context * context )
{
	VERIFY			( context );
	glXMakeCurrent	( context->display, context->window, context->context );
}

} // namespace render 
} // namespace inex 

//void inex::render::make_context_current


#endif // #ifndef HW_WRAPPER_BASE_GL4_LINUX_XLIB_H_INCLUDED