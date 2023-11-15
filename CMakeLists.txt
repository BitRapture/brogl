cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(BRGL)

string(TOLOWER "${CMAKE_SYSTEM_NAME}" PLATFORM)
string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" COMP)
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" ARCH)

add_definitions(-DSDL_MAIN_HANDLED)

include_directories(
 src
 ${PROJECT_SOURCE_DIR}/contrib/${PLATFORM}-${COMP}-${ARCH}/include
)

link_directories(
 ${PROJECT_SOURCE_DIR}/contrib/${PLATFORM}-${COMP}-${ARCH}/lib
)

if(MSVC)
    set(LIBSDL2 SDL2-static)
    set(LIBGL opengl32)
    set(LIBGLEW glew32s)
    add_definitions(-DGLEW_STATIC)
elseif(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s -static")
    set(LIBSDL2 SDL2)
    set(LIBGL opengl32)
    set(LIBGLEW glew32)
    add_definitions(-DGLEW_STATIC)
else()
    set(LIBSDL2 SDL2)
    set(LIBGL GL)
    set(LIBGLEW GLEW)
endif()

add_library(brgl
 src/brgl/boilerplate.cpp 
 src/brgl/primitives.cpp
 
 src/brgl/boilerplate.h
 src/brgl/primitives.h
 src/brgl/brgl.h
)
set_property(TARGET brgl PROPERTY CXX_STANDARD 17)
target_link_libraries(
 brgl ${LIBGL} ${LIBGLEW} ${LIBSDL2}
)

add_executable(brgldemo
 src/demo/main.cpp
 src/demo/demo.cpp

 src/demo/demo.h
)
set_property(TARGET brgldemo PROPERTY CXX_STANDARD 17)
target_link_libraries(
 brgldemo brgl 
)