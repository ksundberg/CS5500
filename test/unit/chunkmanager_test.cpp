#include <catch.hpp>
#include "chunkmanager.h"
#include "block.h"

TEST_CASE("ChunkManager is a 3-dimmensional matrix of blocks under the hood, "
          "so we should be able to set and get them.")
{
  ChunkManager cm;
  cm.set(1, 2, 3, BlockType::Active);
  REQUIRE(cm.get(1, 2, 3));
  cm.set(1, 4, 5, BlockType::Inactive);
  REQUIRE(!(cm.get(1, 4, 5)));
}

TEST_CASE("Chunks can access and set their blocks.")
{
  Chunk* chunk = new Chunk(0, 0, 0);
  chunk->set(0, 0, 0, BlockType::Active);
  REQUIRE(chunk->get(0, 0, 0));
  chunk->set(0, 0, 0, BlockType::Inactive);
  REQUIRE(!(chunk->get(0, 0, 0)));
}

TEST_CASE("Can activate and deactivate all blocks in a chunk.")
{
  Chunk* chunk = new Chunk(1, 4, 5);

  chunk->setAllBlocks(BlockType::Active);
  // Make sure they're all active.
  REQUIRE(chunk->get(5, 8, 2));
  REQUIRE(chunk->get(2, 4, 9));
  REQUIRE(chunk->get(9, 8, 7));

  chunk->setAllBlocks(BlockType::Inactive);
  // Make sure they're all inactive.
  REQUIRE(!(chunk->get(5, 8, 2)));
  REQUIRE(!(chunk->get(2, 4, 9)));
  REQUIRE(!(chunk->get(9, 8, 7)));
}

TEST_CASE("Can check if blocks are active or not.")
{
  auto block = new Block();
  block->set(BlockType::Active);
  REQUIRE(block->get());
  block->set(BlockType::Inactive);
  REQUIRE(!(block->get()));
  delete block;
}
