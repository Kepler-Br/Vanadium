cmake_minimum_required(VERSION 3.14...3.20)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

include(cmake/projectSources.cmake)

project(vanadium
        VERSION 0.5.0
        DESCRIPTION "Vanadium:: game engine"
        LANGUAGES CXX
        )

message(STATUS "Build vanadium version: ${PROJECT_VERSION}")

configure_file(
        "cmake/Version.h.in"
        "${CMAKE_CURRENT_BINARY_DIR}/include/vanadium/Version.h"
)

add_library(vanadium STATIC
        ${IMGUI_SOURCES}
        ${VANADIUM_SOURCES}
        ${VANADIUM_HEADERS}
        )

add_library(vanadium::vanadium ALIAS vanadium)

target_include_directories(vanadium PRIVATE
        include/vanadium
        ${VENDOR_FOLDER}/earcuthpp
        )

target_include_directories(vanadium PUBLIC
        include
        "${CMAKE_CURRENT_BINARY_DIR}/include"
        "${VENDOR_FOLDER}/physfs/src"
        "${VENDOR_FOLDER}/stb"
        )

target_compile_features(vanadium PUBLIC cxx_std_17)
set_target_properties(vanadium PROPERTIES CXX_EXTENSIONS OFF)

add_subdirectory(${VENDOR_FOLDER}/physfs)
add_subdirectory(${VENDOR_FOLDER}/yaml-cpp)
add_subdirectory(${VENDOR_FOLDER}/spdlog)
add_subdirectory(${VENDOR_FOLDER}/glm)
add_subdirectory(${VENDOR_FOLDER}/json)
add_subdirectory(${VENDOR_FOLDER}/tinyxml2)
add_subdirectory(${VENDOR_FOLDER}/fmt)

find_package(SDL2 REQUIRED)
target_link_libraries(vanadium
        PUBLIC
        SDL2::SDL2
        physfs
        yaml-cpp::yaml-cpp
        spdlog::spdlog
        glm::glm
        nlohmann_json::nlohmann_json
        fmt::fmt
        tinyxml2
        )

set(RENDER_API "OpenGL" CACHE STRING "")

if (RENDER_API STREQUAL "OpenGL")
    target_compile_definitions(vanadium
            PUBLIC
            VANADIUM_RENDERAPI_OPENGL
            VANADIUM_OLD_CORE_OPENGL)
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
            OpenGL::GL
            )
else ()
    message(FATAL_ERROR "Not supported render API specified!")
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(vanadium
            PUBLIC
            VANADIUM_PLATFORM_MACOS)
else ()
    message(FATAL_ERROR "Not supported target OS!")
endif ()