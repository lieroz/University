cmake_minimum_required(VERSION 3.10)
project(DescentsAndAscentsPlugin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES DescentsAndAscentsPlugin.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets application)
