cmake_minimum_required(VERSION 2.8.12)

project(Lab_01_gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB MAIN_SOURCE_FILES *.cpp)
file(GLOB SOURCE_FILES src/*.cpp)
file(GLOB COMMAND_SOURCE_FILES src/commands/*.cpp)
file(GLOB FORM_FILES forms/*.ui)

set(SOURCES
    ${MAIN_SOURCE_FILES}
    ${SOURCE_FILES}
    ${COMMAND_SOURCE_FILES}
)

find_package(Qt5 COMPONENTS Quick Widgets REQUIRED)
qt5_wrap_ui(FORMS ${FORM_FILES})

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${FORMS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} Qt5::Quick Qt5::Widgets Lab_01_lib)
