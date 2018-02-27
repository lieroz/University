cmake_minimum_required(VERSION 2.8.12)

project(Lab_01_lib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_subdirectory(3dparty)

find_package(Qt5 COMPONENTS Core REQUIRED)

file(GLOB GLOB_SOURCES src/*.cpp)
file(GLOB COMMON_SOURCES src/common/*.cpp)
file(GLOB COMMANDS_SOURCES src/commands/*.cpp)
file(GLOB DATALOADERS_SOURCES src/dataloaders/*.cpp)

set(SOURCE_FILES
    ${GLOB_SOURCES}
    ${COMMON_SOURCES}
    ${COMMANDS_SOURCES}
    ${DATALOADERS_SOURCES})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} 3dparty)
