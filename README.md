# Vanadium graphics engine
**Todo**: Think about description.
## Requirements
* `OpenGL 4.X` capable video card;
* `C++14` capable compiler.
## Compilation
### Dependencies
`SDL2`. Might add it as a download script.  
Everything else is included as submodule.
### Dependency installation on ubuntu
**Todo**: Try to install this on bare bones ubuntu.    
```sudo apt install -y libsdl2-dev```
### Submodules
[GLEW](https://github.com/nigels-com/glew), 
[glm](https://github.com/g-truc/glm), 
[spdlog](https://github.com/gabime/spdlog), 
[stb](https://github.com/nothings/stb),
[tinyxml2](https://github.com/leethomason/tinyxml2),
[yaml-cpp](https://github.com/jbeder/yaml-cpp).
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
| System name   | Support       | Tested        |
| ------------- | ------------- | ------------- |
| Ubuntu        | Yes           | Yes           |
| Other linux   | Should work   | No            |
| MacOS         | Should work   | No            |
| Other unix    | Should work   | No            |
| Windows       | No            | No            |