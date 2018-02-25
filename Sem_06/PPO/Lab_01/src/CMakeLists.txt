file(GLOB DATALOADER_SOURCE_FILES "dataloaders/*.cpp")
file(GLOB COMMANDS_SOURCE_FILES "commands/*.cpp")
file(GLOB INCLUDE_FILES ${PROJECT_SOURCE_DIR}/include/*.h)

project(lib)

set(SOURCE_FILES
    ${DATALOADER_SOURCE_FILES}
    ${COMMANDS_SOURCE_FILES}
    ${INCLUDE_FILES}
)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
