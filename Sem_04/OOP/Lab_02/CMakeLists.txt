cmake_minimum_required(VERSION 3.6)
project(Lab_02)

set(CMAKE_CXX_STANDARD 11)

include_directories(definitions)
include_directories(tests)

set(DEFINITON_DIR definitions)
set(DEFINITIONS
		${DEFINITON_DIR}/ftlspace.hpp
		${DEFINITON_DIR}/set_iterator.hpp
		${DEFINITON_DIR}/base_container.hpp
		${DEFINITON_DIR}/const_set_iterator.hpp
		${DEFINITON_DIR}/base_iterator.hpp
		${DEFINITON_DIR}/expanding_container.hpp
		${DEFINITON_DIR}/set.hpp
		${DEFINITON_DIR}/exceptions.hpp)

set(IMPLEMENTATION_DIR implementations)
set(IMPLEMENTATIONS
		${IMPLEMENTATION_DIR}/base_container.cpp
		${IMPLEMENTATION_DIR}/base_iterator_impl.hpp
		${IMPLEMENTATION_DIR}/const_set_iterator_impl.hpp
		${IMPLEMENTATION_DIR}/set_iterator_impl.hpp
		${IMPLEMENTATION_DIR}/expanding_container_impl.hpp
		${IMPLEMENTATION_DIR}/set_impl.hpp)

set(TEST_DIR tests)
set(TESTS
		${TEST_DIR}/set_tests.hpp
		${TEST_DIR}/timer.hpp)

add_executable(Lab_02 main.cpp ${IMPLEMENTATIONS} ${DEFINITIONS} ${TESTS})