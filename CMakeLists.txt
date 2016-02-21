cmake_minimum_required (VERSION 2.6)

project(glut_sample)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${GLUT_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(glut_sample STATIC
  include/glut_sample/glut_application.h
  src/glut_application.cpp)
target_link_libraries(glut_sample ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

add_executable(sample samples/sample.cpp)
target_link_libraries(sample glut_sample)
