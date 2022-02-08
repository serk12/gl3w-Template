cmake_minimum_required(VERSION 3.16.3)

set(appName Hanbei)
project(${appName})

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLM REQUIRED)

execute_process(COMMAND ln -s ../shaders)

add_subdirectory(libs)
add_subdirectory(code)
