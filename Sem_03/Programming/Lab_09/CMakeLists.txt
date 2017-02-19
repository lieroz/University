cmake_minimum_required(VERSION 3.6)
project(Lab_09)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES main.c graph.c graph.h dequeue.h dequeue.c)
add_executable(Lab_09 ${SOURCE_FILES})