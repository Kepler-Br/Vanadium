add_executable(fractol
        ${EXAMPLES_FOLDER}/fractol/src/main.cpp
        ${EXAMPLES_FOLDER}/fractol/src/EntryPoint.cpp
        ${EXAMPLES_FOLDER}/fractol/src/states/MainState.cpp
        ${EXAMPLES_FOLDER}/fractol/src/imgui/ImGuiBgfxImpl.cpp
        )
target_include_directories(fractol
        PRIVATE
        ${EXAMPLES_FOLDER}/fractol
        )

target_compile_features(fractol PUBLIC cxx_std_17)
set_target_properties(fractol PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(fractol
        PRIVATE
        vanadium::vanadium
        )
