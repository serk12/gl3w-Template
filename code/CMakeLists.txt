execute_process(COMMAND ln -s "${CMAKE_SOURCE_DIR}/code/Shaders")

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories("${CMAKE_SOURCE_DIR}/libs/gl3w/build/include")
include_directories("${CMAKE_SOURCE_DIR}/libs/eigen")
include_directories("${CMAKE_SOURCE_DIR}/libs/imgui")

# link_directories append CMAKE_CURRENT_SOURCE_DIR torelative path = global
cmake_policy(SET CMP0015 NEW)
link_directories(${OPENGL_LIBRARY_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
link_libraries(dl)

aux_source_directory("${CMAKE_SOURCE_DIR}/code/Core/src" SOURCES)
aux_source_directory("${CMAKE_SOURCE_DIR}/code/Application/src" SOURCES)
aux_source_directory("${CMAKE_SOURCE_DIR}/code/Connector/src" SOURCES)
add_executable(${appName} ${SOURCES} main.cpp)
target_link_libraries(${appName} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} imgui gl3w ${CMAKE_DL_LIBS})
