#ifndef HW_WRAPPER_BASE_GL4_WIN_WINAPI_H_INCLUDED
#	define HW_WRAPPER_BASE_GL4_WIN_WINAPI_H_INCLUDED

#	define GLX_GLXEXT_LEGACY
#	include <windows.h>
#	include <inex/3rd_patry/include/GL/gl.h>
#	include <inex/3rd_patry/include/GL/glext.h>
#	include <inex/3rd_patry/include/GL/wglext.h>
//#	include <inex/3rd_patry/include/GLFW/glfw3.h>

#	include <inex/render/gl4/gl4_extensions.h>
#	include <inex/render/core/quasi_singleton.h>
#	define R_ASSERT_WINDOWS( condition, message ) if ( ! ( condition ) ) do { showMessage( message ); ASSERT_S( ( condition ) ); } while ( 0 )
namespace inex {
namespace render {

struct hw_wrapper_context
{
public:
	hw_wrapper_context ( )
	{
		config.width	= 1024;
		config.height	= 720;
		config.posX		= CW_USEDEFAULT;
		config.posY		= 0;
		config.windowed = true;
		m_style			= WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	}
	
	~hw_wrapper_context( ) { ; }
	
	inline void create( u32 const x, u32 const y )
	{

	}
	
	void	showMessage(LPCSTR message) const	{ LOGGER( message ); MessageBox(0, message, "inexplicable_engine", MB_ICONERROR); }
	s32		create ( u32 const x, u32 const y, HINSTANCE hInstance, s32 nCmdShow, pcstr const window_title)
	{
		m_window_class		= MAKEINTATOM( registerClass( hInstance ) );
		R_ASSERT_WINDOWS	( m_window_class != 0, "registerClass() failed." );

		// create temporary window

		HWND fakeWND		= CreateWindow ( m_window_class, "", m_style, 0, 0, 1, 1, NULL, NULL, hInstance, NULL );

		HDC fakeDC = GetDC(fakeWND);	// Device Context

		PIXELFORMATDESCRIPTOR fakePFD;
		ZeroMemory				( & fakePFD, sizeof( fakePFD ) );
		fakePFD.nSize			= sizeof( fakePFD );
		fakePFD.nVersion		= 1;
		fakePFD.dwFlags			= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		fakePFD.iPixelType		= PFD_TYPE_RGBA;
		fakePFD.cColorBits		= 32;
		fakePFD.cAlphaBits		= 8;
		fakePFD.cDepthBits		= 24;

		s32 const fakePFDID		= ChoosePixelFormat(fakeDC, &fakePFD);
		R_ASSERT_WINDOWS		( fakePFDID != 0, "ChoosePixelFormat() failed.");

		R_ASSERT_WINDOWS		( SetPixelFormat( fakeDC, fakePFDID, & fakePFD ), "SetPixelFormat() failed.");

		HGLRC fakeRC			= wglCreateContext(fakeDC);	// Rendering Contex
		R_ASSERT_WINDOWS		( fakeRC != 0, "wglCreateContext() failed.");

		//context_manager::reference( ).make_current			( m_context );

		R_ASSERT_WINDOWS		( wglMakeCurrent(fakeDC, fakeRC ), "wglMakeCurrent() failed." );

		// get pointers to functions (or init opengl loader here)

		PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
		wglChoosePixelFormatARB = reinterpret_cast< PFNWGLCHOOSEPIXELFORMATARBPROC >( wglGetProcAddress( "wglChoosePixelFormatARB" ) );
		R_ASSERT_WINDOWS		( wglChoosePixelFormatARB != nullptr, "wglGetProcAddress() failed." );
		
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
		wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
		R_ASSERT_WINDOWS		( wglCreateContextAttribsARB != nullptr, "wglGetProcAddress() failed." );

		if ( config.windowed )
		{
			adjustSize();
			center();
		}

		// create a new window and context

		m_hwnd					=
			CreateWindow (
			m_window_class,					// class name
			window_title,					// window name
			m_style,						// styles
			config.posX,					// posx. If x is set to CW_USEDEFAULT y is ignored
			config.posY,					// posy. If x is set to CW_USEDEFAULT y is ignored
			config.width,					// width
			config.height,					// height
			NULL,							// parent window
			NULL,							// menu
			hInstance,						// instance
			NULL							// param
		);				

		m_device_context		= GetDC( m_hwnd );

		const s32 pixelAttribs	[ ] =
		{
			WGL_DRAW_TO_WINDOW_ARB,			GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB,			GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB,			GL_TRUE,
			WGL_PIXEL_TYPE_ARB,				WGL_TYPE_RGBA_ARB,
			WGL_ACCELERATION_ARB,			WGL_FULL_ACCELERATION_ARB,
			WGL_COLOR_BITS_ARB,				32,
			WGL_ALPHA_BITS_ARB,				8,
			WGL_DEPTH_BITS_ARB,				24,
			WGL_STENCIL_BITS_ARB,			8,
			WGL_SAMPLE_BUFFERS_ARB,			GL_TRUE,
			WGL_SAMPLES_ARB,				4,
			0
		};

		s32 pixelFormatID;
		u32 numFormats;
		bool const status		= wglChoosePixelFormatARB(m_device_context, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats);
		R_ASSERT_WINDOWS		( status, "wglChoosePixelFormatARB() failed." );
		R_ASSERT_WINDOWS		( numFormats != 0, "wglChoosePixelFormatARB() failed." );

		PIXELFORMATDESCRIPTOR PFD;
		DescribePixelFormat		(m_device_context, pixelFormatID, sizeof(PFD), &PFD);
		SetPixelFormat			(m_device_context, pixelFormatID, &PFD);

		const u32 minimum_supported_version			= 4;
		const u32 minimum_supported_subversion		= 6;
		const s32 contextAttribs [ ] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB,	minimum_supported_version,
			WGL_CONTEXT_MINOR_VERSION_ARB,	minimum_supported_subversion,
			WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	//		WGL_CONTEXT_FLAGS_ARB,			WGL_CONTEXT_DEBUG_BIT_ARB,
			0
		};

