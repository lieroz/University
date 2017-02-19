cmake_minimum_required(VERSION 3.6)
project(Lab_10)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c heap.h heap.c graph.h graph.c dijkstra.c dijkstra.h)
add_executable(Lab_10 ${SOURCE_FILES})