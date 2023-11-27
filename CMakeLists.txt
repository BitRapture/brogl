cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(BRGL)

if(WIN32)
    string(TOLOWER "${CMAKE_SYSTEM_NAME}" PLATFORM)
    string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" COMP)
    string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" ARCH)

    include_directories(
        src
        ${PROJECT_SOURCE_DIR}/contrib/${PLATFORM}-${COMP}-${ARCH}/include
    )
    link_directories(
        ${PROJECT_SOURCE_DIR}/contrib/${PLATFORM}-${COMP}-${ARCH}/lib
    )
    if(MSVC)
        set(LIBGL opengl32)
        set(LIBGLEW glew32s)
        add_definitions(-DGLEW_STATIC)
    elseif(MINGW)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s -static")
        set(LIBGL opengl32)
        set(LIBGLEW glew32)
        add_definitions(-DGLEW_STATIC)
    endif()
else()
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)

    include_directories(
        src
        ${GLEW_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
    )
    set(LIBGL ${OPENGL_LIBRARIES})
    set(LIBGLEW ${GLEW_LIBRARIES})
endif()


add_library(brgl
 src/brgl/boilerplate.cpp 
 
 src/brgl/boilerplate.h
 src/brgl/brgl.h
)
set_property(TARGET brgl PROPERTY CXX_STANDARD 17)
target_link_libraries(
 brgl ${LIBGL} ${LIBGLEW}
)

#add_executable(brgldemo
# src/demo/main.cpp
# src/demo/demo.cpp
#
# src/demo/demo.h
#)
#set_property(TARGET brgldemo PROPERTY CXX_STANDARD 17)
#target_link_libraries(
# brgldemo brgl 
#)