cmake_minimum_required(VERSION 3.10)
project(Lab_03)

add_subdirectory(application)
add_subdirectory(tests)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} application)
