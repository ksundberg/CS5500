cmake_minimum_required(VERSION 2.8)
project(TorusWorld)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/client
  ${CMAKE_CURRENT_SOURCE_DIR}/client/forms
  ${CMAKE_CURRENT_SOURCE_DIR}/client/src
  ${CMAKE_CURRENT_SOURCE_DIR}/common
  ${CMAKE_CURRENT_SOURCE_DIR}/common/item
  ${CMAKE_CURRENT_SOURCE_DIR}/common/log
  ${CMAKE_CURRENT_SOURCE_DIR}/common/noise
  ${CMAKE_CURRENT_SOURCE_DIR}/common/Physics
  ${CMAKE_CURRENT_SOURCE_DIR}/common/player
  ${CMAKE_CURRENT_SOURCE_DIR}/common/util
  ${CMAKE_CURRENT_SOURCE_DIR}/common/voxel
  ${CMAKE_CURRENT_SOURCE_DIR}/common/materialContainer
  ${CMAKE_CURRENT_SOURCE_DIR}/common/Controls
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
  client/src/main.h
  client/forms/MainWindow.cpp
  client/forms/MainWindow.h
  client/forms/GridPane.cpp
  client/forms/GridPane.h
  client/forms/canvas.cpp
  client/forms/canvas.h
  client/src/Grid.hpp
  client/src/Grid.cpp
  include/wxwidget.h

)
source_group("client" FILES ${client_srcs})

set(common_srcs
  common/log/logger.h
  common/log/logger.cpp

  common/noise/PerlinNoise.cpp
  common/noise/PerlinNoise.h
  
  common/Physics/PhysicsEngine.cpp
  common/Physics/PhysicsEngine.h

  common/player/inventory.h
  common/player/inventory.cpp
  common/player/Camera.cpp
  common/player/Camera.h

  common/item/item.h
  common/item/item.cpp
  common/item/itemgen.h
  common/item/itemgen.cpp

  common/worldFactory.h
  common/worldFactory.cpp

  common/util/vector3.cpp
  common/util/vector3.h
  common/util/Point.hpp

  common/voxel/block.cpp
  common/voxel/block.h
  common/voxel/chunk.cpp
  common/voxel/chunk.h
  common/voxel/chunkmanager.cpp
  common/voxel/chunkmanager.h
  
  common/materialContainer/MaterialContainer.cpp
  common/materialContainer/MaterialContainer.h
  
  common/object.cpp
  common/object.h
  common/world.cpp
  common/world.h
  common/dungeon.cpp
  common/dungeon.h
  
  common/Controls/DisplayHelper.cpp
  common/Controls/DisplayHelper.h
)
source_group("common" FILES ${common_srcs})

set(test_srcs
  test/main.cpp
  include/catch.hpp
  test/unit/sample.cpp
  test/unit/inventory_test.cpp
  test/unit/chunkmanager_test.cpp
  test/unit/vector3f_test.cpp
  test/unit/dungeon_test.cpp
)
source_group("test" FILES ${test_srcs})

#wxwidgets
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base gl REQUIRED)
include(${wxWidgets_USE_FILE})

#tbb
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake/FindTBB/")
find_package(TBB)
include_directories(${TBB_INCLUDE_DIRS})
link_directories(${TBB_LIBRARY_DIRS})

add_library(common STATIC ${common_srcs} ${TBB_LIBRARIES})

# OpenGL
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(torus ${client_srcs})
add_executable(torus_test ${test_srcs})

target_link_libraries(torus common ${wxWidgets_LIBRARIES} 
                                   ${TBB_LIBRARIES} 
                                   ${OPENGL_LIBRARIES}
				   ${GLUT_LIBRARY})
				   
target_link_libraries(torus_test common ${TBB_LIBRARIES})

enable_testing()
add_test(unit_tests torus_test)

# Copy log directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/log/log.conf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/log)
