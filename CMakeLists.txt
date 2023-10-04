cmake_minimum_required(VERSION ${CMAKE_VERSION})

project(BRGL)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(
 src
 ${SDL2_INCLUDE_DIRS}
 ${GLEW_INCLUDE_DIRS}
 ${OPENGL_INCLUDE_DIRS}
)

add_library(brgl
 src/brgl/brgl.cpp
)

add_executable(demo
 src/demo/main.cpp
)

target_link_libraries(
    demo brgl ${SDL2_LIBRARIES} GLEW::glew ${OPENGL_LIBRARIES}
)