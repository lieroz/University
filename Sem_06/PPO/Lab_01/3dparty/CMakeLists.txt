file(GLOB POLYLINE_SOURCE_FILES "polyline/*.cpp")

project(3dparty)

set(SOURCE_FILES
    ${POLYLINE_SOURCE_FILES}
)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
