cmake_minimum_required(VERSION 2.8.12)

project(polyline)

file(GLOB SOURCE_FILES *.cpp)

find_package(Qt5 COMPONENTS Core Location REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Location)
