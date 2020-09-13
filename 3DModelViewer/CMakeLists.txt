# CMakeList.txt : CMake project for 3DModelViewer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (3DModelViewer "main.cpp" )
target_link_libraries(3DModelViewer glSupportLib)
# TODO: Add tests and install targets if needed.
