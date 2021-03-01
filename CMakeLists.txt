cmake_minimum_required(VERSION 3.16)
project(vanadium)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")


set(VENDOR_FOLDER vanadium/vendor)

set(VANADIUM_SOURCES
        ./vanadium/src/core/StateStack.cpp
        ./vanadium/src/core/Log.cpp
        ./vanadium/src/core/Window.cpp
        ./vanadium/src/core/Timer.cpp
        ./vanadium/src/core/EventProvider.cpp
        ./vanadium/src/core/IO.cpp
        ./vanadium/src/core/Application.cpp
        ./vanadium/src/core/Stopwatch.cpp
        ./vanadium/src/platform/default/DefaultWindow.cpp
        ./vanadium/src/platform/default/DefaultStopwatch.cpp
        ./vanadium/src/platform/default/DefaultKeyCodes.cpp
        ./vanadium/src/platform/default/DefaultEventProvider.cpp
        ./vanadium/src/platform/default/DefaultTimer.cpp
        ./vanadium/src/platform/default/DefaultIO.cpp
        vanadium/src/platform/opengl/OpenGLVertexBuffer.cpp
        ./vanadium/src/platform/opengl/OpenGLShader.cpp
        ./vanadium/src/platform/opengl/OpenGLTexture.cpp
        ./vanadium/src/platform/opengl/OpenGLRenderApi.cpp
        ./vanadium/src/platform/opengl/OpenGLFramebuffer.cpp
        ./vanadium/src/platform/opengl/OpenGLVertexArray.cpp
        ./vanadium/src/render/VertexArray.cpp
        ./vanadium/src/render/Framebuffer.cpp
        ./vanadium/src/render/Texture.cpp
        ./vanadium/src/render/Shader.cpp
        vanadium/src/render/VertexBuffer.cpp
        ./vanadium/src/render/RenderApi.cpp
        ./vanadium/src/stateCommands/PopAllStatesCommand.cpp
        ./vanadium/src/stateCommands/PushStateCommand.cpp
        ./vanadium/src/stateCommands/PopStateCommand.cpp
        )

set(VANADIUM_HEADERS
        ./vanadium/src/core/Animation.h
        ./vanadium/src/core/StringHash.h
        ./vanadium/src/core/Types.h
        ./vanadium/src/core/Application.h
        ./vanadium/src/core/StateStack.h
        ./vanadium/src/core/SanityChecker.h
        ./vanadium/src/core/Exceptions.h
        ./vanadium/src/core/KeyCodes.h
        ./vanadium/src/core/Window.h
        ./vanadium/src/core/Timer.h
        ./vanadium/src/core/EventProvider.h
        ./vanadium/src/core/Log.h
        ./vanadium/src/core/IO.h
        ./vanadium/src/core/Stopwatch.h
        vanadium/src/core/interfaces/Command.h
        ./vanadium/src/core/State.h
        ./vanadium/src/core/Assert.h
        ./vanadium/src/include/vanadium/Vanadium.h
        ./vanadium/src/platform/default/DefaultIO.h
        ./vanadium/src/platform/default/DefaultKeyCodes.h
        ./vanadium/src/platform/default/DefaultStopwatch.h
        ./vanadium/src/platform/default/DefaultTimer.h
        ./vanadium/src/platform/default/DefaultIncludes.h
        ./vanadium/src/platform/default/DefaultWindow.h
        ./vanadium/src/platform/default/DefaultEventProvider.h
        vanadium/src/platform/opengl/OpenGLVertexBuffer.h
        ./vanadium/src/platform/opengl/OpenGLFramebuffer.h
        ./vanadium/src/platform/opengl/OpenGLCall.h
        ./vanadium/src/platform/opengl/OpenGLTexture.h
        ./vanadium/src/platform/opengl/OpenGLShader.h
        ./vanadium/src/platform/opengl/OpenGLRenderApi.h
        ./vanadium/src/platform/opengl/OpenGLIncludes.h
        ./vanadium/src/platform/opengl/OpenGLVertexArray.h
        ./vanadium/src/render/Shader.h
        ./vanadium/src/render/RenderApi.h
        ./vanadium/src/render/Framebuffer.h
        vanadium/src/render/VertexBuffer.h
        ./vanadium/src/render/VertexArray.h
        ./vanadium/src/render/Texture.h
        ./vanadium/src/stateCommands/PopStateCommand.h
        ./vanadium/src/stateCommands/PushStateCommand.h
        ./vanadium/src/stateCommands/PopAllStatesCommand.h
        ./vanadium/src/event/Event.h
        ./vanadium/src/event/KeyEvent.h
        ./vanadium/src/event/WindowEvent.h
        ./vanadium/src/event/MouseEvent.h
        ./vanadium/src/event/EventDispatcher.h
        )

