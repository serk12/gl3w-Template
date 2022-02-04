cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)
cmake_policy(SET CMP0072 OLD)

set(appName Hanbei)
project(${appName})

set (CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

execute_process(COMMAND ln -s ../shaders)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLM REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories("${CMAKE_SOURCE_DIR}/libs/gl3w/build/include")
include_directories("${CMAKE_SOURCE_DIR}/libs/eigen")
include_directories("${CMAKE_SOURCE_DIR}/libs/imgui")
include_directories("${CMAKE_SOURCE_DIR}/code/headers")

link_directories(${OPENGL_LIBRARY_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})

link_libraries(dl)

set(imgui_files libs/imgui/imgui.cpp libs/imgui/imgui_demo.cpp libs/imgui/imgui_draw.cpp libs/imgui/imgui_widgets.cpp libs/imgui/backends/imgui_impl_opengl3.cpp libs/imgui/backends/imgui_impl_glut.cpp)
set(gl3w_files libs/gl3w/build/src/gl3w.c)
aux_source_directory( "${CMAKE_SOURCE_DIR}/code/src" SOURCES)

add_library(imgui ${imgui_files} )
add_executable( ${appName} ${SOURCES} ${gl3w_files} main.cpp )
target_link_libraries( ${appName} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} imgui)
