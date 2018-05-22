cmake_minimum_required(VERSION 3.10)
project(tests)

enable_testing(true)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Test REQUIRED)
file(GLOB SOURCE_FILES *.cpp)

foreach(testSrc ${SOURCE_FILES})
        get_filename_component(testName ${testSrc} NAME_WE)
        add_executable(${testName} ${testSrc})
        add_test(${testName} ${testName})
        target_link_libraries(${testName} Qt5::Test application)
endforeach(testSrc)