set(EXAMPLE_FILES
        ./example/states/CustomState.h

        ./example/states/CustomState.cpp
        ./example/main.cpp
        )

set(TINYXML2_SOURCES ${VENDOR_FOLDER}/tinyxml2/tinyxml2.cpp vanadium/src/stateCommands/ReplaceStateCommand.cpp vanadium/src/stateCommands/ReplaceStateCommand.h vanadium/src/core/Random.h vanadium/src/platform/default/DefaultRandom.h vanadium/src/platform/default/DefaultRandom.cpp vanadium/src/core/State.cpp vanadium/src/vfs/Exceptions.h vanadium/src/vfs/FileStream.cpp vanadium/src/vfs/FileStream.h vanadium/src/platform/default/DefaultDialogs.cpp vanadium/src/scene/Mesh.cpp)

add_executable(${PROJECT_NAME}
        ${VANADIUM_SOURCES}
        ${VANADIUM_HEADERS}
        ${EXAMPLE_FILES}
        ${TINYXML2_SOURCES}
        vanadium/src/core/interfaces/Hashable.h
        vanadium/src/vfs/Entry.h vanadium/src/vfs/Entry.cpp vanadium/src/vfs/Vfs.cpp vanadium/src/vfs/Vfs.h vanadium/src/core/Dialogs.h vanadium/src/platform/default/DefaultDialogs.h vanadium/src/scene/Camera.cpp vanadium/src/scene/Camera.h vanadium/src/render/IndexBuffer.cpp vanadium/src/render/IndexBuffer.h vanadium/src/platform/opengl/OpenGLIndexBuffer.cpp vanadium/src/platform/opengl/OpenGLIndexBuffer.h vanadium/src/scene/FpsCamera.cpp vanadium/src/scene/FpsCamera.h vanadium/src/scene/Mesh.h)

# Somewhat slows compilation a lot.
#target_precompile_headers(vanadium
#        PUBLIC
#        ${VANADIUM_HEADERS}
#        )

if (APPLE)
    set(CMAKE_MACOSX_RPATH 1)
endif()

set(BUILD_SHARED_LIBS OFF)
#set(PHYSFS_BUILD_SHARED FALSE)
set(PHYSFS_BUILD_TEST FALSE)
add_subdirectory(${VENDOR_FOLDER}/physfs ./build/physfs)
add_subdirectory(${VENDOR_FOLDER}/yaml-cpp ./build/yaml-cpp)
add_subdirectory(${VENDOR_FOLDER}/spdlog ./build/spdlog)
add_subdirectory(${VENDOR_FOLDER}/glm ./build/glm)
if(SYSTEM_SDL STREQUAL 1)
    check_include_file(SDL2/SDL.h SDL_INCLUDE_INSIDE_FOLDER_EXISTS)
    check_include_file(SDL.h SDL_INCLUDE_OUTSIDE_FOLDER_EXISTS)
    if(SDL_INCLUDE_INSIDE_FOLDER_EXISTS STREQUAL 1)
        include_directories(SDL)
    elseif(SDL_INCLUDE_OUTSIDE_FOLDER_EXISTS STREQUAL 1)

    else()
        message(SEND_ERROR "SDL2 header not found.")
    endif()
else ()
    # Todo: Remove it before release build.
    set(SDL_STATIC ON)
    set(SDL_SHARED OFF)
    add_subdirectory(${VENDOR_FOLDER}/SDL ./build/sdl2)
    include_directories(
            ${VENDOR_FOLDER}/SDL/include
    )
endif()
include_directories(
        vanadium/src
        ${VENDOR_FOLDER}/stb
        ${VENDOR_FOLDER}/tinyxml2
        ${VENDOR_FOLDER}/physfs/src
)

# See SDL2 CMakeLists.txt
if(WIN32)
    # Wot?
    if(NOT WINDOWS)
        target_compile_definitions(${PROJECT_NAME} PUBLIC VANADIUM_PLATFORM_WINDOWS)
    endif()
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC VANADIUM_PLATFORM_LINUX)
elseif(APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC VANADIUM_PLATFORM_MACOS)
endif()
target_compile_definitions(${PROJECT_NAME} PUBLIC VANADIUM_RENDERAPI_OPENGL VANADIUM_DEBUG VANADIUM_OLD_CORE_OPENGL)


if (VANADIUM_PLATFORM_MACOS)
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME}
            ${OPENGL_LIBRARIES}
            SDL2main
            SDL2-static
            physfs-static
            yaml-cpp
            spdlog
            glm
            )
else ()
    #set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "./")
    target_link_libraries(${PROJECT_NAME}
            GL
            GLEW
            SDL2
            physfs
            yaml-cpp
            spdlog
            glm
            )
endif ()
