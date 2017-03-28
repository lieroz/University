cmake_minimum_required(VERSION 3.6)
project(Lab_02)

set(CMAKE_CXX_STANDARD 11)

include_directories(definitions)
include_directories(tests)

set(DEFINITON_DIR definitions)
set(DEFINITIONS
		${DEFINITON_DIR}/ftlspace.hpp
		${DEFINITON_DIR}/base_iterator.hpp
		${DEFINITON_DIR}/array_iterator.hpp
		${DEFINITON_DIR}/base_container.hpp
		${DEFINITON_DIR}/vector.hpp
		${DEFINITON_DIR}/const_array_iterator.hpp
		${DEFINITON_DIR}/base_array_iterator.hpp
		${DEFINITON_DIR}/base_allocator.hpp
		${DEFINITON_DIR}/object_traits.hpp
		${DEFINITON_DIR}/standard_alloc_policy.hpp
		${DEFINITON_DIR}/expanding_container.hpp
		${DEFINITON_DIR}/set.hpp)

set(IMPLEMENTATION_DIR implementations)
set(IMPLEMENTATIONS
		${IMPLEMENTATION_DIR}/base_iterator_impl.hpp
		${IMPLEMENTATION_DIR}/object_traits_impl.hpp
		${IMPLEMENTATION_DIR}/standard_alloc_policy_impl.hpp
		${IMPLEMENTATION_DIR}/base_allocator_impl.hpp
		${IMPLEMENTATION_DIR}/base_container_impl.hpp
		${IMPLEMENTATION_DIR}/base_array_iterator_impl.hpp
		${IMPLEMENTATION_DIR}/const_array_iterator_impl.hpp
		${IMPLEMENTATION_DIR}/array_iterator_impl.hpp
		${IMPLEMENTATION_DIR}/vector_impl.hpp
		${IMPLEMENTATION_DIR}/expanding_container_impl.hpp
		${IMPLEMENTATION_DIR}/set_impl.hpp)

set(TEST_DIR tests)
set(TESTS
		${TEST_DIR}/vector_tests.hpp
		${TEST_DIR}/set_tests.hpp
		${TEST_DIR}/timer.hpp)

add_executable(Lab_02 main.cpp ${IMPLEMENTATIONS} ${DEFINITIONS} ${TESTS})