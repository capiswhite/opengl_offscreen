#要求的Cmake最低版本
cmake_minimum_required(VERSION 3.2)
 
#工程名称
PROJECT(opengl_offscreen_test)

set(CMAKE_CXX_STANDARD 17)
set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 0)
set(APP_TARGET opengl_offscreen_test)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
file(GLOB SOURCES
        *.h
        *.cpp
        )
source_group("Sources" FILES
        main.cpp)


#egl
find_package(PkgConfig REQUIRED)
pkg_check_modules(DEPS REQUIRED egl glew opengl) 

set(FREEGLUT_INCLUDE_DIRS /usr/include/GL) 
set(FREEGLUT_LIBRARIES /usr/lib/x86_64-linux-gnu/libglut.so)

set(FreeImage_INCLUDE_DIRS /usr/include) 
set(FreeImage_LIBRARIES /usr/lib/x86_64-linux-gnu/libfreeimage.so)

include_directories(${FREEGLUT_INCLUDE_DIRS})

add_executable(${APP_TARGET} ${SOURCES})

target_link_libraries(
        ${APP_TARGET}
        ${DEPS_LIBRARIES}
        ${FreeImage_LIBRARIES}
        ${FREEGLUT_LIBRARIES}
)

