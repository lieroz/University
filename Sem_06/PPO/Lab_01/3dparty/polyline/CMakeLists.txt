project(polyline)

file(GLOB SOURCE_FILES *.cpp)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Qt5::Core)
