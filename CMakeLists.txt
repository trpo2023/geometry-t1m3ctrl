cmake_minimum_required(VERSION 3.5.1)
project(geometry)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -lm -Igeometry-t1m3ctrl -Iinclude -Ithirdparty")

include_directories(include)
include_directories(thirdparty)

add_library(geometrylib src/errors.c src/geometry.c)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

add_executable(test_app test/test.c test/main.c)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/test)

target_link_libraries(test_app geometrylib)

add_executable(geometry src/main.c)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

target_link_libraries(geometry geometrylib)



