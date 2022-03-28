cmake_minimum_required(VERSION 3.0.0)
project(simple_count)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -lpthread -ldl -fPIC -O0")

file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})

set(SIMPLE_COUNT_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(SIMPLE_COUNT_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
