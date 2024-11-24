{ pkgs ? import <nixpkgs> { config.allowUnfree = true; } }:

pkgs.mkShell {
  buildInputs =  with pkgs; [
    cmake
    pkg-config
    
    # X11
    xorg.libX11
    xorg.libX11.dev
    xorg.libXext
    xorg.libXrender
    xorg.libXfixes
    xorg.xorgproto
    
    # OpenGL и NVIDIA
    libGL
    libGLU
    mesa
    linuxPackages.nvidia_x11
    nvidia-vaapi-driver
    egl-wayland
    
    # GLES 3.0
    mesa_glu
    mesa_drivers
    mesa.drivers
    libglvnd
    
    # Добавляем pkg-config файлы для GLES
    mesa.dev
    
    # Утилиты для отладки
    glxinfo
    vulkan-tools
    
    # IDE
    vscode

    # Others
    gdb
  ];

  shellHook = ''
    export PATH=$PATH:${pkgs.linuxPackages.nvidia_x11}/bin
    export LD_LIBRARY_PATH=/run/opengl-driver/lib:/run/opengl-driver-32/lib:${pkgs.linuxPackages.nvidia_x11}/lib
    export PKG_CONFIG_PATH="${pkgs.mesa.dev}/lib/pkgconfig:$PKG_CONFIG_PATH"
    export __GLX_VENDOR_LIBRARY_NAME=nvidia
    
    # GLES3
    export LIBGL_DEBUG=verbose
    export EGL_LOG_LEVEL=debug
    export MESA_GL_VERSION_OVERRIDE=3.0
    export MESA_GLSL_VERSION_OVERRIDE=300
    
    echo "NVIDIA OpenGL ES 3.0 development environment ready!"
    echo ""
    echo "GPU Information:"
    glxinfo | grep "OpenGL renderer"
    echo ""
    echo "OpenGL ES Version:"
    glxinfo | grep "OpenGL ES"
    
    # Проверяем доступность GLES3
    if command -v glxinfo >/dev/null; then
      echo ""
      echo "Available GL versions:"
      glxinfo | grep "version string"
    fi

    # Проверяем наличие библиотек GLES
    echo ""
    echo "Checking GLES libraries:"
    pkg-config --libs glesv2 || echo "glesv2.pc not found"
    ls -l /run/opengl-driver/lib/libGLESv2.so* || echo "libGLESv2.so not found"

    unset SOURCE_DATE_EPOCH

    echo "inexplicable development environment activated..."
  '';
}
