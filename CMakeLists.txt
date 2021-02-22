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
        src/Vanadium.h src/core/Window.cpp src/platform/linux/LinuxWindow.cpp src/platform/linux/LinuxWindow.h src/core/EventProvider.h src/core/EventProvider.cpp src/platform/linux/LinuxEventProvider.cpp src/platform/linux/LinuxEventProvider.h src/core/Timer.h src/core/Timer.cpp src/platform/linux/LinuxTimer.cpp src/platform/linux/LinuxTimer.h src/core/StateStack.cpp src/core/StateStack.h src/core/State.h src/core/Command.h)

target_precompile_headers(vanadium
        PUBLIC
        src/core/Application.h
        src/core/EventProvider.h
        src/core/Window.h
        src/core/KeyCodes.h
        src/core/Timer.h
        src/core/State.h
        src/core/Command.h
        src/core/StateStack.h
        src/event/Event.h
        src/event/KeyEvent.h
        src/event/WindowEvent.h
        src/event/MouseEvent.h
        src/event/EventDispatcher.h

        src/platform/linux/LinuxEventProvider.h
        src/platform/linux/LinuxTimer.h
        src/platform/linux/LinuxWindow.h
        )

target_compile_definitions(vanadium PUBLIC VANADIUM_PLATFORM_LINUX)
    
target_link_libraries(${PROJECT_NAME}
        GLEW
        SDL2
        GL
        ) 
