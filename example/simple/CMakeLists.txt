cmake_minimum_required(VERSION 3.7...3.20)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif ()

project(exampleSimple
        DESCRIPTION "Simple Vanadium:: usage example"
        LANGUAGES CXX
        )

add_executable(exampleSimple
        main.cpp
        )

target_compile_features(exampleSimple PUBLIC cxx_std_17)
set_target_properties(exampleSimple PROPERTIES CXX_EXTENSIONS OFF)
