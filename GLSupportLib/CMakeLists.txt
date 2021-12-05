cmake_minimum_required (VERSION 3.8)


add_library (glSupportLib "src/Initializer.cpp" "include/Window.h" "src/Window.cpp" "include/Buffer.h"  "include/ShaderProgram.h" "src/ShaderProgram.cpp" "src/Buffer.cpp")
target_include_directories(glSupportLib PUBLIC "include" "../External/glm" "../External/tinygltf" "../External/stl_reader")
target_link_libraries(glSupportLib PUBLIC glad glfw)
set_property(TARGET glSupportLib PROPERTY CXX_STANDARD 17)