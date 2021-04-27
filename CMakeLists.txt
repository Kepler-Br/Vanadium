cmake_minimum_required(VERSION 3.7...3.20)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif ()

if (APPLE)
    set(PLATFORM_MACOS TRUE)
elseif (UNIX)
    if (CMAKE_SYSTEM_NAME MATCHES ".*Linux")
        set(PLATFORM_LINUX TRUE)
    elseif ()
        message(FATAL_ERROR "Not a supported target OS!")
    endif ()
else ()
    message(FATAL_ERROR "Not a supported target OS!")
endif ()

include(cmake/projectSources.cmake)

project(vanadium
        VERSION 0.2.5
        DESCRIPTION "Vanadium:: game engine"
        LANGUAGES CXX
        )

option(MAKE_LOGS "Determine whether engine should make logs." ON)

message(STATUS "Build vanadium version: ${PROJECT_VERSION}")

include(CheckTypeSize)

check_type_size("std::size_t" SIZEOF_SIZE_T LANGUAGE CXX)
if (NOT SIZEOF_SIZE_T EQUAL 8)
    message(FATAL_ERROR "size_t is not 8 bytes! We need it to be 8 to support string hashing")
endif ()

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
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vanadium"
        "${VENDOR_FOLDER}/earcuthpp"
        )

target_include_directories(vanadium PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_BINARY_DIR}/include"
        "${VENDOR_FOLDER}/physfs/src"
        "${VENDOR_FOLDER}/stb"
        "${VENDOR_FOLDER}/imgui"
        )

target_compile_features(vanadium PUBLIC cxx_std_17)
set_target_properties(vanadium PROPERTIES CXX_EXTENSIONS OFF)

set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_LIBS ON)
add_subdirectory(${VENDOR_FOLDER}/physfs)
add_subdirectory(${VENDOR_FOLDER}/yaml-cpp)
add_subdirectory(${VENDOR_FOLDER}/spdlog)
add_subdirectory(${VENDOR_FOLDER}/glm)
add_subdirectory(${VENDOR_FOLDER}/json)
add_subdirectory(${VENDOR_FOLDER}/tinyxml2)
add_subdirectory(${VENDOR_FOLDER}/fmt)

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
        )

target_link_libraries(vanadium
        PRIVATE
        physfs
        )

if (PLATFORM_MACOS)
    target_compile_definitions(vanadium
            PUBLIC
            VANADIUM_PLATFORM_MACOS)
elseif (PLATFORM_LINUX)
    target_compile_definitions(vanadium
            PUBLIC
            VANADIUM_PLATFORM_LINUX)
else ()
    message(FATAL_ERROR "Not a supported target OS!")
endif ()

set(RENDER_API "OpenGL" CACHE STRING "")

if (RENDER_API STREQUAL "OpenGL")
    target_compile_definitions(vanadium
            PUBLIC
            VANADIUM_RENDERAPI_OPENGL
            )
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME}
            PRIVATE
            OpenGL::GL
            )
    if (PLATFORM_LINUX)
        find_package(GLEW REQUIRED)
        target_link_libraries(${PROJECT_NAME}
                PRIVATE
                GLEW::GLEW
                )
    endif ()
else ()
    message(FATAL_ERROR "Not a supported render API specified!")
endif ()

if (NOT MAKE_LOGS)
    target_compile_definitions(vanadium
            PUBLIC
            VANADIUM_TURN_OFF_LOGS)
endif ()
