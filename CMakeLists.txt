cmake_minimum_required(VERSION 3.19)
project(egdkProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_subdirectory(src/editor)
add_subdirectory(src/game)
