# AdvancedRaymarching
Advanced raymarching implementation based upon simple engine that encapsulates SDL2 and OpenGL functions.  
Engine part is 100% documented. Feel free to read, understand and edit it.
## Requirements
* `OpenGL` capable video card;
* `C++11` capable compiler.
## Compilation
### Dependencies
Strong dependencies(Needed to compile Engine):
`GLEW`, `GLM`.  
Weak dependencies(User interface implementation defined):
`SDL2`.
### Dependency installation on ubuntu
`sudo apt install -y libglm-dev libglew-dev libsdl2-dev`
### Compilation
```
mkdir build
cd build
cmake ..
make -j
```  
Everything should be inside `build` directory.

## Engine documentation generation
`doxygen Doxyfile`  
Everything should be inside `Documentation` folder.  
Now open `./Documentation/html/index.html`.
## Supported systems
| System name   | Support       | Tested        |
| ------------- | ------------- | ------------- |
| Ubuntu        | Yes           | Yes           |
| Other linux   | Should work   | No            |
| MacOS         | Should work   | No            |
| Other unix    | Maybe         | No            |
| Windows       | No            | No            |