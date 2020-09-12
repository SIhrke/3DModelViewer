cmake_minimum_required (VERSION 3.8)


add_library (glSupportLib "src/Initializer.cpp" "include/Window.h" "src/Window.cpp")
target_include_directories(glSupportLib PUBLIC "include")
target_link_libraries(glSupportLib PUBLIC glad glfw)