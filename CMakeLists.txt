cmake_minimum_required(VERSION 3.16)
project(vanadium)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

include_directories(
        src
)

add_executable(vanadium
        example/main.cpp
        src/core/Application.cpp
        src/core/Application.h
        src/core/Window.h
        src/event/Event.h
        src/event/KeyEvent.h
        src/core/KeyCodes.h
        src/event/WindowEvent.h
        src/event/MouseEvent.h
        src/event/EventDispatcher.h
        src/Vanadium.h src/core/Window.cpp
        src/platform/default/DefaultWindow.cpp
        src/platform/default/DefaultWindow.h
        src/core/EventProvider.h
        src/core/EventProvider.cpp
        src/platform/default/DefaultEventProvider.cpp
        src/platform/default/DefaultEventProvider.h
        src/core/Stopwatch.h
        src/core/Stopwatch.cpp
        src/platform/default/DefaultStopwatch.cpp
        src/platform/default/DefaultStopwatch.h
        src/core/StateStack.cpp
        src/core/StateStack.h
        src/core/State.h
        src/core/Command.h src/stateCommands/PopStateCommand.cpp src/stateCommands/PopStateCommand.h src/stateCommands/PushStateCommand.cpp src/stateCommands/PushStateCommand.h src/stateCommands/PopAllStatesCommand.cpp src/stateCommands/PopAllStatesCommand.h src/core/Timer.h src/core/Timer.cpp src/platform/default/DefaultTimer.cpp src/platform/default/DefaultTimer.h src/core/Animation.h src/render/RenderApi.h src/platform/opengl/OpenGLRenderApi.h src/platform/opengl/OpenGLRenderApi.cpp src/platform/opengl/OpenGLIncludes.h src/platform/opengl/OpenGLCall.h src/render/Framebuffer.h src/render/RenderApi.cpp src/render/Framebuffer.cpp src/render/Texture2D.cpp src/render/Texture2D.h src/platform/opengl/OpenGLTexture2D.cpp src/platform/opengl/OpenGLTexture2D.h)

target_precompile_headers(vanadium
        PUBLIC
        src/core/Application.h
        src/core/EventProvider.h
        src/core/Window.h
        src/core/KeyCodes.h
        src/core/Stopwatch.h
        src/core/State.h
        src/core/Command.h
        src/core/StateStack.h
        src/core/Timer.h
        src/core/Stopwatch.h
        src/core/Animation.h

        src/event/Event.h
        src/event/KeyEvent.h
        src/event/WindowEvent.h
        src/event/MouseEvent.h
        src/event/EventDispatcher.h

        src/platform/default/DefaultEventProvider.h
        src/platform/default/DefaultStopwatch.h
        src/platform/default/DefaultWindow.h

        src/render/Framebuffer.h
        src/render/RenderApi.h

        src/stateCommands/PopAllStatesCommand.h
        src/stateCommands/PopStateCommand.h
        src/stateCommands/PushStateCommand.h
        )

target_compile_definitions(vanadium PUBLIC VANADIUM_PLATFORM_LINUX VANADIUM_RENDERAPI_OPENGL)
    
target_link_libraries(${PROJECT_NAME}
        GLEW
        SDL2
        GL
        ) 
