cmake_minimum_required(VERSION 2.8)
project(TorusWorld) # Very tentative project name.

# Use C++11
add_definitions( -std=c++0x )

# Warnings
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror")

# Headers
include_directories(include)
file(GLOB_RECURSE HEADERS include/*.hpp include/*.h)

# Main program
set(PROGRAM_SOURCE_DIRECTORY src)
add_executable( torus_run # Executable name.
                "${PROGRAM_SOURCE_DIRECTORY}/main.cpp" )

# Tests
enable_testing()
set(TEST_DIRECTORY test)
file(GLOB TEST_FILE_LIST "${TEST_DIRECTORY}/*.cpp")
add_executable( test_run ${TEST_FILE_LIST} ${HEADERS})
add_test(unit_tests test_run)
