cmake_minimum_required(VERSION 3.5)
project(CPP-BASIC)

enable_testing(true)

if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif (CMAKE_COMPILER_IS_GNUCC)

add_subdirectory(interpreter)
add_subdirectory(extra)
add_subdirectory(host_posix)
add_subdirectory(test)

