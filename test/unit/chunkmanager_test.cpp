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
  Chunk* chunk = new Chunk(0, 0, 0);
  chunk->set(0, 0, 0, BlockType::Ground);
  REQUIRE(chunk->get(0, 0, 0));
  chunk->set(0, 0, 0, BlockType::Inactive);
  REQUIRE(!(chunk->get(0, 0, 0)));
  delete chunk;
}

TEST_CASE("Can activate and deactivate all blocks in a chunk.")
{
  Chunk* chunk = new Chunk(1, 4, 5);

  chunk->setAllBlocks(BlockType::Ground);
  // Make sure they're all active.
  REQUIRE(chunk->get(5, 8, 2));
  REQUIRE(chunk->get(2, 4, 9));
  REQUIRE(chunk->get(9, 8, 7));

  chunk->setAllBlocks(BlockType::Inactive);
  // Make sure they're all inactive.
  REQUIRE(!(chunk->get(5, 8, 2)));
  REQUIRE(!(chunk->get(2, 4, 9)));
  REQUIRE(!(chunk->get(9, 8, 7)));

  delete chunk;
}

TEST_CASE("Can check if blocks are active or not.")
{
  auto block = new Block();
  block->set(BlockType::Ground);
  REQUIRE(block->get());
  block->set(BlockType::Inactive);
  REQUIRE(!(block->get()));
  delete block;
}
