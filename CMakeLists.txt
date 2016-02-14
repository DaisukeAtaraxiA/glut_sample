cmake_minimum_required (VERSION 2.6)

project(glut_sample)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${GLUT_INCLUDE_DIR})

add_executable(glut_sample src/main.cpp)
target_link_libraries(glut_sample ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
