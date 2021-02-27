# Vanadium graphics engine
**Todo**: Think about description.
## Requirements
* `OpenGL 4.X` capable video card;
* `C++14` capable compiler.
## How to clone
`git clone --recursive https://github.com/Kepler-Br/Vanadium`  
If you have already cloned this without submodules, use this:  
`git submodule update --init --recursive`
## Compilation
### Dependencies
| Name          | Licence       |
| ------------- | ------------- |
| [GLEW](https://github.com/nigels-com/glew) | [Multi licenced](https://github.com/nigels-com/glew/blob/master/LICENSE.txt) |

### Dependency installation on ubuntu
**Todo**: Try to install this on bare bones ubuntu.
### Dependency installation on MacOS   
**Todo**: Compile and run it on MacOS.
### Dependencies included as sources or submodules
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
**WARNING!** No engine documentation right now.  
`doxygen Doxyfile`  
Everything should be inside `Documentation` folder.  
Now open `./Documentation/html/index.html`.
## Supported systems
| System name   | Support       | Runs          |
| ------------- | ------------- | ------------- |
| Ubuntu        | Yes           | Yes           |
| Other linux   | No            | Maybe         |
| MacOS         | No            | Yes           |
| Other unix    | No            | No            |
| Windows       | No            | No            |
| CYGWIN        | No            | No            |
