<img align="left" alt="Vanadium:: logo" src="misc/logo.svg" width="130px"/>

# Vanadium::

***V::** stands for Vanadium::*  
<br/>
[![License](https://img.shields.io/badge/liceecil-MIIM-brightgreen.svg)](https://en.wikipedia.org/wiki/MIT_License)

## Description
Yet another custom *"game engine"* no one needed.  
**Friendly note:** You probably shouldn't use it because the logic behind engine architecture is beyond human comprehension.  

## Requirements

* `C++17` capable compiler.
* [Cmake](https://cmake.org/) to compile the project.

## How to clone

```shell
git clone --recursive --progress https://github.com/Kepler-Br/Vanadium
```  
If you have already cloned this without submodules, use this:  
```shell
git submodule update --init --recursive --progress
```

## Compilation

### Dependencies

| Name                            | Licence                                    |
| -------------                   | -------------                              |
| [SDL2](https://www.libsdl.org/) | [zlib](https://www.libsdl.org/license.php) |

### Dependency installation on Ubuntu/Debian

```shell
apt install cmake libsdl2-dev libdrm-dev libgbm-dev
```

### Dependency installation on MacOS

```shell
brew install cmake sdl2
```

### Dependency installation on Windows

* ~~Install MSYS2~~
* ~~Open mingw64.exe in installed directory~~
* ~~Install
  packages: pacman -S mingw-w64-x86_64-clang mingw-w64-x86_64-lld mingw-w64-x86_64-make mingw-w64-x86_64-polly mingw-w64-x86_64-compiler-rt mingw-w64-x86_64-SDL2~~

### Dependencies included as sources or submodules

| Name                                                          | Maintainer                                       | Licence                                                                      | Short description                                               |
| -------------                                                 | -------------                                    | -------------                                                                | -------------                                                   |
| [stb](https://github.com/nothings/stb)                        | [Sean Barrett](http://nothings.org)              | [MIT/Public Domain](https://github.com/nothings/stb/blob/master/LICENSE)     | Single-file public domain libraries<br/>Only image part is used |
| [glm](https://github.com/g-truc/glm)                          | [G-Truc](http://www.g-truc.net)                  | [Modified MIT](https://github.com/g-truc/glm/blob/master/manual.md#section0) | OpenGL Mathematics                                              |
| [bgfx][bgfx-link], [bimg][bimg-link], [bx][bx-link]           | [Бранимир Караџић](https://github.com/bkaradzic) | [BSD 2-Clause](https://github.com/bkaradzic/bgfx/blob/master/LICENSE)        | Cross-platform graphics API wrapper                             |
| [spdlog](https://github.com/gabime/spdlog)                    | [Gabi Melman](https://github.com/gabime)         | [MIT](https://github.com/gabime/spdlog/blob/v1.x/LICENSE)                    | Logging library                                                 |
| [imgui](https://github.com/ocornut/imgui)                     | [Ocornut](https://www.miracleworld.net/)         | [MIT](https://github.com/ocornut/imgui/blob/master/LICENSE.txt)              | Immediate mode GUI                                              |
| [fmt](https://github.com/fmtlib/fmt)                          | [fmt](https://fmt.dev/latest/index.html)         | [MIT](https://github.com/fmtlib/fmt/blob/master/LICENSE.rst)                 | String formatting                                               |
| [yaml-cpp](https://github.com/jbeder/yaml-cpp)                | [Jesse Beder](https://github.com/jbeder)         | [MIT](https://github.com/jbeder/yaml-cpp/blob/master/LICENSE)                | YAML processing                                                 |
| [json](https://github.com/nlohmann/json)                      | [Niels Lohmann](http:/nlohmann.me)               | [MIT](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT)             | JSON  processing                                                |
| [xoshiro-cpp](https://github.com/Reputeless/Xoshiro-cpp)      | [Ryo Suzuki](https://github.com/Reputeless)      | [MIT](https://github.com/Reputeless/Xoshiro-cpp/blob/master/LICENSE)         | Pseudo random generator                                         |
| [tinyxml2](https://github.com/leethomason/tinyxml2)           | [Lee Thomason](www.grinninglizard.com)           | [zlib](https://github.com/leethomason/tinyxml2/blob/master/LICENSE.txt)      | XML processing                                                  |
| [physfs](https://github.com/icculus/physfs)                   | [Icculus](https://icculus.org/)                  | [zlib](https://hg.icculus.org/icculus/physfs/_raw-file/tip/LICENSE.txt)      | Virtual file system                                             |
| [earcut.hpp](https://github.com/mapbox/earcut.hpp) (modified) | [Mapbox](https://www.mapbox.com/)                | [ISC](https://github.com/mapbox/earcut.hpp/blob/master/LICENSE)              | Vertex triangulation                                            |
| [Boost.DI](https://github.com/boost-ext/di)                   | [boost-ext](https://github.com/boost-ext)        | [boost](https://www.boost.org/LICENSE_1_0.txt)                               | Dependency injection                                            |

[bgfx-link]: https://github.com/bkaradzic/bgfx
[bimg-link]: https://github.com/bkaradzic/bimg
[bx-link]: https://github.com/bkaradzic/bx

### Flags

| Flag              | Type          | Default           | Meaning                                                                     |
| -------------     | ------------- | -------------     | -------------                                                               |
| -DMAKE_LOGS       | Boolean       | ON                | Make logs                                                                   |
| -DBUILD_EXAMPLES  | Boolean       | OFF               | Build examples                                                              |
| -DVANADIUM_STATIC | Boolean       | ON                | Build a static version of the library                                       |
| -DVANADIUM_SHARED | Boolean       | ON                | Build a shared version of the library                                       |
| -DSDL2_SRC_PATH   | String        | **Not specified** | If specified, CMAKE will try to build SDL2 from sources from specified path |

### Compilation on Linux/MacOS

```shell
mkdir build; cd build; cmake .. -DBUILD_EXAMPLES=ON && make -j
```

### Compilation on Windows

* ~~Launch `MSYS2 MinGW` through Windows start menu or execute file `mingw64.exe` manually from installation directory~~
* ~~Navigate to Vanadium source directory using `cd` command.~~  
* ~~mkdir build; cd build~~
* ~~cmake -G "MinGW Makefiles" ..~~  
* ~~mingw32-make -j~~  
Not tested after migration to bgfx.

## Supported systems

| System name             | Runs          |
| -------------           | ------------- |
| GNU/Linux based systems | Yes           |
| MacOS                   | Yes           |
| Windows                 | Should        |
| Emscripten              | Should        |

## Supported render APIs

Pretty much everything that is supported by [bgfx](https://github.com/bkaradzic/bgfx).
