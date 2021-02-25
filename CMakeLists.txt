cmake_minimum_required(VERSION 3.16)
project(vanadium)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

file(GLOB_RECURSE YAML_CPP_SOURCES vanadium/vendor/yaml-cpp/src/*.cpp)

include_directories(
        vanadium/src
        vanadium/vendor/yaml-cpp/include
        vanadium/vendor/spdlog/include
        vanadium/vendor/stb
        vanadium/vendor/tinyxml2
        vanadium/vendor/glm
)

add_executable(vanadium
        example/main.cpp

        ${YAML_CPP_SOURCES}

        vanadium/vendor/tinyxml2/tinyxml2.cpp

        vanadium/src/core/Application.cpp
        vanadium/src/core/Application.h
        vanadium/src/core/Window.h
        vanadium/src/event/Event.h
        vanadium/src/event/KeyEvent.h
        vanadium/src/core/KeyCodes.h
        vanadium/src/event/WindowEvent.h
        vanadium/src/event/MouseEvent.h
        vanadium/src/event/EventDispatcher.h
        vanadium/src/include/vanadium/Vanadium.h
        vanadium/src/core/Window.cpp
        vanadium/src/platform/default/DefaultWindow.cpp
        vanadium/src/platform/default/DefaultWindow.h
        vanadium/src/core/EventProvider.h
        vanadium/src/core/EventProvider.cpp
        vanadium/src/platform/default/DefaultEventProvider.cpp
        vanadium/src/platform/default/DefaultEventProvider.h
        vanadium/src/core/Stopwatch.h
        vanadium/src/core/Stopwatch.cpp
        vanadium/src/platform/default/DefaultStopwatch.cpp
        vanadium/src/platform/default/DefaultStopwatch.h
        vanadium/src/core/StateStack.cpp
        vanadium/src/core/StateStack.h
        vanadium/src/core/State.h
        vanadium/src/core/Command.h
        vanadium/src/stateCommands/PopStateCommand.cpp
        vanadium/src/stateCommands/PopStateCommand.h
        vanadium/src/stateCommands/PushStateCommand.cpp
        vanadium/src/stateCommands/PushStateCommand.h
        vanadium/src/stateCommands/PopAllStatesCommand.cpp
        vanadium/src/stateCommands/PopAllStatesCommand.h
        vanadium/src/core/Timer.h
        vanadium/src/core/Timer.cpp
        vanadium/src/platform/default/DefaultTimer.cpp
        vanadium/src/platform/default/DefaultTimer.h
        vanadium/src/core/Animation.h
        vanadium/src/render/RenderApi.h
        vanadium/src/platform/opengl/OpenGLRenderApi.h
        vanadium/src/platform/opengl/OpenGLRenderApi.cpp
        vanadium/src/platform/opengl/OpenGLIncludes.h
        vanadium/src/platform/opengl/OpenGLCall.h
        vanadium/src/render/Framebuffer.h
        vanadium/src/render/RenderApi.cpp
        vanadium/src/render/Framebuffer.cpp
        vanadium/src/render/Texture.cpp
        vanadium/src/render/Texture.h
        vanadium/src/platform/opengl/OpenGLTexture.cpp
        vanadium/src/platform/opengl/OpenGLTexture.h

        vanadium/src/core/Log.cpp
        vanadium/src/core/Log.h
        vanadium/src/core/IO.h
        vanadium/src/core/IO.cpp

        vanadium/src/platform/default/DefaultIO.cpp
        vanadium/src/platform/default/DefaultIO.h
        vanadium/src/platform/opengl/OpenGLShader.cpp
        vanadium/src/platform/opengl/OpenGLShader.h
        vanadium/src/platform/opengl/OpenGLFramebuffer.cpp
        vanadium/src/platform/opengl/OpenGLFramebuffer.h

        vanadium/src/render/Buffer.cpp
        vanadium/src/render/Buffer.h
        vanadium/src/render/VertexArray.cpp
        vanadium/src/render/VertexArray.h
        vanadium/src/render/Shader.h
        vanadium/src/render/Shader.cpp

        vanadium/src/platform/opengl/OpenGLBuffer.cpp
        vanadium/src/platform/opengl/OpenGLBuffer.h
        vanadium/src/platform/opengl/OpenGLVertexArray.cpp
        vanadium/src/platform/opengl/OpenGLVertexArray.h
        vanadium/src/core/Types.h
        vanadium/src/core/SanityChecker.h
        vanadium/src/platform/default/DefaultKeyCodes.h
        vanadium/src/core/Assert.h

        example/states/CustomState.cpp
        example/states/CustomState.h
        vanadium/src/core/Exceptions.h
        vanadium/src/core/StringHash.h
        vanadium/src/platform/default/DefaultKeyCodes.cpp)

# Somewhat slows compilation a lot.
#target_precompile_headers(vanadium
#        PUBLIC
#        ./vanadium/src/core/Animation.h
#        ./vanadium/src/core/Application.h
#        ./vanadium/src/core/Assert.h
#        ./vanadium/src/core/Command.h
#        ./vanadium/src/core/EventProvider.h
#        ./vanadium/src/core/IO.h
#        ./vanadium/src/core/KeyCodes.h
#        ./vanadium/src/core/Log.h
#        ./vanadium/src/core/SanityChecker.h
#        ./vanadium/src/core/State.h
#        ./vanadium/src/core/StateStack.h
#        ./vanadium/src/core/Stopwatch.h
#        ./vanadium/src/core/Timer.h
#        ./vanadium/src/core/Types.h
#        ./vanadium/src/core/Window.h
#        ./vanadium/src/core/Exceptions.h
#        ./vanadium/src/core/StringHash.h
#        ./vanadium/src/event/Event.h
#        ./vanadium/src/event/EventDispatcher.h
#        ./vanadium/src/event/KeyEvent.h
#        ./vanadium/src/event/MouseEvent.h
#        ./vanadium/src/event/WindowEvent.h
#        ./vanadium/src/include/vanadium/Vanadium.h
#        ./vanadium/src/platform/default/DefaultEventProvider.h
#        ./vanadium/src/platform/default/DefaultIO.h
#        ./vanadium/src/platform/default/DefaultKeyCodes.h
#        ./vanadium/src/platform/default/DefaultStopwatch.h
#        ./vanadium/src/platform/default/DefaultTimer.h
#        ./vanadium/src/platform/default/DefaultWindow.h
#        ./vanadium/src/platform/opengl/OpenGLBuffer.h
#        ./vanadium/src/platform/opengl/OpenGLCall.h
#        ./vanadium/src/platform/opengl/OpenGLFramebuffer.h
#        ./vanadium/src/platform/opengl/OpenGLIncludes.h
#        ./vanadium/src/platform/opengl/OpenGLRenderApi.h
#        ./vanadium/src/platform/opengl/OpenGLShader.h
#        ./vanadium/src/platform/opengl/OpenGLTexture.h
#        ./vanadium/src/platform/opengl/OpenGLVertexArray.h
#        ./vanadium/src/render/Buffer.h
#        ./vanadium/src/render/Framebuffer.h
#        ./vanadium/src/render/RenderApi.h
#        ./vanadium/src/render/Shader.h
#        ./vanadium/src/render/Texture.h
#        ./vanadium/src/render/VertexArray.h
#        ./vanadium/src/stateCommands/PopAllStatesCommand.h
#        ./vanadium/src/stateCommands/PopStateCommand.h
#        ./vanadium/src/stateCommands/PushStateCommand.h
#        )

target_compile_definitions(vanadium PUBLIC VANADIUM_PLATFORM_LINUX VANADIUM_RENDERAPI_OPENGL VANADIUM_DEBUG)
    
target_link_libraries(${PROJECT_NAME}
        GLEW
        GL
        SDL2
        )
