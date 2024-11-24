#ifndef HW_WRAPPER_BASE_GL4_LINUX_XLIB_H_INCLUDED
#	define HW_WRAPPER_BASE_GL4_LINUX_XLIB_H_INCLUDED

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <EGL/egl.h>
#include <EGL/eglplatform.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h> 
#include <iostream>
#include <vector>
#include <cstring>

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
	
// Вершинный шейдер
const char* vertexShaderSource = R"(#version 300 es
    layout(location = 0) in vec4 position;
    void main() {
        gl_Position = position;
    }
)";

// Фрагментный шейдер
const char* fragmentShaderSource = R"(#version 300 es
    precision mediump float;
    out vec4 fragColor;
    void main() {
        fragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
)";

// Функция проверки ошибок EGL
void checkEGLError(const char* location) {
    EGLint error = eglGetError();
    if (error != EGL_SUCCESS) {
        std::cerr << "EGL error at " << location << ": 0x" << std::hex << error << std::endl;
    }
}

// Функция для компиляции шейдера
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    if (shader == 0) {
        std::cerr << "Failed to create shader of type " << type << std::endl;
        return 0;
    }

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetShaderInfoLog(shader, logLength, nullptr, log.data());
        std::cerr << "Shader compilation failed: " << log.data() << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}


	inline void create( u32 const x, u32 const y )
	{
	// Инициализация X11
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Failed to open X display\n";
        return;
    }

    std::cout << "X11 display opened successfully\n";
    std::cout << "Display name: " << XDisplayString(display) << std::endl;

    // Получаем EGL display
    EGLDisplay eglDisplay = eglGetDisplay((EGLNativeDisplayType)display);
    if (eglDisplay == EGL_NO_DISPLAY) {
        std::cerr << "Failed to get EGL display with native display, trying platform display...\n";
        
        typedef EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, void* native_display, const EGLint* attrib_list);
        PFNEGLGETPLATFORMDISPLAYPROC eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
        
        if (eglGetPlatformDisplayEXT) {
            eglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_X11_KHR, (void*)display, NULL);
        }
    }

    if (eglDisplay == EGL_NO_DISPLAY) {
        std::cerr << "Failed to get EGL display\n";
        return;
    }

    std::cout << "Successfully got EGL display\n";

    EGLint majorVersion, minorVersion;
    if (!eglInitialize(eglDisplay, &majorVersion, &minorVersion)) {
        std::cerr << "Failed to initialize EGL\n";
        return;
    }

    std::cout << "EGL initialized: version " << majorVersion << "." << minorVersion << std::endl;
    std::cout << "EGL vendor: " << eglQueryString(eglDisplay, EGL_VENDOR) << std::endl;
    std::cout << "EGL version: " << eglQueryString(eglDisplay, EGL_VERSION) << std::endl;
    std::cout << "EGL extensions: " << eglQueryString(eglDisplay, EGL_EXTENSIONS) << std::endl;

    // Выбираем конфигурацию для GLES 3
    EGLint configAttribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,  // Меняем на ES3
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 8,
        EGL_SAMPLE_BUFFERS, 1,  // Включаем MSAA
        EGL_SAMPLES, 4,         // 4x MSAA
        EGL_NONE
    };
    
    EGLint numConfigs;
    EGLConfig eglConfig;
    if (!eglChooseConfig(eglDisplay, configAttribs, &eglConfig, 1, &numConfigs)) {
        std::cerr << "Failed to choose EGL config\n";
        return;
    }

    std::cout << "Found " << numConfigs << " matching EGL configurations\n";

    // Получаем нативный визуал
    EGLint nativeVisualId;
    eglGetConfigAttrib(eglDisplay, eglConfig, EGL_NATIVE_VISUAL_ID, &nativeVisualId);

    XVisualInfo visualTemplate;
    visualTemplate.visualid = nativeVisualId;
    int numVisuals;
    XVisualInfo* visualInfo = XGetVisualInfo(display, VisualIDMask, &visualTemplate, &numVisuals);

    if (!visualInfo) {
        std::cerr << "Failed to get X visual\n";
        return;
    }

    // Создаем окно X11
    Window root = DefaultRootWindow(display);
    XSetWindowAttributes windowAttributes;
    windowAttributes.background_pixel = 0;
    windowAttributes.border_pixel = 0;
    windowAttributes.colormap = XCreateColormap(display, root, visualInfo->visual, AllocNone);
    windowAttributes.event_mask = ExposureMask | StructureNotifyMask | KeyPressMask;

    unsigned long mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

    Window window = XCreateWindow(display, 
                                root,
                                0, 0, 800, 600,
                                0,
                                visualInfo->depth,
                                InputOutput,
                                visualInfo->visual,
                                mask,
                                &windowAttributes);

    XFree(visualInfo);

    // Устанавливаем свойства окна
    XSizeHints* sizeHints = XAllocSizeHints();
    sizeHints->flags = PMinSize | PMaxSize;
    sizeHints->min_width = sizeHints->max_width = 800;
    sizeHints->min_height = sizeHints->max_height = 600;
    XSetWMNormalHints(display, window, sizeHints);
    XFree(sizeHints);

    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    XMapWindow(display, window);
    XStoreName(display, window, "OpenGL ES 3.0 Triangle");

    // Ждем, пока окно станет видимым
    XEvent xev;
    while (1) {
        XNextEvent(display, &xev);
        if (xev.type == MapNotify)
            break;
    }

    XSync(display, False);

    // Создаем EGL поверхность
    EGLSurface eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)window, nullptr);
    if (eglSurface == EGL_NO_SURFACE) {
        std::cerr << "Failed to create EGL surface, error: 0x" << std::hex << eglGetError() << std::endl;
        return;
    }

    // Создаем контекст GLES 3
    EGLint contextAttribs[] = {
        EGL_CONTEXT_MAJOR_VERSION, 3,
        EGL_CONTEXT_MINOR_VERSION, 0,
        EGL_NONE
    };

    EGLContext eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);
    if (eglContext == EGL_NO_CONTEXT) {
        checkEGLError("eglCreateContext");
        return;
    }

    if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) {
        checkEGLError("eglMakeCurrent");
        return;
    }

    std::cout << "OpenGL ES version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL ES vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL ES renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Компиляция шейдеров
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    if (!vertexShader) return;
    
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    if (!fragmentShader) {
        glDeleteShader(vertexShader);
        return;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetProgramInfoLog(shaderProgram, logLength, nullptr, log.data());
        std::cerr << "Shader program linking failed: " << log.data() << std::endl;
        return;
    }

    // Вершины треугольника
    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    // Создаем и настраиваем VAO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Создаем и заполняем VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Настраиваем атрибуты вершин
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Отвязываем VAO и VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Включаем сглаживание (используем GL_SAMPLE_COVERAGE вместо GL_MULTISAMPLE)
    if (eglGetConfigAttrib(eglDisplay, eglConfig, EGL_SAMPLES, &success) && success > 0) {
        glEnable(GL_SAMPLE_COVERAGE);
        glSampleCoverage(1.0f, GL_FALSE);
    }

    // Основной цикл
    while (true) {
        while (XPending(display)) {
            XNextEvent(display, &xev);
            if (xev.type == ClientMessage) {
                if ((Atom)xev.xclient.data.l[0] == wmDeleteMessage) {
                    goto cleanup;
                }
            }
            if (xev.type == KeyPress)
                goto cleanup;
        }

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        eglSwapBuffers(eglDisplay, eglSurface);
    }

cleanup:
    // Очистка ресурсов
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(eglDisplay, eglContext);
    eglDestroySurface(eglDisplay, eglSurface);
    eglTerminate(eglDisplay);
    
    XDestroyWindow(display, window);
    XFreeColormap(display, windowAttributes.colormap);
    XCloseDisplay(display);

    return;
	}
	
public: // temporary
	Display *				display;
	Window                  root;
	    EGLint attributes[17] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };
	XVisualInfo *			visual_info;
	Colormap                color_map;
	XSetWindowAttributes    window_attributes;
	Window                  window;
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
		inex::memory::ie_delete	( m_context );
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
	m_context			= memory::ie_new<hw_wrapper_context>();
	//m_device			= 0;
}

inline void context_manager::make_current ( hw_wrapper_context * context )
{
	VERIFY			( context );
	//eglMakeCurrent	( context->display, context->window, context->context );
}

} // namespace render 
} // namespace inex 

//void inex::render::make_context_current


#endif // #ifndef HW_WRAPPER_BASE_GL4_LINUX_XLIB_H_INCLUDED