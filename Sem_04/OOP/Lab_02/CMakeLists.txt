cmake_minimum_required(VERSION 3.6)
project(Lab_02)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ftlspace.hpp base_iterator.hpp vector_iterator.hpp base_container.hpp vector.hpp const_vector_iterator.hpp base_vector_iterator.hpp base_allocator.hpp)
add_executable(Lab_02 ${SOURCE_FILES})