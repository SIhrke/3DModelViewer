# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("3DModelViewer")

add_subdirectory("GLSupportLib")
add_subdirectory(External/glad_generated)
add_subdirectory(External/glfw)
add_subdirectory(External/glTF-SDK)

# Include sub-projects.
add_subdirectory ("3DModelViewer")
