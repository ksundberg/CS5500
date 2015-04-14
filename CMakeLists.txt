cmake_minimum_required(VERSION 2.8)
project(TorusWorld)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/client
  ${CMAKE_CURRENT_SOURCE_DIR}/client/forms
  ${CMAKE_CURRENT_SOURCE_DIR}/client/src
  ${CMAKE_CURRENT_SOURCE_DIR}/common
  ${CMAKE_CURRENT_SOURCE_DIR}/common/item
  ${CMAKE_CURRENT_SOURCE_DIR}/common/interfaces
  ${CMAKE_CURRENT_SOURCE_DIR}/common/log
  ${CMAKE_CURRENT_SOURCE_DIR}/common/noise
  ${CMAKE_CURRENT_SOURCE_DIR}/common/player
  ${CMAKE_CURRENT_SOURCE_DIR}/common/util
  ${CMAKE_CURRENT_SOURCE_DIR}/common/voxel
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
  client/forms/MainWindow.cpp
  client/forms/GridPane.cpp
  client/forms/canvas.cpp
  client/src/Grid.cpp
)
source_group("client" FILES ${client_srcs})

set(common_srcs
  common/log/logger.cpp

  common/noise/PerlinNoise.cpp
  
  common/Physics/MovingObject.cpp
  common/Physics/MovingObject.h

  common/player/inventory.cpp
  common/player/Camera.cpp

  common/item/item.cpp
  common/item/itemgen.cpp

  common/interfaces/IRenderable.cpp
  common/interfaces/IVertexContainer.cpp

  common/util/vector3.cpp

  common/voxel/block.cpp
  common/voxel/chunk.cpp
  common/voxel/chunkmanager.cpp

  common/object.cpp
  common/dungeon.cpp
  common/critter.cpp
  common/world.cpp

  common/density/rectangular_prism.cpp

  client/forms/graphics.cpp
  client/forms/vertexviewer.cpp
)
source_group("common" FILES ${common_srcs})

set(test_srcs
  test/main.cpp
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

add_library(common STATIC ${common_srcs})

# OpenGL
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake/FindGLM/")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS}
                    ${GLUT_INCLUDE_DIRS}
                    ${GLM_INCLUDE_DIRS}
                    ${GLEW_INCLUDE_DIRS})

add_executable(torus ${client_srcs})
add_executable(torus_test ${test_srcs})

target_link_libraries(torus common ${wxWidgets_LIBRARIES}
                                   ${TBB_LIBRARIES}
                                   ${OPENGL_LIBRARIES}
                                   ${GLUT_LIBRARY}
                                   ${GLEW_LIBRARY})

target_link_libraries(torus_test common ${TBB_LIBRARIES}
                                        ${wxWidgets_LIBRARIES}
                                        ${OPENGL_LIBRARIES}
                                        ${GLUT_LIBRARY}
                                        ${GLEW_LIBRARY})

enable_testing()
add_test(unit_tests torus_test)

# Copy log directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/log/log.conf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/log)

add_custom_command(TARGET torus POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/common/voxel/world.v.glsl"
    "${CMAKE_BINARY_DIR}/world.v.glsl"
        DEPENDS "${CMAKE_SOURCE_DIR}/world.v.glsl")

add_custom_command(TARGET torus POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/common/voxel/world.f.glsl"
    "${CMAKE_BINARY_DIR}/world.f.glsl"
        DEPENDS "${CMAKE_SOURCE_DIR}/world.f.glsl")
