cmake_minimum_required(VERSION 3.10)
project(Lab_02)

add_subdirectory(application)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} application)
