cmake_minimum_required(VERSION 3.14)
project(count_pair_bytes)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -pthread -lgcov")

file(GLOB SOURCES "sources/*.c")
file(GLOB INCLUDE "headers/*.h")
file(GLOB EXC "main.c")
file(GLOB EXC_TEST "tests/test_100MB.cpp")
file(GLOB EXC_TEST_VALGRIND "tests/main_test.cpp")

add_library(lib SHARED ${INCLUDE} ${SOURCES})
add_executable(main ${EXC})
target_link_libraries(main lib)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests_100MB ${EXC_TEST})
target_link_libraries(tests_100MB lib gtest_main)

add_executable(tests ${EXC_TEST_VALGRIND})
target_link_libraries(tests lib gtest_main)
