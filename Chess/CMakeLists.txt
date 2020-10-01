cmake_minimum_required(VERSION 3.10)

project(CChess)

file(GLOB SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# add the executable
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_executable(CChess ${SOURCE})

