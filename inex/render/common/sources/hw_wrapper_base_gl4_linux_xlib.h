#ifndef HW_WRAPPER_BASE_GL4_LINUX_XLIB_H_INCLUDED
#	define HW_WRAPPER_BASE_GL4_LINUX_XLIB_H_INCLUDED

#   include <X11/Xlib.h>
#   include <X11/Xutil.h>
#   include <EGL/egl.h>
#   include <EGL/eglplatform.h>
#   include <EGL/eglext.h>
#   include <GLES3/gl3.h> 
#   include <iostream>
#   include <vector>
#   include <cstring>

#	include <inex/render/gl4/gl4_extensions.h>
#	include <inex/render/core/quasi_singleton.h>

#   if INEX_PLATFORM_LINUX
namespace inex::render
{
    using native_display    = Display *;
    using native_window     = Window;
    using native_visual     = XVisualInfo *;
    using native_context    = EGLContext;
} // namespace inex::render
#   else
#       error please define native types for your platform / display system
#   endif // if INEX_PLATFORM_LINUX

namespace inex {
namespace render {

enum class texture_format
{
    tf_rgba8,
    tf_rgba16f,

}; // enum class texture_format

enum class render_feature
{
    rf_compute_shaders,
    rf_ray_tracing, // lmao rly

}; // enum class render_feature

// forward declarations
class hw_wrapper_context;
class render_device_desc;
class render_context;

class device_capabilities
{
public:
    std::string vendor;
    std::string renderer;
    std::string version;
    std::vector< std::string > extensions;

    struct
    {
        uint32_t max_texture_size;
        uint32_t max_viewport_dims[ 2 ];
        uint32_t max_color_attachments;
        uint32_t max_samples;
    } limits;

    struct {
        bool compute_shader_support;
        bool geometry_shader_support;
        bool tessellation_support;
        bool ray_tracing_support;
        bool mesh_shaders_support;
    } features;

    struct {
        bool depth_texture_support;
        bool float_texture_support;
        bool compressed_texture_support;
        bool srgb_support;
    } formats;

public:
    bool supports_texture_format ( texture_format format ) const
    {
        switch (format)
        {
        case texture_format::tf_rgba8:      return true;
        case texture_format::tf_rgba16f:    return formats.float_texture_support;
        default: NODEFAULT();
        }
    }

    bool supports_feature ( render_feature feature )
    {
        switch (feature)
        {
        case render_feature::rf_compute_shaders:    return features.compute_shader_support;
        case render_feature::rf_ray_tracing:        return features.ray_tracing_support;        
        default: NODEFAULT();
        }
    }

    // void initialize_d3d11 ( ID3D11Device* device )
    // {
    //     D3D11_FEATURE_DATA_D3D11_OPTIONS features = {};
    //     device->CheckFeatureSupport( D3D11_FEATURE_D3D11_OPTIONS, &features, sizeof( features ) );
    // }

