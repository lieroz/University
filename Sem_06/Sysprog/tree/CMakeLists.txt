cmake_minimum_required(VERSION 2.8)

project(tree)

file(GLOB SOURCE_FILES *.c)

set(SOURCES
    ${SOURCE_FILES})

add_library(${PROJECT_NAME} ${SOURCES})
