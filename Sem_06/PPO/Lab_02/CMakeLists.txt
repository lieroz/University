cmake_minimum_required(VERSION 3.10)
project(Lab_02)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(GLOB DATA_SOURCES src/data/*.cpp)
file(GLOB MODEL_SOURCES src/data/models/*.cpp)
set(PROJECT_SOURCES
        ${DATA_SOURCES}
        ${MODEL_SOURCES}
        )

add_executable(${PROJECT_NAME} main.cpp ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)