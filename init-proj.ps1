# Fetch dependencies to the global conan directory and compile them, adding a native config file that allows meson to locate said deps:
conan install . --output-folder=builddir --build=missing

# Debug build in 'builddir/debug':
meson setup --buildtype=debug --native-file=builddir/conan_meson_native.ini . builddir/debug
meson compile -C builddir/debug

# Final executables:
# Windows:     '<project_root>/builddir/debug/relearnopengl.exe'
# Linux/MacOS: '<project_root>/builddir/debug/relearnopengl'

# Release/Optimised build in 'builddir/release':
meson setup --buildtype=release --native-file=builddir/conan_meson_native.ini -Db_lto=true . builddir/release
# meson compile -C builddir/release

# Final executables:
# Windows:     '<project_root>/builddir/release/relearnopengl.exe'
# Linux/MacOS: '<project_root>/builddir/release/relearnopengl'
