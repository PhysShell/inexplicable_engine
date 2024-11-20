#ifndef HW_WRAPPER_BASE_GL4_LINUX_WAYLAND_H_INCLUDED
#   define HW_WRAPPER_BASE_GL4_LINUX_WAYLAND_H_INCLUDED

#   include <wayland-client.h>
#   include <EGL/egl.h>
#   include <EGL/eglext.h>
#   include <wayland-egl.h>
#   include <GL/gl.h>
#   include <GL/glext.h>
#   include <inex/include/xdg-shell-client-protocol.h>

#   include <inex/render/gl4/gl4_extensions.h>
#   include <inex/render/core/quasi_singleton.h>


namespace inex {
namespace render {

class hw_wrapper_context;

class context_manager : public quasi_singleton<context_manager> {
public:
    inline void make_current(hw_wrapper_context *context);
    inline void create(u32 const x, u32 const y) {
        NOT_IMPLEMENTED();
    }
};


struct hw_wrapper_context {
public:
    hw_wrapper_context() : display(nullptr), egl_display(EGL_NO_DISPLAY), egl_surface(EGL_NO_SURFACE), egl_context(EGL_NO_CONTEXT) {}
    ~hw_wrapper_context() {
        if (egl_context != EGL_NO_CONTEXT) eglDestroyContext(egl_display, egl_context);
        if (egl_surface != EGL_NO_SURFACE) eglDestroySurface(egl_display, egl_surface);
        if (egl_display != EGL_NO_DISPLAY) eglTerminate(egl_display);
        if (display) wl_display_disconnect(display);
    }

    inline void create(u32 const width, u32 const height) {

   display = wl_display_connect(nullptr);
    ASSERT_D(display, "Wayland error: Cannot connect to Wayland display");

    registry = wl_display_get_registry(display);
    ASSERT_D(registry, "Wayland error: Cannot get registry");

    ASSERT_D(registry != nullptr, "Wayland error: registry is nullptr");
    ASSERT_D(this != nullptr, "Wayland error: 'this' is nullptr");

    ASSERT_D(display != nullptr, "Wayland error: 'DISPLAY' is nullptr");

    auto result = wl_registry_add_listener(registry, &registry_listener, this);
    wl_display_roundtrip(display);

    ASSERT_D(compositor, "Wayland error: Cannot find compositor");
    surface = wl_compositor_create_surface(compositor);
    ASSERT_D(surface, "Wayland error: Cannot create surface");

    ASSERT_D(wm_base, "Wayland error: xdg_wm_base not initialized");

    // Создаем xdg_surface и xdg_toplevel
    xdg_surface = xdg_wm_base_get_xdg_surface(wm_base, surface);
    ASSERT_D(xdg_surface, "Wayland error: Cannot create xdg_surface");

    xdg_toplevel = xdg_surface_get_toplevel(xdg_surface);
    ASSERT_D(xdg_toplevel, "Wayland error: Cannot create xdg_toplevel");
    xdg_toplevel_set_title(xdg_toplevel, "Wayland EGL Window");

    wl_surface_commit(surface);
    wl_display_roundtrip(display);

    egl_display = eglGetDisplay(display);
    ASSERT_D(egl_display != EGL_NO_DISPLAY, "EGL error: Cannot get display");

    if (!eglInitialize(egl_display, nullptr, nullptr)) {
        EGLint error = eglGetError();
        ASSERT_D(false, "EGL error: Cannot initialize. Error code: %d", error);
    }

    EGLConfig config;
    EGLint egl_attributes[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_NONE
    };

    EGLint num_configs;
    eglChooseConfig(egl_display, egl_attributes, &config, 1, &num_configs);
    ASSERT_D(num_configs > 0, "EGL error: Cannot choose config");

    wl_egl_window *egl_window = wl_egl_window_create(surface, width, height);
    ASSERT_D(egl_window, "EGL error: Cannot create wl_egl_window");

    egl_surface = eglCreateWindowSurface(egl_display, config, reinterpret_cast<EGLNativeWindowType>(egl_window), nullptr);
    ASSERT_D(egl_surface != EGL_NO_SURFACE, "EGL error: Cannot create surface");

    egl_context = eglCreateContext(egl_display, config, EGL_NO_CONTEXT, nullptr);
    ASSERT_D(egl_context != EGL_NO_CONTEXT, "EGL error: Cannot create context");

    ASSERT_D(eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context) == EGL_TRUE,
             "EGL error: Cannot make context current");

    LOGGER("- [hw-wrapper][info]\t: EGL context and surface created");

    }

private:
    static const wl_registry_listener registry_listener;

public:
    wl_display *display;
    wl_registry *registry;
    wl_compositor *compositor;
    wl_surface *surface;

    struct xdg_wm_base *wm_base;
    struct xdg_surface *xdg_surface;
    struct xdg_toplevel *xdg_toplevel;

    EGLDisplay egl_display;
    EGLSurface egl_surface;
    EGLContext egl_context;
};

static void handle_xdg_wm_base_ping(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial);

static const struct xdg_wm_base_listener wm_base_listener = {
    handle_xdg_wm_base_ping
};

static void handle_xdg_wm_base_ping(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial) {
    auto *context = reinterpret_cast<hw_wrapper_context *>(data);
    xdg_wm_base_pong(xdg_wm_base, serial);
    LOGGER("Received ping from xdg_wm_base, responded with pong");
}

static void registry_handler(void *data, wl_registry *registry, uint32_t id, const char *interface, uint32_t version) {
    LOGGER("Binding interface: %s, id: %d, version: %d", interface, id, version);
    auto *context = reinterpret_cast<hw_wrapper_context *>(data);
  if (!context) {
    ASSERT_S(!"Context is null registry_handler");
        return;
  }
    if (strcmp(interface, "wl_compositor") == 0) {
        context->compositor = reinterpret_cast<wl_compositor *>(wl_registry_bind(registry, id, &wl_compositor_interface, 1));
    } else if (strcmp(interface, "xdg_wm_base") == 0) {
        ASSERT_D(context->wm_base, "Wayland error: Failed to bind xdg_wm_base interface");
        context->wm_base = reinterpret_cast<xdg_wm_base *>(wl_registry_bind(registry, id, &xdg_wm_base_interface, 1));
        ASSERT_D(context->wm_base, "Wayland error: Failed to bind xdg_wm_base interface reinterpret_cast");
    }

    xdg_wm_base_add_listener(context->wm_base, &wm_base_listener, context);
}

class hw_wrapper_base {
public:
    hw_wrapper_base() { m_context = memory::ie_new<hw_wrapper_context>(); }

    void create(u32 const width, u32 const height, pcstr const window_title) {
        m_context->create(width, height);
    }

    void destroy() {
        VERIFY(m_context != 0);
        memory::ie_delete(m_context);
    }

    pvoid render_device() const { NOT_IMPLEMENTED(); return nullptr; }
    hw_wrapper_context *context() const { return m_context; }

protected:
    hw_wrapper_context *m_context;
};

inline void context_manager::make_current(hw_wrapper_context *context) {
    VERIFY(context);
    eglMakeCurrent(context->egl_display, context->egl_surface, context->egl_surface, context->egl_context);
}

} // namespace render
} // namespace inex

#endif // #ifndef HW_WRAPPER_BASE_GL4_LINUX_WAYLAND_H_INCLUDED