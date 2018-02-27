cmake_minimum_required(VERSION 2.8.12)

project(3dparty)

add_subdirectory(polyline)

set(INCLUDE_DIRS
    polyline
)

set(LIBS
    polyline
)

add_library(${PROJECT_NAME} STATIC)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBS})
