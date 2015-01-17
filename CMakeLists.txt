cmake_minimum_required(VERSION 2.8)
project(TorusWorld) # Very tentative project name.

# Use C++11
add_definitions( -std=c++0x )

# Warnings
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror")

# Headers
include_directories(include)
file(GLOB_RECURSE HEADERS include/*.hpp include/*.h)

set(PROGRAM_SOURCE_DIRECTORY src)

add_executable( torus_run # Executable name.
                "${PROGRAM_SOURCE_DIRECTORY}/main.cpp" )
