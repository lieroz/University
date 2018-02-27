cmake_minimum_required(VERSION 2.8.12)

project(Lab_01 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB SOURCES src/*.cpp)
file(GLOB COMMON_SOURCES src/common/*.cpp)
file(GLOB COMMANDS_SOURCES src/commands/*.cpp)
file(GLOB DATALOADERS_SOURCES src/dataloaders/*.cpp)

set(SOURCE_FILES
    ${SOURCES}
    ${COMMON_SOURCES}
    ${COMMANDS_SOURCES}
    ${DATALOADERS_SOURCES})

add_subdirectory(3dparty)

find_package(Qt5 COMPONENTS Quick Core Widgets REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp" "qml.qrc" ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} Qt5::Quick Qt5::Core Qt5::Widgets 3dparty)
