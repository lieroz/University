cmake_minimum_required(VERSION 2.8)

project(sysprog_labs)

set(SOURCES
    "tree.c")

foreach(sourcefile ${SOURCES})
    string(REPLACE ".c" "" name ${sourcefile})
    add_executable(${name} ${sourcefile})
endforeach(sourcefilename ${SOURCES})
