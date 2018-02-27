cmake_minimum_required(VERSION 2.8.12)

project(Lab_01_gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB FORM_FILES forms/*.ui)

find_package(Qt5 COMPONENTS Quick Widgets REQUIRED)
qt5_wrap_ui(FORMS ${FORM_FILES})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${FORMS})
target_link_libraries(${PROJECT_NAME} Qt5::Quick Qt5::Widgets Lab_01_lib)
