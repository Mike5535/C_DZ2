cmake_minimum_required(VERSION 3.0.0)
project(count_pair)

add_executable( ${PROJECT_NAME} main.c )

add_subdirectory(simple_count)
add_subdirectory(thread_count)

message("SIMPLE_COUNT_INCLUDE_DIRS = ${SIMPLE_COUNT_INCLUDE_DIRS}")
message("SIMPLE_COUNT_LIBRARIES = ${SIMPLE_COUNT_LIBRARIES}")

message("THREAD_COUNT_INCLUDE_DIRS = ${THREAD_COUNT_INCLUDE_DIRS}")
message("THREAD_COUNT_LIBRARIES = ${THREAD_COUNT_LIBRARIES}")


set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lpthread -ldl -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${SIMPLE_COUNT_INCLUDE_DIRS} ;${THREAD_COUNT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SIMPLE_COUNT_LIBRARIES} ;${THREAD_COUNT_LIBRARIES})


add_subdirectory(tests)
