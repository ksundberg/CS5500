#include <catch.hpp>
#include "chunkmanager.h"
#include "block.h"

TEST_CASE("ChunkManager is a 3-dimmensional matrix of blocks under the hood.")
{
  ChunkManager cm;
  SECTION("Can set and get blocks.")
  {
    cm.set(1, 2, 3, BlockType::Ground);
    REQUIRE(cm.get(1, 2, 3));
    cm.set(1, 4, 5, BlockType::Inactive);
    REQUIRE(!(cm.get(1, 4, 5)));
    cm.set(cm.BOUNDX - 1, cm.BOUNDY - 1, cm.BOUNDZ - 1, BlockType::Water);
    REQUIRE(cm.get(cm.BOUNDX - 1, cm.BOUNDY - 1, cm.BOUNDZ - 1) ==
            BlockType::Water);
  }
  SECTION("Out of bounds blocks are inactive.")
  {
    cm.set(cm.BOUNDX, cm.BOUNDY, cm.BOUNDZ, BlockType::Ground);
    REQUIRE(cm.get(cm.BOUNDX, cm.BOUNDY, cm.BOUNDZ) == BlockType::Inactive);

    cm.set(-1, -1, -1, BlockType::Ground);
    REQUIRE(cm.get(-1, -1, -1) == BlockType::Inactive);
  }
}

TEST_CASE("Chunks can access and set their blocks.")
{
  Chunk chunk(0, 0, 0);
  chunk.set(0, 0, 0, BlockType::Ground);
  REQUIRE(chunk.get(0, 0, 0));
  chunk.set(0, 0, 0, BlockType::Inactive);
  REQUIRE(!(chunk.get(0, 0, 0)));
}

TEST_CASE("Can activate and deactivate all blocks in a chunk.")
{
  Chunk chunk(1, 4, 5);

  chunk.setAllBlocks(BlockType::Ground);
  // Make sure they're all active.
  REQUIRE(chunk.get(5, 8, 2) != BlockType::Inactive);
  REQUIRE(chunk.get(2, 4, 9) != BlockType::Inactive);
  REQUIRE(chunk.get(9, 8, 7) != BlockType::Inactive);

  chunk.setAllBlocks(BlockType::Inactive);
  // Make sure they're all inactive.
  REQUIRE(chunk.get(5, 8, 2) == BlockType::Inactive);
  REQUIRE(chunk.get(2, 4, 9) == BlockType::Inactive);
  REQUIRE(chunk.get(9, 8, 7) == BlockType::Inactive);
}

TEST_CASE("Can check if blocks are active or not.")
{
  Block block({0, 0, 0}, BlockType::Inactive);
  block.type = BlockType::Ground;
  REQUIRE(block.type != BlockType::Inactive);
  block.type = BlockType::Inactive;
  REQUIRE(block.type == BlockType::Inactive);
}
