# Vanadium graphics engine
**Todo**: Think about description.
**Todo** Use GLAD instead. GLEW leaks.
## Requirements
* `OpenGL 3.X` capable video card;
* `C++14` capable compiler;
* [Cmake](https://cmake.org/) to compile project.
## How to clone
`git clone --recursive https://github.com/Kepler-Br/Vanadium`  
If you have already cloned this without submodules, use this:  
`git submodule update --init --recursive`
## Compilation
### Dependencies
| Name          | Licence       | Why?          |
| ------------- | ------------- | ------------- |
| [GLEW](https://github.com/nigels-com/glew) | [Multi licenced](https://github.com/nigels-com/glew/blob/master/LICENSE.txt) | OpenGL |

### Dependency installation on ubuntu
**Todo**: Try to install this on bare bones ubuntu.
### Dependency installation on MacOS   
**Todo**: Compile and run it on MacOS.
### Dependencies included as sources or submodules
**Todo:** Add SDL2 as optional source dependency.

| Name          | Licence       |
| ------------- | ------------- |
| [stb](https://github.com/nothings/stb) | [MIT/Public Domain](https://github.com/nothings/stb/blob/master/LICENSE) |
| [GLM](https://github.com/g-truc/glm) | [Modified MIT](https://github.com/g-truc/glm/blob/master/manual.md#section0)|
| [spdlog](https://github.com/gabime/spdlog) | [MIT](https://github.com/gabime/spdlog/blob/v1.x/LICENSE)|
| [yaml-cpp](https://github.com/jbeder/yaml-cpp) | [MIT](https://github.com/jbeder/yaml-cpp/blob/master/LICENSE) |
| [tinyxml2](https://github.com/leethomason/tinyxml2) | [zlib](https://github.com/leethomason/tinyxml2/blob/master/LICENSE.txt)|
| [PhysicsFS](https://icculus.org/physfs/) | [zlib](https://hg.icculus.org/icculus/physfs/raw-file/tip/LICENSE.txt) |
| [SDL2](https://github.com/libsdl-org/SDL) | [zlib](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt) |

### Compilation
```
mkdir build
cd build
cmake ..
make -j
```  
Everything should be inside `build` directory.

## Engine documentation generation
No engine documentation right now.  
~~doxygen Doxyfile  
Everything should be inside `Documentation` folder.  
Now open `./Documentation/html/index.html`.~~
## Supported systems
| System name   | Support       | Runs          |
| ------------- | ------------- | ------------- |
| Ubuntu        | Yes           | Yes           |
| Other linux   | Planned       | Maybe         |
| MacOS         | Planned       | Yes           |
| Other unix    | No            | Untested      |
| Windows       | CYGWIN only   | No            |
| CYGWIN        | Planned       | No            |
| Emscripten    | Planned       | No            |
| Android       | *Maybe*       | No            |
| IOS           | Ha-ha-ha.     | No            |
## Supported render APIs
| API name          | Support        |
| ----------------- | -------------- |
| OpenGL 3.X        | Yes            |
| OpenGL ES         | Planned        |
| WebGL(Emscripten) | Planned        |
| Vulkan            | Hell no        |
| DirectX 11        | Distant future |
| DirectX 12        | Hell no        |