add_executable(exampleSimple
        ${EXAMPLES_FOLDER}/simple/src/main.cpp
        ${EXAMPLES_FOLDER}/simple/src/EntryPoint.cpp
        ${EXAMPLES_FOLDER}/simple/src/states/MainState.cpp
        )
target_include_directories(exampleSimple
        PUBLIC
        ${EXAMPLES_FOLDER}/simple
        )

target_compile_features(exampleSimple PUBLIC cxx_std_17)
set_target_properties(exampleSimple PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(exampleSimple
        PRIVATE
        vanadium::vanadium)
