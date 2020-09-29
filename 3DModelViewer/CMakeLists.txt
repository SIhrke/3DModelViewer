# CMakeList.txt : CMake project for 3DModelViewer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
configure_file(fragmentShader.frag ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(vertexShader.vert ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
file(COPY ../Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add source to this project's executable.
add_executable (3DModelViewer "main.cpp" "Model.cpp")
target_link_libraries(3DModelViewer glSupportLib)
set_property(TARGET 3DModelViewer PROPERTY CXX_STANDARD 17)
# TODO: Add tests and install targets if needed.
