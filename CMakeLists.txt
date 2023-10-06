cmake_minimum_required(VERSION ${CMAKE_VERSION})

project(BRGL)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
include_directories(
 src/
 ${SDL2_INCLUDE_DIRS}
 ${GLEW_INCLUDE_DIRS}
 ${OPENGL_INCLUDE_DIRS}
 ${GLM_INCLUDE_DIRS}
)

add_library(brgl
 src/brgl/brgl.cpp
)
set_property(TARGET brgl PROPERTY CXX_STANDARD 17)
target_link_libraries(
 brgl ${SDL2_LIBRARIES} GLEW::glew ${OPENGL_LIBRARIES} ${GLM_LIBRARIES}
)

add_executable(brgldemo
 src/demo/main.cpp
 src/demo/demo.cpp
)
set_property(TARGET brgldemo PROPERTY CXX_STANDARD 17)
target_link_libraries(
 brgldemo brgl 
)