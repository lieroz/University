cmake_minimum_required(VERSION 3.6)
project(Lab_12)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    main.c PrintTable.h PrintTable.c Colors.h AddToFile.h AddToFile.c)

add_executable(Lab_12 ${SOURCE_FILES})

find_package(LibXml2 REQUIRED)

include_directories(${LIBXML2_INCLUDE_DIR})

target_link_libraries( Lab_12 ${LIBXML2_LIBRARIES})