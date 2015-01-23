cmake_minimum_required(VERSION 2.8)
project(TorusWorld)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/client
  ${CMAKE_CURRENT_SOURCE_DIR}/client/forms
  ${CMAKE_CURRENT_SOURCE_DIR}/client/src
  ${CMAKE_CURRENT_SOURCE_DIR}/common
  ${CMAKE_CURRENT_SOURCE_DIR}/common/log
  ${CMAKE_CURRENT_SOURCE_DIR}/common/noise
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/log
  ${CMAKE_CURRENT_SOURCE_DIR}/test
)

add_definitions( -std=c++0x )

set(EXTRA_COMPILE_FLAGS "-Wall -Wextra -Werror -Wno-missing-braces -g")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${EXTRA_COMPILE_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})

set(client_srcs
  client/src/main.cpp
  client/forms/MainWindow.cpp
  client/forms/MainWindow.h
  client/forms/GridPane.cpp
  client/forms/GridPane.h
  client/src/Grid.hpp
  client/src/Grid.cpp
  client/src/Point.hpp
  include/wxwidget.h
)
source_group("client" FILES ${client_srcs})

set(common_srcs
  common/log/logger.h
  common/log/logger.cpp
  common/noise/PerlinNoise.cpp
  common/noise/PerlinNoise.h
)
source_group("common" FILES ${common_srcs})

set(test_srcs
  test/main.cpp
  include/catch.hpp
  test/unit/sample.cpp
)
source_group("test" FILES ${test_srcs})

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})


add_library(common SHARED ${common_srcs})

add_executable(torus ${client_srcs})
add_executable(torus_test ${test_srcs})

target_link_libraries(torus common ${wxWidgets_LIBRARIES})
target_link_libraries(torus_test common)

enable_testing()
add_test(unit_tests torus_test)

# Copy log directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/log/log.conf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/log)
