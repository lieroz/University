project(3dparty)

add_subdirectory(polyline)

add_library(${PROJECT_NAME} STATIC)
target_include_directories(${PROJECT_NAME} PUBLIC polyline)
target_link_libraries(${PROJECT_NAME} polyline)
