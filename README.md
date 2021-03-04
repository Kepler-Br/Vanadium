# Vanadium::
**V** stands for *Vanadium::*  
**Todo**: Think about description.  
**Todo**: Use GLAD instead. GLEW leaks.  

## Requirements
* `OpenGL 3.X and >` capable video card;
* `C++17` capable compiler; Possible to use `C++14` compiler but without filesystem access.
* [Cmake](https://cmake.org/) to compile the project.
## How to clone
`git clone --recursive https://github.com/Kepler-Br/Vanadium`  
If you have already cloned this without submodules, use this:  
`git submodule update --init --recursive`

## Compilation
### Dependencies
| Name          | Licence       | Remark          | OS            |
| ------------- | ------------- | --------------- | ------------- |
| [GLEW](https://github.com/nigels-com/glew) | [Multi licenced](https://github.com/nigels-com/glew/blob/master/LICENSE.txt) | OpenGL bindings | Linux/Windows |
| [SDL2](https://github.com/libsdl-org/SDL) | [zlib](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt) | If you want to compile using system lib | All |

### Dependency installation on Ubuntu/Debian
Without SDL2 (Compile using SDL2 sources):  
`apt install cmake libglew-dev`  
With SDL2:  
`apt install cmake libsdl2-dev libglew-dev`  
**Todo**: Try to install this on bare bones ubuntu.

### Dependency installation on MacOS
Without SDL2 (Compile using SDL2 sources):  
`brew install cmake`  
With SDL2:  
`brew install cmake sdl2`  

### Dependencies included as sources or submodules

| Name          | Licence       |
| ------------- | ------------- |
| [stb](https://github.com/nothings/stb) | [MIT/Public Domain](https://github.com/nothings/stb/blob/master/LICENSE) |
| [GLM](https://github.com/g-truc/glm) | [Modified MIT](https://github.com/g-truc/glm/blob/master/manual.md#section0)|
| [spdlog](https://github.com/gabime/spdlog) | [MIT](https://github.com/gabime/spdlog/blob/v1.x/LICENSE)|
| [yaml-cpp](https://github.com/jbeder/yaml-cpp) | [MIT](https://github.com/jbeder/yaml-cpp/blob/master/LICENSE) |
| [ImGUI](https://github.com/ocornut/imgui) | [MIT](https://github.com/ocornut/imgui/blob/master/LICENSE.txt) |
| [tinyxml2](https://github.com/leethomason/tinyxml2) | [zlib](https://github.com/leethomason/tinyxml2/blob/master/LICENSE.txt)|
| [PhysicsFS](https://icculus.org/physfs/) | [zlib](https://hg.icculus.org/icculus/physfs/raw-file/tip/LICENSE.txt) |
| [SDL2](https://github.com/libsdl-org/SDL) | [zlib](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt) |
### Compilation
#### Flags
| Flag | Meaning |
| ------------- | ------------- |
| -DSYSTEM_SDL=1 | Use system installed SDL2 library |
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
| ~~DirectX 11~~        | ~~Distant future~~ |
| ~~DirectX 12~~        | ~~Hell no~~        |