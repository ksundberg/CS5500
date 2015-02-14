#include <catch.hpp>
#include "dungeon.h"
#include "logger.h"

TEST_CASE("We have a dungeon to work with.")
{
  ChunkList chunks;
  Dungeon::makeDungeon(chunks);
  auto dungeon_length = Dungeon::dungeonBlockLength();
  SECTION("The bottom of the dungeon contains active blocks.")
  {
    REQUIRE(Dungeon::isBlockActive(chunks, 0, 0, 0));
    REQUIRE(Dungeon::isBlockActive(chunks, 2, 2, 0));

    REQUIRE(Dungeon::isBlockActive(chunks, dungeon_length - 1, dungeon_length - 1, 0));
  }

  SECTION("Out of bounds dungeon blocks are inactive.")
  {
    REQUIRE(!(Dungeon::isBlockActive(chunks, -1, -1, -1)));
  }

  SECTION("We have an entrance at the top middle of the dungeon.")
  {
    REQUIRE(!(Dungeon::isBlockActive(chunks, dungeon_length/2, dungeon_length/2, dungeon_length-1)));
  }
}
