cmake_minimum_required(VERSION 2.8.12)
project(Lab_02)

if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else ()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif ()

include(DownloadProject.cmake)
download_project(
        PROJ nana
        GIT_REPOSITORY https://github.com/cnjinhao/nana.git
        GIT_TAG master
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

add_subdirectory(${nana_SOURCE_DIR} ${nana_BINARY_DIR})

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} nana Threads::Threads)