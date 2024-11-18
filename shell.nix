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
    pkgs.libglvnd.dev    # OpenGL headers & libraries
    pkgs.gdb
    pkgs.vscode
    pkgs.vscodium
    pkgs.llvmPackages.lldb
  ];

  shellHook = ''
    #export LD_LIBRARY_PATH=$(nix eval --raw nixpkgs#gcc-unwrapped)/lib:$LD_LIBRARY_PATH
    echo "inexplicable development environment activated..."
  '';
}