		m_rendering_context		= wglCreateContextAttribsARB(m_device_context, 0, contextAttribs);
		if ( ! m_rendering_context )
		{
			string128 buffer;
			snprintf				( buffer, 128, "wglCreateContextAttribsARB() failed. check if minimal opengl version is supported by videoboard: '%d.%d'.", minimum_supported_version, minimum_supported_subversion );
			R_ASSERT_WINDOWS		( 0, buffer );
		}

		// delete temporary context and window

		wglMakeCurrent			( NULL, NULL );
		wglDeleteContext		( fakeRC );
		ReleaseDC				( fakeWND, fakeDC );
		DestroyWindow			( fakeWND );
		R_ASSERT_WINDOWS		( wglMakeCurrent( m_device_context, m_rendering_context ), "wglMakeCurrent() failed." );

		// init opengl loader here (extra safe version)

		render::initialize		( );

		LOGGER	(
			"* [render][info]\t: %s\n* [render][info]\t: OpenGL version supported %s\n",
			glGetString( GL_RENDERER ),
			glGetString( GL_VERSION )
		);

		//glEnable				( GL_DEPTH_TEST ); // enable depth-testing
		//glDepthFunc				( GL_LESS );

		SetWindowText			( m_hwnd, window_title );
		ShowWindow				( m_hwnd, ! nCmdShow ? SW_SHOWDEFAULT : nCmdShow );

		return 0;
	}
	
	ATOM registerClass(HINSTANCE hInstance)
	{
		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(wcex);
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex.lpfnWndProc = WindowProcedure;
		wcex.hInstance = hInstance;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.lpszClassName = "Core";

		return RegisterClassEx(&wcex);
	}
	
	void adjustSize()
	{
		RECT rect = { 0, 0, config.width, config.height };
		AdjustWindowRect(&rect, m_style, false);
		config.width = rect.right - rect.left;
		config.height = rect.bottom - rect.top;
	}
	
	void center()
	{
		RECT primaryDisplaySize;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &primaryDisplaySize, 0);	// system taskbar and application desktop toolbars not included
		config.posX = (primaryDisplaySize.right - config.width) / 2;
		config.posY = (primaryDisplaySize.bottom - config.height) / 2;
	}
	
	void render()
	{
		glClearColor(0.529f, 0.586f, 0.949f, 1.0f);	// rgb(33,150,243)
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void swap_buffers() { SwapBuffers( m_device_context ); }
	void destroy()
	{
		wglMakeCurrent(NULL, NULL);
		if (m_rendering_context) {
			wglDeleteContext(m_rendering_context);
		}
		if (m_device_context) {
			ReleaseDC(m_hwnd, m_device_context);
		}
		if (m_hwnd) {
			DestroyWindow(m_hwnd);
		}
	}
	
	static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message) {
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) {
				PostQuitMessage(0);
			}
			break;
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;		// message handled
	}

	HDC		winapi_device		( ) const	{ return m_device_context; }
	HGLRC	winapi_context		( ) const	{ return m_rendering_context; }
	
public:
	LPTSTR	m_window_class;			// Window Class
	HGLRC	m_rendering_context;	// OpenGL Rendering Context
	HDC		m_device_context;		// Device Context
	HWND	m_hwnd;					// Window
	DWORD	m_style;

	struct Config {
		int width;
		int	height;
		int posX;
		int posY;
		bool windowed;
	} config;

}; // struct hw_wrapper_context

class hw_wrapper_base //: boost::noncopyable
{
public:
	hw_wrapper_base	( );

	// remove inline
	void create	(u32 const x, u32 const y, pcstr const window_title, HINSTANCE handle_instance, int command_line_show );
	
	void destroy ( )
	{
		VERIFY					( m_context != 0 );
		m_context->destroy		( );
		//glXDestroyContext		( display, context );
		//XDestroyWindow			( display, window);
		//XCloseDisplay			( display );
		memory::ie_delete		( m_context );
	}

	HGLRC		render_context		( ) const	{ return m_context->winapi_context( ); }
	HDC			render_device		( ) const	{ return m_context->winapi_device( ); }
	hw_wrapper_context *	context	( ) const	{ return m_context; }

protected:
	hw_wrapper_context *	m_context;	//	pDevice	//	render device
	
private:
	inline void set_window_title ( pcstr const value ) { VERIFY( value ); }
}; // class hw_wrapper_base_gl4

inline hw_wrapper_base::hw_wrapper_base ( )
{
	/*memory::zero(&m_dev_pparams, sizeof(m_dev_pparams));*/
	m_context			= memory::ie_new<hw_wrapper_context>();
	//m_device			= 0;
}

class context_manager : public quasi_singleton< context_manager >
{
public:
	inline void make_current 	( hw_wrapper_context * context ) 						{ VERIFY( context ); wglMakeCurrent( context->m_device_context, context->m_rendering_context ); }
	inline void create			( u32 const x, u32 const y )							{ VERIFY( x > 0 ); VERIFY ( y > 0 ); }
	inline void destroy			( hw_wrapper_context * context )						{ VERIFY( context ); context->destroy(); }
	
}; // class context_manager

} // namespace render 
} // namespace inex 

//void inex::render::make_context_current
#	undef R_ASSERT_WINDOWS
#endif // #ifndef HW_WRAPPER_BASE_GL4_WIN_WINAPI_H_INCLUDED