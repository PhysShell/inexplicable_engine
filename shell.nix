{ pkgs ? import <nixpkgs> { config.allowUnfree = true; } }:

pkgs.mkShell {
  buildInputs = [
    pkgs.xorg.libX11     # Библиотека Xlib
    pkgs.xorg.libXext    # Xext библиотеки
    pkgs.openal          # Библиотека OpenAL
    pkgs.pkg-config      # Для поиска библиотек
    pkgs.cmake           # Для сборки проекта
    pkgs.gcc             # Компилятор GCC
    pkgs.freealut        # Alut headers & libraries
    pkgs.mesa            # OpenGL headers & libraries
    pkgs.mesa.dev
    pkgs.libglvnd
    pkgs.libglvnd.dev    # OpenGL headers & libraries
    pkgs.gdb
    pkgs.vscode
    pkgs.vscodium
    pkgs.wayland
    pkgs.libffi
    pkgs.wayland-protocols
    pkgs.egl-wayland

    pkgs.gitRepo pkgs.gnupg pkgs.autoconf pkgs.curl
     pkgs.procps pkgs.gnumake pkgs.util-linux pkgs.m4 pkgs.gperf pkgs.unzip
     pkgs.cudatoolkit pkgs.linuxPackages.nvidia_x11
     pkgs.libGLU pkgs.libGL
     pkgs.xorg.libXi pkgs.xorg.libXmu pkgs.freeglut
     pkgs.xorg.libXext pkgs.xorg.libX11 pkgs.xorg.libXv pkgs.xorg.libXrandr pkgs.zlib 
     pkgs.ncurses5 pkgs.stdenv.cc pkgs.binutils

     #pkgs.wayland-libraries


   # pkgs.llvmPackages.lldb
  ];

  shellHook = ''
    #export LD_LIBRARY_PATH=$(nix eval --raw nixpkgs#gcc-unwrapped)/lib:$LD_LIBRARY_PATH
    export CUDA_PATH=${pkgs.cudatoolkit}
    # export LD_LIBRARY_PATH=${pkgs.linuxPackages.nvidia_x11}/lib:${pkgs.ncurses5}/lib
    export EXTRA_LDFLAGS="-L/lib -L${pkgs.linuxPackages.nvidia_x11}/lib"
    export EXTRA_CCFLAGS="-I/usr/include"
    #export __GLX_VENDOR_LIBRARY_NAME=nvidia
    #export EGL_PLATFORM=surfaceless
    #export LIBGL_DRIVERS_PATH=${pkgs.mesa}/lib/dri
    unset SOURCE_DATE_EPOCH
    echo "inexplicable development environment activated..."
  '';
}
