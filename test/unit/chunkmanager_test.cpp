#include <catch.hpp>
#include "chunkmanager.h"

TEST_CASE("Chunk Manager update function test",
          "[float deltaTime, Vector3 cameraPosition, Vector3 cameraRotation)]")
{
  float deltaTime = 10.0;
  Vector3 camera_position(2, 3, 5);
  Vector3 camera_rotation(6, 5, 9);

  ChunkManager Manager_test;

  Manager_test.Update(deltaTime, camera_position, camera_rotation);
  REQUIRE(Manager_test.chunkRenderList == Manager_test.pChunkVisibilityList);

  ChunkList previous_render_list = Manager_test.chunkRenderList;
  ChunkList previous_visability_list = Manager_test.pChunkVisibilityList;

  camera_rotation.x = 70;
  camera_rotation.y = 130;
  camera_rotation.z = 150;

  camera_position.x = 56.7;
  camera_position.y = 67.8;
  camera_position.z = 87.5;

  Manager_test.Update(deltaTime, camera_position, camera_rotation);
  REQUIRE(Manager_test.chunkRenderList == Manager_test.pChunkVisibilityList);
}

TEST_CASE("Chunks can access and set their blocks.")
{
  Chunk* chunk = new Chunk(0, 0, 0);
  chunk->activateBlock(0, 0, 0);
  REQUIRE(chunk->isBlockActive(0, 0, 0));
  chunk->deactivateBlock(0, 0, 0);
  REQUIRE(!(chunk->isBlockActive(0, 0, 0)));
}

TEST_CASE("Can activate and deactivate all blocks in a chunk.")
{
  Chunk* chunk = new Chunk(1, 4, 5);

  chunk->activateAllBlocks();
  // Make sure they're all active.
  REQUIRE(chunk->isBlockActive(5, 8, 2));
  REQUIRE(chunk->isBlockActive(2, 4, 9));
  REQUIRE(chunk->isBlockActive(9, 8, 7));

  chunk->deactivateAllBlocks();
  // Make sure they're all inactive.
  REQUIRE(!(chunk->isBlockActive(5, 8, 2)));
  REQUIRE(!(chunk->isBlockActive(2, 4, 9)));
  REQUIRE(!(chunk->isBlockActive(9, 8, 7)));
}
