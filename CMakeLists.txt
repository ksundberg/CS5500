cmake_minimum_required(VERSION 2.8)
project(TorusWorld) # Very tentative project name.

# Use C++11
add_definitions( -std=c++0x )

# Warnings
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror")

add_subdirectory(src)
