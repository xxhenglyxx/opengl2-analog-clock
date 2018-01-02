
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(analog-clock)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package(OpenGL)
find_package(GLUT)

find_library(COCOA Cocoa)

include_directories(
    include
    ${GLUT_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
)

add_executable(
    analog-clock
    src/main.cpp
    src/Clock.cpp
)

target_link_libraries(
    analog-clock
    ${OPENGL_LIBRARIES}
    ${COCOA_LIBRARIES}
    ${GLUT_LIBRARIES}
)