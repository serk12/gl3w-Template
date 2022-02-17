include_directories("${CMAKE_SOURCE_DIR}/libs/imgui")
set(imgui_files imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_tables.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_glut.cpp)
add_library(imgui ${imgui_files})

include_directories("${CMAKE_SOURCE_DIR}/libs/gl3w/build/include")
set(gl3w_files gl3w/build/src/gl3w.c)
add_library(gl3w ${gl3w_files})

set(LIBZIP_DO_INSTALL OFF)
set(BUILD_SHARED_LIBS OFF)
set(LIBZIP_DO_INSTALL OFF)
