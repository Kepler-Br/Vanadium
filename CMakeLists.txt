cmake_minimum_required(VERSION 3.16)
project(vanadium)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

include_directories(
        .
)

add_executable(vanadium
        src/main.cpp
        src/core/Application.cpp
        src/core/Application.h
        src/core/Window.h
        src/event/Event.h
        src/event/KeyEvent.h
        src/core/KeyCodes.h
        src/event/WindowEvent.h
        src/event/MouseEvent.h
        src/event/EventDispatcher.h
        src/Vanadium.h src/core/Window.cpp src/platform/linux/LinuxWindow.cpp src/platform/linux/LinuxWindow.h)

target_precompile_headers(vanadium
        PUBLIC
        src/core/Application.h
        src/core/Window.h
        src/event/Event.h
        src/event/KeyEvent.h
        src/core/KeyCodes.h
        src/event/WindowEvent.h
        src/event/MouseEvent.h
        src/event/EventDispatcher.h
        )

target_compile_definitions(vanadium PUBLIC VANADIUM_PLATFORM_LINUX)
    
target_link_libraries(${PROJECT_NAME}
        GLEW
        SDL2
        GL
        ) 
