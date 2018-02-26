file(GLOB DATALOADER_SOURCE_FILES "dataloaders/*.cpp")
file(GLOB COMMANDS_SOURCE_FILES "commands/*.cpp")
file(GLOB COMMON_SOURCE_FILES "common/*.cpp")
file(GLOB LIB_SOURCE_FILES "*.cpp")
file(GLOB INCLUDE_FILES ${PROJECT_SOURCE_DIR}/include/*.h)

include_directories(${PROJECT_SOURCE_DIR}/3dparty)

project(lib)

set(SOURCE_FILES
    ${DATALOADER_SOURCE_FILES}
    ${COMMANDS_SOURCE_FILES}
    ${COMMON_SOURCE_FILES}
    ${LIB_SOURCE_FILES}
    ${INCLUDE_FILES}
    ${3D_PARTY_INCLUDE_FILES}
)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5Widgets)
