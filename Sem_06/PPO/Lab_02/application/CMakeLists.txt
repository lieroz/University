cmake_minimum_required(VERSION 3.10)
project(application)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Test Widgets Charts REQUIRED)

file(GLOB DATA_SOURCES src/data/*.cpp)
file(GLOB DATA_MODEL_SOURCES src/data/models/*.cpp)
file(GLOB UI_SOURCES src/ui/*.cpp)
file(GLOB UI_COMMAND_SOURCES src/ui/commands/*.cpp)
file(GLOB UI_PRESENTER_SOURCES src/ui/presenters/*.cpp)
set(PROJECT_SOURCES
        ${DATA_SOURCES}
        ${DATA_MODEL_SOURCES}
        ${UI_SOURCES}
        ${UI_COMMAND_SOURCES}
        ${UI_PRESENTER_SOURCES}
        )

file(GLOB QOBJECT_HEADERS include/ui/*.h)
file(GLOB QOBJECT_PRESENTER_HEADERS include/ui/presenters/*.h)
set(PROJECT_QOBJECT_HEADES
    ${QOBJECT_HEADERS}
    ${QOBJECT_PRESENTER_HEADERS}
    )
qt5_wrap_cpp(MOC_FILES ${PROJECT_QOBJECT_HEADES})

file(GLOB FORM_FILES include/ui/*.ui)
qt5_wrap_ui(FORMS ${FORM_FILES})

add_library(${PROJECT_NAME} ${PROJECT_SOURCES} ${MOC_FILES} ${FORMS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Charts)