    void initialize( )
    {
        vendor          = (const char*)glGetString( GL_VENDOR );
        renderer        = (const char*)glGetString( GL_RENDERER );
        version         = (const char*)glGetString( GL_VERSION );

        glGetIntegerv   ( GL_MAX_TEXTURE_SIZE, (GLint*)&limits.max_texture_size );
        glGetIntegerv   ( GL_MAX_VIEWPORT_DIMS, (GLint*)limits.max_viewport_dims );
    }
}; // class device_capabilities

struct render_device_desc
{
    u32 width;
    u32 height;
    pcstr header;
    bool fullscreen;
}; // struct render_device_desc

class i_render_device_base
{
public:
    virtual ~i_render_device_base( ) = default;
    virtual bool create ( ) = 0;
    virtual void destroy ( ) = 0;
    //virtual void reset ( ) = 0;
    virtual void draw_frame( ) = 0;
    virtual void end_frame ( ) = 0;
    virtual void clear_frame ( ) = 0;
    virtual device_capabilities get_capabilities ( ) const = 0;
    virtual render_context * get_context ( ) = 0;
}; // class i_render_device_base

// class render_deivce_base : public i_render_device_base
// {
// protected:
//     virtual bool create_context    ( render_device_desc const& desc ) = 0;
//     virtual void destory_context    ( ) = 0; 
// protected:
//     std::unique_ptr< render_context > m_context;
//     device_capabilities m_capabilities;

// public:
//     bool create ( render_device_desc const& desc ) override final
//     {
//         if (!create_context( desc ) )
//         {
//             return false;
//         }

//         m_capabilities.initialize( );
//         return true;
//     }

//     void destroy ( ) override final
//     {
//         destory_context ( );
//         m_context.reset( );
//     }
// }; // class render_deivce_base

class render_context
{
protected:
    native_display  m_display;
    native_window   m_window;
#   if INEX_PLATFORM_LINUX
#   else
#       error please define native members for your platform / display system
#   endif // if INEX_PLATFORM_LINUX
public:
    virtual     ~render_context ( ) = default;
    virtual bool create         ( render_device_desc const& desc ) = 0;
    virtual void destroy        ( ) = 0;
    virtual void make_current   ( ) = 0;
    virtual void swap_buffers   ( ) = 0;
}; // class render_context

class render_context_x11 : public render_context
{
private:
    void check_egl_error( const char* location )
    {
        EGLint error = eglGetError( );
        if ( error != EGL_SUCCESS )
        {
            std::cerr << "EGL error at " << location << ": 0x" << std::hex << error << std::endl;
        }
    }

public:
    bool create ( render_device_desc const& desc ) override
    {
        m_display       = XOpenDisplay( nullptr );
        ASSERT_D        ( m_display, "Failed to open X display" );

        m_egl_display   = eglGetDisplay( m_display );
        if ( m_egl_display == EGL_NO_DISPLAY )
        {
            destroy     ( );
            ASSERT_S    ( !"Failed to get EGL display");
        }

        EGLint major_version, minor_version;
        ASSERT_D        ( eglInitialize( m_egl_display, &major_version, &minor_version ), "Failed to initialize EGL" );

		LOGGER	(
			"[renderer][info]\t: %s\n[renderer][info]\t: OpenGL version supported %d.%d\n",
			glGetString( GL_RENDERER ),
			major_version,
            minor_version
		);

        EGLint config_attribs[ ] = {
            EGL_SURFACE_TYPE,       EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE,    EGL_OPENGL_ES3_BIT,
            EGL_RED_SIZE,           8,
            EGL_GREEN_SIZE,         8,
            EGL_BLUE_SIZE,          8,
            EGL_ALPHA_SIZE,         8,
            EGL_DEPTH_SIZE,         24,
            EGL_STENCIL_SIZE,       8,
            EGL_SAMPLE_BUFFERS,     1, // Enable MSAA
            EGL_SAMPLES,            4, // 4x MSAA
            EGL_NONE
        };

        EGLint num_configs;
        EGLConfig egl_config;

        auto egl_choose_config_result =  
            eglChooseConfig (
                m_egl_display,
                config_attribs,
                &egl_config,
                1,
                &num_configs
            );

        if (!egl_choose_config_result)
        {
            destroy ( );
            ASSERT_S ( !"Failed to choose EGL config");
        }

        LOGGER          ( "Found %d matching EGL configurations", num_configs );

        EGLint          native_visual_id;
        eglGetConfigAttrib ( m_egl_display, egl_config, EGL_NATIVE_VISUAL_ID, &native_visual_id );

        XVisualInfo visualTemplate;
        visualTemplate.visualid     = native_visual_id;
        
        s32 num_visuals;
        native_visual visual_info   = XGetVisualInfo( m_display, VisualIDMask, &visualTemplate, &num_visuals );
        ASSERT_D        ( visual_info, "Failed to get X visual" );

        native_window root      = DefaultRootWindow( m_display );

        m_attributes.background_pixel  = 0;
        m_attributes.border_pixel      = 0;
        m_attributes.colormap          = XCreateColormap( m_display, root, visual_info->visual, AllocNone );
        m_attributes.event_mask        = ExposureMask | StructureNotifyMask | KeyPressMask;

        u64 mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

        m_window = XCreateWindow(
            m_display, 
            root,
            0, 0, desc.width, desc.height, 0, // window position and size
            visual_info->depth,
            InputOutput,
            visual_info->visual,
            mask,
            &m_attributes
        );

        XFree                   ( visual_info );

        XSizeHints* size_hints  = XAllocSizeHints( );
        size_hints->flags       = PMinSize | PMaxSize;
        size_hints->min_width   = size_hints->max_width = desc.width;
        size_hints->min_height  = size_hints->max_height = desc.height;

        XSetWMNormalHints       ( m_display, m_window, size_hints );
        XFree                   ( size_hints );

        m_wm_delete_message     = XInternAtom( m_display, "WM_DELETE_WINDOW", False );
        XSetWMProtocols         ( m_display, m_window, &m_wm_delete_message, 1 );

        XMapWindow              ( m_display, m_window );
        XStoreName              ( m_display, m_window, desc.header );

        XEvent xev;
        while ( 1 ) // wait till window becomes visible
        {
            XNextEvent  ( m_display, &xev );
            if (xev.type == MapNotify)
                break;
        }

        XSync               ( m_display, False );

        m_egl_surface       = eglCreateWindowSurface( m_egl_display, egl_config, (EGLNativeWindowType)m_window, nullptr );
        if (m_egl_surface == EGL_NO_SURFACE )
        {
            LOGGER( "Failed to create EGL surface, error: 0x%x", eglGetError( ) );
            destroy( );
            ASSERT_S ( false );
        }

        EGLint context_attribs[ ] = {
            EGL_CONTEXT_MAJOR_VERSION, 3,
            EGL_CONTEXT_MINOR_VERSION, 0,
            EGL_NONE
        };

        m_egl_context = eglCreateContext( m_egl_display, egl_config, EGL_NO_CONTEXT, context_attribs );
        if (m_egl_context == EGL_NO_CONTEXT)
        {
            destroy ( );
            check_egl_error( "eglCreateContext" );
            ASSERT_S( !"m_egl_context == EGL_NO_CONTEXT" );
        }

        GLint success;
        if (eglGetConfigAttrib( m_egl_display, egl_config, EGL_SAMPLES, &success) && success > 0)
        {
            LOGGER( "gl_enable: GL_SAMPLE_COVERAGE" );
            glEnable(GL_SAMPLE_COVERAGE);
            glSampleCoverage(1.0f, GL_FALSE);
        }

        return true;
    }

