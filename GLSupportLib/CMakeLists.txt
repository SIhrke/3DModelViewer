cmake_minimum_required (VERSION 3.8)


add_library (glSupportLib "src/Initializer.cpp" "include/Window.h" "src/Window.cpp" "include/Buffer.h" "src/Buffer.cpp" "include/ShaderProgram.h" "src/ShaderProgram.cpp")
target_include_directories(glSupportLib PUBLIC "include" "../External/glm")
target_link_libraries(glSupportLib PUBLIC glad glfw)