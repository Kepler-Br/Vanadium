# Vanadium::

![Vanadium](misc/logo.png "Vanadium")  
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://en.wikipedia.org/wiki/MIT_License)

**V::** stands for *Vanadium::*  
Simple "game engine" for my projects.  
You probably should not use it.

## Requirements

* `C++17` capable compiler.
* [Cmake](https://cmake.org/) to compile the project.

## How to clone

`git clone --recursive --progress https://github.com/Kepler-Br/Vanadium`  
If you have already cloned this without submodules, use this:  
`git submodule update --init --recursive --progress`

## Compilation

### Dependencies

| Name                            | Licence                                    |
| -------------                   | -------------                              |
| [SDL2](https://www.libsdl.org/) | [zlib](https://www.libsdl.org/license.php) |

### Dependency installation on Ubuntu/Debian

`apt install cmake libsdl2-dev`

### Dependency installation on MacOS

`brew install cmake sdl2`

### Dependency installation on Windows

* ~~Install MSYS2~~
* ~~Open mingw64.exe in installed directory~~
* ~~Install
  packages: pacman -S mingw-w64-x86_64-clang mingw-w64-x86_64-lld mingw-w64-x86_64-make mingw-w64-x86_64-polly mingw-w64-x86_64-compiler-rt mingw-w64-x86_64-SDL2~~

### Dependencies included as sources or submodules

| Name                                                          | Author<br/>(Seek links from "Name" for contributor list) | Licence                                                                      | Short description                                               |
| -------------                                                 | -------------                                            | -------------                                                                | -------------                                                   |
| [stb](https://github.com/nothings/stb)                        | [Sean Barrett](http://nothings.org)                      | [MIT/Public Domain](https://github.com/nothings/stb/blob/master/LICENSE)     | Single-file public domain libraries<br/>Only image part is used |
| [glm](https://github.com/g-truc/glm)                          | [G-Truc](http://www.g-truc.net)                          | [Modified MIT](https://github.com/g-truc/glm/blob/master/manual.md#section0) | OpenGL Mathematics                                              |
| [spdlog](https://github.com/gabime/spdlog)                    | [Gabi Melman](https://github.com/gabime)                 | [MIT](https://github.com/gabime/spdlog/blob/v1.x/LICENSE)                    | Logging library                                                 |
| [imgui](https://github.com/ocornut/imgui)                     | [Ocornut](https://www.miracleworld.net/)                 | [MIT](https://github.com/ocornut/imgui/blob/master/LICENSE.txt)              | Immediate mode GUI                                              |
| [fmt](https://github.com/fmtlib/fmt)                          | [fmt](https://fmt.dev/latest/index.html)                 | [MIT](https://github.com/fmtlib/fmt/blob/master/LICENSE.rst)                 | String formatting                                               |
| [yaml-cpp](https://github.com/jbeder/yaml-cpp)                | [Jesse Beder](https://github.com/jbeder)                 | [MIT](https://github.com/jbeder/yaml-cpp/blob/master/LICENSE)                | YAML processing                                                 |
| [json](https://github.com/nlohmann/json)                      | [Niels Lohmann](http:/nlohmann.me)                       | [MIT](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT)             | JSON  processing                                                |
| [xoshiro-cpp](https://github.com/Reputeless/Xoshiro-cpp)      | [Ryo Suzuki](https://github.com/Reputeless)              | [MIT](https://github.com/Reputeless/Xoshiro-cpp/blob/master/LICENSE)         | Pseudo random _generator                                         |
| [tinyxml2](https://github.com/leethomason/tinyxml2)           | [Lee Thomason](www.grinninglizard.com)                   | [zlib](https://github.com/leethomason/tinyxml2/blob/master/LICENSE.txt)      | XML processing                                                  |
| [physfs](https://github.com/icculus/physfs)                   | [Icculus](https://icculus.org/)                          | [zlib](https://hg.icculus.org/icculus/physfs/_raw-file/tip/LICENSE.txt)       | Virtual file system                                             |
| [earcut.hpp](https://github.com/mapbox/earcut.hpp) (modified) | [Mapbox](https://www.mapbox.com/)                        | [ISC](https://github.com/mapbox/earcut.hpp/blob/master/LICENSE)              | Vertex triangulation                                            |
| [bgfx][bgfx-link], [bimg][bimg-link], [bx][bx-link]           | [Бранимир Караџић](https://github.com/bkaradzic)         | [BSD 2-Clause](https://github.com/bkaradzic/bgfx/blob/master/LICENSE)        | Cross-platform graphics API wrapper                             |

[bgfx-link]: https://github.com/bkaradzic/bgfx
[bimg-link]: https://github.com/bkaradzic/bimg
[bx-link]: https://github.com/bkaradzic/bx

### Flags

| Flag          | Default       | Meaning                                                      |
| ------------- | ------------- | -------------                                                |
| -DNO_LOGS     | *Not set*     | Disable any logging. You probably don't want this to happen. |

### Compilation on Linux/MacOS

* `mkdir build; cd build`
* `cmake ..`
* `make -j`

### Compilation on Windows

* ~~Launch `MSYS2 MinGW` through Windows start menu or execute file `mingw64.exe` manually from installation directory~~
* ~~Navigate to Vanadium source directory using `cd` command.~~  
* ~~mkdir build; cd build~~
* ~~cmake -G "MinGW Makefiles" ..~~  
* ~~mingw32-make -j~~  
Not tested after migration to bgfx.

## Supported systems

| System _name             | Support           | Runs                    |
| -------------           | -------------     | -------------           |
| GNU/Linux based systems | Yes               | Yes                     |
| MacOS                   | Yes               | Yes                     |
| Windows                 | Planned           | No                      |
| Emscripten              | Planned           | No                      |

## Supported render APIs

Pretty much everything that is supported by [bgfx](https://github.com/bkaradzic/bgfx).
