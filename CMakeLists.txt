# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set project name and specify the language
project(GLVR)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Include directories for glad, GLFW, and OpenGL headers
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIR}
)

# Add the directory containing GLFW3
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Add the source file for the glad implementation
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/include/glad.c)

# Add the executable target for your project
add_executable(GLVR ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Link the glad library, GLFW3, and OpenGL libraries
target_link_libraries(GLVR glad glfw3 ${OPENGL_LIBRARIES})