    void make_current ( ) override
    {
        if ( !eglMakeCurrent( m_egl_display, m_egl_surface, m_egl_surface, m_egl_context ) )
        {
            LOGGER( "Failed to make context current: 0x%x", eglGetError( ) );
            NODEFAULT( );
        }
    }

    void swap_buffers ( ) override
    {
        eglSwapBuffers  ( m_egl_display, m_egl_surface );
    }

    void destroy( ) override
    {
        if ( m_egl_display != EGL_NO_DISPLAY )
        {
            eglMakeCurrent( m_egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );

            if ( m_egl_context != EGL_NO_CONTEXT )
            {
                eglDestroyContext( m_egl_display, m_egl_context );
            }

            if ( m_egl_surface != EGL_NO_SURFACE )
            {
                eglDestroySurface( m_egl_display, m_egl_surface );
            }

            eglTerminate( m_egl_display );
        }

        if ( m_display ) 
        {
            XDestroyWindow  ( m_display, m_window );
            XFreeColormap   ( m_display, m_attributes.colormap );
            XCloseDisplay   ( m_display );
        }
    }

    bool process_events()
    {
        XEvent xev;
        while ( XPending( m_display ) )
        {
            XNextEvent( m_display, &xev );
            if ( xev.type == ClientMessage )
            {
                if ( ( Atom ) xev.xclient.data.l[ 0 ] == m_wm_delete_message )
                {
                    return false;
                }
            }

            if ( xev.type == KeyPress )
            {
                return false;
            }
        }

        return true;
    }

private:
    EGLDisplay  m_egl_display;
    EGLContext  m_egl_context;
    EGLSurface  m_egl_surface;
    Atom        m_wm_delete_message;
    XSetWindowAttributes m_attributes;
}; // class render_context_x11

class i_renderable {
public:
    virtual ~i_renderable() = default;
    virtual void initialize() = 0;
    virtual void render() = 0;
    virtual void destroy() = 0;
};

// Реализация для треугольника
class triangle : public i_renderable {
private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_shader_program;

