#include <catch.hpp>
#include "dungeon.h"
#include "logger.h"

TEST_CASE("We have a dungeon to work with.")
{
  Dungeon dungeon;
  auto block_count = dungeon.blockCount();
  SECTION("The bottom of the dungeon contains active blocks.")
  {
    REQUIRE(dungeon.isBlockActive(0, 0, 0));
    REQUIRE(dungeon.isBlockActive(2, 2, 0));

    REQUIRE(dungeon.isBlockActive(block_count - 1, block_count - 1, 0));
  }

  SECTION("Out of bounds dungeon blocks are inactive.")
  {
    REQUIRE(!(dungeon.isBlockActive(-1, -1, -1)));
  }

  SECTION("We have an entrance at the top middle of the dungeon.")
  {
    REQUIRE(!(dungeon.isBlockActive(block_count/2, block_count/2, block_count-1)));
  }
}
