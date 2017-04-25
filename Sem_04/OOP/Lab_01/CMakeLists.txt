cmake_minimum_required(VERSION 3.6)
project(Lab_01)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lab_01 main.cpp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

include_directories(headers)

set(HEADERS_DIR headers)
set(HEADERS
		${HEADERS_DIR}/mainwindow.h
		${HEADERS_DIR}/qstrtochararr.h
		${HEADERS_DIR}/error.h
		${HEADERS_DIR}/load_file.h
		${HEADERS_DIR}/geometry.h
		${HEADERS_DIR}/print_picture.h
		${HEADERS_DIR}/processor.h
		${HEADERS_DIR}/lineto.h
		${HEADERS_DIR}/action.h
		${HEADERS_DIR}/stream.h
		${HEADERS_DIR}/ptr.h
		${HEADERS_DIR}/dot.h
		${HEADERS_DIR}/link.h
		${HEADERS_DIR}/ui_mainwindow.h)

set(SOURCES_DIR sources)
set(SOURCES
		${SOURCES_DIR}/mainwindow.cpp
		${SOURCES_DIR}/error.cpp
		${SOURCES_DIR}/qstrtochararr.cpp
		${SOURCES_DIR}/load_file.cpp
		${SOURCES_DIR}/geometry.cpp
		${SOURCES_DIR}/print_picture.cpp
		${SOURCES_DIR}/processor.cpp
		${SOURCES_DIR}/lineto.cpp
		${SOURCES_DIR}/action.cpp
		${SOURCES_DIR}/stream.cpp
		${SOURCES_DIR}/ptr.cpp
		${SOURCES_DIR}/dot.cpp
		${SOURCES_DIR}/link.cpp)

add_library(library SHARED ${SOURCES} ${HEADERS})
target_link_libraries(library Qt5::Core Qt5::Widgets Qt5::Gui)

target_link_libraries(Lab_01 library)