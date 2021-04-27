# Vanadium::
![Vanadium](misc/logo.png "Vanadium")  
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://en.wikipedia.org/wiki/MIT_License)

**V** stands for *Vanadium::*  
**Todo**: Think about description.

## Requirements

* `OpenGL 3.X and >` capable video card;
* `C++17` capable compiler.
* [Cmake](https://cmake.org/) to compile the project.

## How to clone

`git clone --recursive https://github.com/Kepler-Br/Vanadium`  
If you have already cloned this without submodules, use this:  
`git submodule update --init --recursive`

## Compilation

### Dependencies

| Name                                       | Licence                                                                      | Remark          | OS                  |
| -------------                              | -------------                                                                | --------------- | -------------       |
| [GLEW](https://github.com/nigels-com/glew) | [Multi licenced](https://github.com/nigels-com/glew/blob/master/LICENSE.txt) | OpenGL bindings | Linux/Windows       |
| [SDL2](https://github.com/libsdl-org/SDL)  | [zlib](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt)              | -               | Linux/Windows/MacOS |

### Dependency installation on Ubuntu/Debian

`apt install cmake libsdl2-dev libglew-dev`  
**Todo**: Try to install this on bare bones ubuntu.

### Dependency installation on MacOS

`brew install cmake sdl2`

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
| [tinyxml2](https://github.com/leethomason/tinyxml2)           | [Lee Thomason](www.grinninglizard.com)                   | [zlib](https://github.com/leethomason/tinyxml2/blob/master/LICENSE.txt)      | XML processing                                                  |
| [physfs](https://icculus.org/physfs/)                         | [Icculus](https://icculus.org/)                          | [zlib](https://hg.icculus.org/icculus/physfs/raw-file/tip/LICENSE.txt)       | Virtual file system                                             |
| [earcut.hpp](https://github.com/mapbox/earcut.hpp) (modified) | [Mapbox](https://www.mapbox.com/)                        | [ISC](https://github.com/mapbox/earcut.hpp/blob/master/LICENSE)              | Vertex triangulation                                            |

### Compilation

#### Flags

| Flag          | Default       | Meaning                                                                      |
| ------------- | ------------- | -------------                                                                |
| -DRENDER_API  | OpenGL        | What render API to use.<br/>OpenGL is the only supported render API for now. |
| -DNO_LOGS     | *Not set*     | Disable any logging. You probably don't want this happen.                    |

```
mkdir build
cd build
cmake ..
make -j
```  

Library should be inside `build` directory.

## Supported systems

| System name   | Support       | Runs          |
| ------------- | ------------- | ------------- |
| Ubuntu        | Yes           | Yes           |
| Other linux   | Planned       | Maybe         |
| MacOS         | Yes           | Yes           |
| Other unix    | No            | Untested      |
| Windows       | CYGWIN only   | No            |
| Emscripten    | Planned       | No            |
| Android       | *Maybe*       | No            |
| IOS           | Ha-ha-ha      | No            |

## Supported render APIs

| API name          | Support        |
| ----------------- | -------------- |
| OpenGL 3.X        | Yes            |
| OpenGL ES         | Planned        |
| WebGL(Emscripten) | Planned        |
| Vulkan            | No             |
| DirectX *         | No             |