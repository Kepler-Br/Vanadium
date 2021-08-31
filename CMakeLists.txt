cmake_minimum_required(VERSION 3.7...3.20)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif ()

set(VENDOR_FOLDER external)
set(EXAMPLES_FOLDER example)

project(vanadium
        VERSION 0.2.5
        DESCRIPTION "Vanadium:: game engine"
        LANGUAGES CXX
        )

string(TIMESTAMP BUILD_TIMESTAMP %s UTC)
string(TIMESTAMP BUILD_DATE_STRING "%Y-%m-%d %H:%M" UTC)

option(MAKE_LOGS "Determine whether engine should make logs." ON)
option(BUILD_EXAMPLES "Build examples or not." OFF)

message(STATUS "Build vanadium version: ${PROJECT_VERSION}")

include(CheckTypeSize)
include(cmake/projectSources.cmake)

check_type_size(size_t SIZEOF_SIZE_T LANGUAGE CXX)
if (NOT SIZEOF_SIZE_T EQUAL 8)
    message(FATAL_ERROR "size_t is not 8(" ${SIZEOF_SIZE_T} ") bytes or not found! We need it to be 8 to support string hashing")
endif ()

configure_file(
        "cmake/Version.h.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/Version.h"
)

add_library(vanadium
        STATIC
        ${IMGUI_SOURCES}
        ${VANADIUM_SOURCES}
        ${VANADIUM_HEADERS}
        src/graphics/RendererApiEnum.h src/graphics/RendererApiEnum.cpp)

add_library(vanadium::vanadium ALIAS vanadium)

if (APPLE)
    set(PLATFORM_MACOS TRUE)
    target_compile_definitions(vanadium
            PUBLIC
            VANADIUM_PLATFORM_MACOS
            )
elseif (UNIX)
    if (CMAKE_SYSTEM_NAME MATCHES ".*Linux")
        set(PLATFORM_LINUX TRUE)
        target_compile_definitions(vanadium
                PUBLIC
                VANADIUM_PLATFORM_LINUX
                )
    elseif ()
        message(FATAL_ERROR "Not a supported target OS!")
    endif ()
elseif (WIN32)
    set(PLATFORM_WINDOWS TRUE)
    target_compile_definitions(vanadium
            PUBLIC
            VANADIUM_PLATFORM_WINDOWS
            )
else ()
    message(FATAL_ERROR "Not a supported target OS!")
endif ()

target_include_directories(vanadium
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${VENDOR_FOLDER}/stb"
        "${VENDOR_FOLDER}/imgui"
        "${VENDOR_FOLDER}/physfs/src"
        "${VENDOR_FOLDER}/xoshiro-cpp"
        "${VENDOR_FOLDER}/earcuthpp"
        )

target_compile_features(vanadium PUBLIC cxx_std_17)
set_target_properties(vanadium PROPERTIES CXX_EXTENSIONS OFF)

set(BUILD_STATIC_LIBS ON CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")

set(YAML_BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "")
set(YAML_CPP_INSTALL OFF CACHE BOOL "")
set(YAML_MSVC_SHARED_RT OFF CACHE BOOL "")
add_subdirectory(${VENDOR_FOLDER}/yaml-cpp)
add_subdirectory(${VENDOR_FOLDER}/spdlog)
add_subdirectory(${VENDOR_FOLDER}/json)
add_subdirectory(${VENDOR_FOLDER}/tinyxml2)
add_subdirectory(${VENDOR_FOLDER}/fmt)
set(PHYSFS_BUILD_SHARED FALSE CACHE BOOL "")
set(PHYSFS_BUILD_TEST FALSE CACHE BOOL "")
add_subdirectory(${VENDOR_FOLDER}/physfs)
set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "")
set(BGFX_BUILD_TOOLS OFF CACHE BOOL "")
set(BGFX_INSTALL_EXAMPLES OFF CACHE BOOL "")
set(BGFX_INSTALL OFF CACHE BOOL "")
add_subdirectory(${VENDOR_FOLDER}/bgfx.cmake)
add_subdirectory(${VENDOR_FOLDER}/glm)

find_package(SDL2 REQUIRED)
if (TARGET SDL2::SDL2)
    target_link_libraries(vanadium
            PUBLIC
            SDL2::SDL2-static
            )
else ()
    target_link_libraries(vanadium
            PUBLIC
            SDL2-static
            )
endif ()
target_link_libraries(vanadium
        PUBLIC
        yaml-cpp::yaml-cpp
        spdlog::spdlog
        glm::glm
        nlohmann_json::nlohmann_json
        fmt::fmt
        tinyxml2
        bgfx
        bx
        bimg
        physfs-static
        )

if (NOT MAKE_LOGS)
    target_compile_definitions(vanadium
            PUBLIC
            VANADIUM_TURN_OFF_LOGS
            )
endif ()

if (BUILD_EXAMPLES)
    include(${EXAMPLES_FOLDER}/fractol/fractol.cmake)
endif ()
