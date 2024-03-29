cmake_minimum_required(VERSION 3.7...3.20)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

set(VENDOR_FOLDER external)

set(IMGUI_SOURCES
        ${VENDOR_FOLDER}/imgui/imgui.cpp
        ${VENDOR_FOLDER}/imgui/imgui_draw.cpp
        ${VENDOR_FOLDER}/imgui/imgui_tables.cpp
        ${VENDOR_FOLDER}/imgui/imgui_widgets.cpp
        ${VENDOR_FOLDER}/imgui/backends/imgui_impl_sdl.cpp
        ${VENDOR_FOLDER}/imgui/imgui_demo.cpp
        )

set(VANADIUM_SOURCES
        src/core/application/Application.cpp
        src/core/application/ApplicationProperties.cpp
        src/core/application/stateCommands/PopAllStatesCommand.cpp
        src/core/application/stateCommands/PopStateCommand.cpp
        src/core/application/stateCommands/PushStateCommand.cpp
        src/core/application/stateCommands/ReplaceStateCommand.cpp
        src/core/application/State.cpp
        src/core/application/StateStack.cpp
        src/core/EventProvider.cpp
        src/core/Exceptions.cpp
        src/core/IO.cpp
        src/core/Log.cpp
        src/core/math/Math.cpp
        src/core/math/Random.cpp
        src/core/Stopwatch.cpp
        src/core/streams/InputMemoryBuffer.cpp
        src/core/streams/InputMemoryStream.cpp
        src/core/subsystems/BgfxCallback.cpp
        src/core/subsystems/BgfxSubsystem.cpp
        src/core/subsystems/LoggingSubsystem.cpp
        src/core/subsystems/SdlSubsystem.cpp
        src/core/subsystems/VfsSubsystem.cpp
        src/core/Timer.cpp
        src/core/Tools.cpp
        src/core/Window.cpp
        src/core/WindowProperties.cpp
        src/graphics/RendererApiEnum.cpp
        src/graphics/ShaderFactory.cpp
        src/platform/default/DefaultIO.cpp
        src/platform/default/DefaultStopwatch.cpp
        src/platform/default/DefaultTimer.cpp
        src/platform/sdl/SdlDialogs.cpp
        src/platform/sdl/SdlEventProvider.cpp
        src/platform/sdl/SdlKeyCodes.cpp
        src/platform/sdl/SdlWindow.cpp
        src/scene/Camera.cpp
        src/scene/Mesh.cpp
        src/scene/PositionCamera.cpp
        src/submodules/svg/Parser.cpp
        src/submodules/svg/Rasterizer.cpp
        src/vfs/FileStreamBuffer.cpp
        src/vfs/InputFileStream.cpp
        src/vfs/OutputFileStream.cpp
        src/vfs/Vfs.cpp
        )

set(VANADIUM_HEADERS
        src/core/Animation.h
        src/core/application/Application.h
        src/core/application/ApplicationProperties.h
        src/core/application/stateCommands/PopAllStatesCommand.h
        src/core/application/stateCommands/PopStateCommand.h
        src/core/application/stateCommands/PushStateCommand.h
        src/core/application/stateCommands/ReplaceStateCommand.h
        src/core/application/State.h
        src/core/application/StateStack.h
        src/core/Assert.h
        src/core/Dialogs.h
        src/core/EventProvider.h
        src/core/Exceptions.h
        src/core/interfaces/Command.h
        src/core/interfaces/Subsystem.h
        src/core/IO.h
        src/core/KeyCodes.h
        src/core/LogFormatters.h
        src/core/Log.h
        src/core/math/Math.h
        src/core/math/Random.h
        src/core/Stopwatch.h
        src/core/streams/InputMemoryBuffer.h
        src/core/streams/InputMemoryStream.h
        src/core/StringHash.h
        src/core/subsystems/BgfxCallback.h
        src/core/subsystems/BgfxSubsystem.h
        src/core/subsystems/LoggingSubsystem.h
        src/core/subsystems/SdlSubsystem.h
        src/core/subsystems/VfsSubsystem.h
        src/core/Timer.h
        src/core/Tools.h
        src/core/Types.h
        src/core/Version.h
        src/core/Window.h
        src/core/WindowProperties.h
        src/event/EventDispatcher.h
        src/event/Event.h
        src/event/KeyEvent.h
        src/event/MouseEvent.h
        src/event/WindowEvent.h
        src/graphics/RendererApiEnum.h
        src/graphics/ShaderFactory.h
        src/platform/default/DefaultIO.h
        src/platform/default/DefaultStopwatch.h
        src/platform/default/DefaultTimer.h
        src/platform/sdl/SdlDialogs.h
        src/platform/sdl/SdlEventProvider.h
        src/platform/sdl/SdlIncludes.h
        src/platform/sdl/SdlKeyCodes.h
        src/platform/sdl/SdlWindow.h
        src/scene/Camera.h
        src/scene/Mesh.h
        src/scene/PositionCamera.h
        src/submodules/svg/Commands.h
        src/submodules/svg/Document.h
        src/submodules/svg/Layer.h
        src/submodules/svg/Parser.h
        src/submodules/svg/Path.h
        src/submodules/svg/Rasterizer.h
        src/submodules/svg/Types.h
        src/Vanadium.h
        src/vfs/FileStreamBuffer.h
        src/vfs/InputFileStream.h
        src/vfs/OutputFileStream.h
        src/vfs/Vfs.h
        )