    const char* vertex_shader_source = R"(#version 300 es
        layout(location = 0) in vec4 position;
        void main() {
            gl_Position = position;
        }
    )";

    const char* fragment_shader_source = R"(#version 300 es
        precision mediump float;
        out vec4 fragColor;
        void main() {
            fragColor = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )";

public:
    void initialize() override {
        // Компиляция шейдеров
        GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
        GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

        // Создание программы
        m_shader_program = glCreateProgram();
        glAttachShader(m_shader_program, vertex_shader);
        glAttachShader(m_shader_program, fragment_shader);
        glLinkProgram(m_shader_program);

        // Очистка шейдеров после линковки
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        // Создание геометрии
        GLfloat vertices[] = {
            0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
        };

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void render() override {
        glUseProgram(m_shader_program);
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    void destroy() override {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteProgram(m_shader_program);
    }

private:
    GLuint compile_shader(GLenum type, const char* source) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLint length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> log(length);
            glGetShaderInfoLog(shader, length, nullptr, log.data());
            // Здесь лучше использовать вашу систему логирования
            std::cerr << "Shader compilation failed: " << log.data() << std::endl;
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }
};

class gl_render_device : public i_render_device_base
{
private:
    std::unique_ptr<render_context> m_context;
    std::vector<std::unique_ptr<i_renderable>> m_renderables;

public:
    device_capabilities get_capabilities ( ) const
    {
        return device_capabilities( );
    }

    bool create( ) override
    {
        render_device_desc desc;
        desc.width = 800;
        desc.height = 600;
        desc.header = "OpenGL ES 3.0 Renderer";

        m_context = std::make_unique< render_context_x11 >();
        if (!m_context->create( desc ) ) {
            return false;
        }

        m_context->make_current( );

        auto triangle_obj = std::make_unique<triangle>();
        triangle_obj->initialize( );
        m_renderables.push_back( std::move( triangle_obj ) );

        return true;
    }

    void draw_frame( ) override
    {
        clear_frame( );
    }

    void end_frame( ) override
    {
        m_context->swap_buffers( );
    }

    void clear_frame( ) override
    {
        glClearColor( 0.8f, 0.2f, 0.2f, 1.0f );
        glClear     ( GL_COLOR_BUFFER_BIT );
    }

    render_context* get_context() override
    {
        return m_context.get();
    }

    void render_frame( )
    {
        draw_frame( );
        
        for (auto& renderable : m_renderables)
        {
            renderable->render( );
        }
        
        end_frame( );
    }

    void destroy( ) override
    {
        for (auto& renderable : m_renderables)
        {
            renderable->destroy( );
        }

        m_renderables.clear( );
        
        if (m_context)
        {
            m_context->destroy( );
        }
    }

    bool running( )
    {
        return static_cast< render_context_x11 * >( m_context.get( ) )->process_events( );
    }
}; // class gl_render_device

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
	hw_wrapper_context ( )
    {
        
    }
	~hw_wrapper_context( ) { ; }

	inline void create( u32 const x, u32 const y, pcstr const window_title )
	{
        LOGGER( "using gl_render_device " );
        render_device_desc desc;
        desc.width = 800;
        desc.height = 600;
        desc.header = "My Window";

        gl_render_device * device = memory::ie_new< gl_render_device > ( );

        device->create( );
        LOGGER( "entering engine loop" );
        while ( device->running( ) )
        {
            device->render_frame( );
        }

        LOGGER( "destroying device" );
        device->destroy( );
        memory::ie_delete ( device );
        return;
	}
	
public:

}; // struct hw_wrapper_context

class hw_wrapper_base //: boost::noncopyable
{
public:
	hw_wrapper_base	( );

	// remove inline
	void create	( u32 const x, u32 const y, pcstr const window_title )
	{
		m_context->create( x, y, window_title );
	}
	
	void destroy ( )
	{
		VERIFY					( m_context != 0 );
		inex::memory::ie_delete	( m_context );
	}

	pvoid					render_device ( ) const		{ NOT_IMPLEMENTED ( ); return 0; }
	hw_wrapper_context *	context	( ) const			{ return m_context; }

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