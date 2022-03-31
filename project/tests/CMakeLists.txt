cmake_minimum_required(VERSION 3.14)
project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -lpthread -ldl -pthread -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lpthread -ldl -pthread -lgcov" )

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

message("THREAD_COUNT_INCLUDE_DIRS = ${THREAD_COUNT_INCLUDE_DIRS}")
message("THREAD_COUNT_LIBRARIES = ${THREAD_COUNT_LIBRARIES}")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SIMPLE_COUNT_INCLUDE_DIRS} ;${THREAD_COUNT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SIMPLE_COUNT_LIBRARIES} ;${THREAD_COUNT_LIBRARIES} GTest::gtest_main)