{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = [
    pkgs.xorg.libX11     # Библиотека Xlib
    pkgs.openal          # Библиотека OpenAL
    pkgs.pkg-config      # Для поиска библиотек
    pkgs.cmake           # Для сборки проекта
    pkgs.gcc             # Компилятор GCC
  ];

  shellHook = ''
    echo "inexplicable development environment activated..."
  '';
}
