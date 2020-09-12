# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("3DModelViewer")
add_subdirectory(External/glew/build/cmake)

add_subdirectory(External/glfw)
# Include sub-projects.
add_subdirectory ("3DModelViewer")
