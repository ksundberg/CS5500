cmake_minimum_required(VERSION 2.8)
project(dwfort)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/common
  ${CMAKE_CURRENT_SOURCE_DIR}/src/common/log
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test
  ${CMAKE_CURRENT_SOURCE_DIR}/log
)

# Use C++11
add_definitions( -std=c++0x )

set(EXTRA_COMPILE_FLAGS "-Wall -Wextra -Weror -g")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${EXTRA_COMPILE_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})

set(client_srcs
  src/client/main.cpp
)
source_group("client" FILES ${client_srcs})

set(common_srcs
  src/common/sample.h
  src/common/sample.cpp
  src/common/log/logger.h
  src/common/log/logger.cpp
)
source_group("common" FILES ${common_srcs})

set(test_srcs
  src/test/main.cpp
  src/test/catch/catch.hpp
  src/test/unit/sample.cpp
)
source_group("test" FILES ${test_srcs})

add_library(common SHARED ${common_srcs})

add_executable(dwfort ${client_srcs})
add_executable(dwfort_test ${test_srcs})

target_link_libraries(dwfort common)
target_link_libraries(dwfort_test common)

enable_testing()
add_test(unit_tests dwfort_test)

# Copy log directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/log/log.conf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/log)
