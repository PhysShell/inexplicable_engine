#ifndef HW_WRAPPER_BASE_GL4_WIN_WINAPI_H_INCLUDED
#	define HW_WRAPPER_BASE_GL4_WIN_WINAPI_H_INCLUDED

#	define GLX_GLXEXT_LEGACY
#	include <windows.h>
#	include <inex/3rd_patry/include/GL/gl.h>
#	include <inex/3rd_patry/include/GL/glext.h>
#	include <inex/3rd_patry/include/GL/wglext.h>
//#	include <inex/3rd_patry/include/GLFW/glfw3.h>

namespace inex {
namespace render {

struct hw_wrapper_context
{
public:
	hw_wrapper_context ( )
	{
		config.width = 1024;
		config.height = 720;
		config.posX = CW_USEDEFAULT;
		config.posY = 0;
		config.windowed = true;
		style = WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	}
	
	~hw_wrapper_context( ) { ; }
	
	inline void create( u32 const x, u32 const y )
	{

	}
	
	
	void showMessage(LPCSTR message) { MessageBox(0, message, "Window::create", MB_ICONERROR); }
	int create(HINSTANCE hInstance, int nCmdShow)
	{
		windowClass = MAKEINTATOM(registerClass(hInstance));
		if (windowClass == 0) {
			showMessage("registerClass() failed.");
			return 1;
		}

		// create temporary window

		HWND fakeWND = CreateWindow(
			windowClass, "Fake Window",
			style,
			0, 0,						// position x, y
			1, 1,						// width, height
			NULL, NULL,					// parent window, menu
			hInstance, NULL);			// instance, param

		HDC fakeDC = GetDC(fakeWND);	// Device Context

		PIXELFORMATDESCRIPTOR fakePFD;
		ZeroMemory(&fakePFD, sizeof(fakePFD));
		fakePFD.nSize = sizeof(fakePFD);
		fakePFD.nVersion = 1;
		fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		fakePFD.iPixelType = PFD_TYPE_RGBA;
		fakePFD.cColorBits = 32;
		fakePFD.cAlphaBits = 8;
		fakePFD.cDepthBits = 24;

		const int fakePFDID = ChoosePixelFormat(fakeDC, &fakePFD);
		if (fakePFDID == 0) {
			showMessage("ChoosePixelFormat() failed.");
			return 1;
		}

		if (SetPixelFormat(fakeDC, fakePFDID, &fakePFD) == false) {
			showMessage("SetPixelFormat() failed.");
			return 1;
		}

		HGLRC fakeRC = wglCreateContext(fakeDC);	// Rendering Contex

		if (fakeRC == 0) {
			showMessage("wglCreateContext() failed.");
			return 1;
		}

		if (wglMakeCurrent(fakeDC, fakeRC) == false) {
			showMessage("wglMakeCurrent() failed.");
			return 1;
		}

		// get pointers to functions (or init opengl loader here)

		PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
		wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
		if (wglChoosePixelFormatARB == nullptr) {
			showMessage("wglGetProcAddress() failed.");
			return 1;
		}

		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
		wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
		if (wglCreateContextAttribsARB == nullptr) {
			showMessage("wglGetProcAddress() failed.");
			return 1;
		}

		if (config.windowed == true) {
			adjustSize();
			center();
		}

		// create a new window and context
									
		WND = CreateWindow(
			windowClass, "OpenGL Window",	// class name, window name
			style,							// styles
			config.posX, config.posY,		// posx, posy. If x is set to CW_USEDEFAULT y is ignored
			config.width, config.height,	// width, height
			NULL, NULL,						// parent window, menu
			hInstance, NULL);				// instance, param

		DC = GetDC(WND);

		const int pixelAttribs[] = {
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_ALPHA_BITS_ARB, 8,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
			WGL_SAMPLES_ARB, 4,
			0
		};

		int pixelFormatID; UINT numFormats;
		const bool status = wglChoosePixelFormatARB(DC, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats);

		if (status == false || numFormats == 0) {
			showMessage("wglChoosePixelFormatARB() failed.");
			return 1;
		}

		PIXELFORMATDESCRIPTOR PFD;
		DescribePixelFormat(DC, pixelFormatID, sizeof(PFD), &PFD);
		SetPixelFormat(DC, pixelFormatID, &PFD);

		const int major_min = 4, minor_min = 0;
		const int contextAttribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
			WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	//		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
			0
		};

		RC = wglCreateContextAttribsARB(DC, 0, contextAttribs);
		if (RC == NULL) {
			showMessage("wglCreateContextAttribsARB() failed.");
			return 1;
		}

		// delete temporary context and window

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(fakeRC);
		ReleaseDC(fakeWND, fakeDC);
		DestroyWindow(fakeWND);
		if (!wglMakeCurrent(DC, RC)) {
			showMessage("wglMakeCurrent() failed.");
			return 1;
		}

		// init opengl loader here (extra safe version)

		SetWindowText(WND, reinterpret_cast<LPCSTR>(glGetString(GL_VERSION)));
		ShowWindow(WND, nCmdShow);
		
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
		AdjustWindowRect(&rect, style, false);
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
		glClearColor(0.129f, 0.586f, 0.949f, 1.0f);	// rgb(33,150,243)
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void swapBuffers() { SwapBuffers( DC ); }
	void destroy()
	{
		wglMakeCurrent(NULL, NULL);
		if (RC) {
			wglDeleteContext(RC);
		}
		if (DC) {
			ReleaseDC(WND, DC);
		}
		if (WND) {
			DestroyWindow(WND);
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
	
public:
	LPTSTR windowClass;	// Window Class
	HGLRC RC;			// Rendering Context
	HDC	DC;				// Device Context
	HWND WND;			// Window
	DWORD style;

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
	void create	( u32 const x, u32 const y, pcstr const window_title )
	{
		if (window.create(hInstance, nCmdShow) != 0) {
			PostQuitMessage(1);
		}

		MSG msg;
		bool active = true;
		while (active) {
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					active = false;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			window.render();
			window.swapBuffers();
		}
		
		window.destroy();
		
		m_context.create									( x, y );
		context_manager::reference( ).make_context_current	( m_context );
		VERIFY												( initialize_extensions( ) );
	}
	
	void destroy ( )
	{
		VERIFY					( m_context != 0 )
		glXMakeCurrent			( display, None, NULL );
		glXDestroyContext		( display, context );
		XDestroyWindow			( display, window);
		XCloseDisplay			( display );
		inex::memory::ie_delete	( m_context );
	}

protected:
	hw_wrapper_context *	m_context;	//	pDevice	//	render device
	pvoid 					m_device;
	
private:
	inline void set_window_title ( pcstr const value ) { VERIFY( value ); XStoreName( display, window, value );
}; // class hw_wrapper_base_gl4

inline hw_wrapper_base::hw_wrapper_base ( )
{
	/*memory::zero(&m_dev_pparams, sizeof(m_dev_pparams));*/
}

class context_manager : public quasi_singleton< context_manager >
{
public:
	inline void make_current 	( hw_wrapper_context * context ) 						{ VERIFY( context ); glXMakeCurrent	( display, window, context ); }
	inline void create			( u32 const x, u32 const y );
	
}; // class context_manager

} // namespace render 
} // namespace inex 

void inex::render::make_context_current

#endif // #ifndef HW_WRAPPER_BASE_OGL3_H_INCLUDED