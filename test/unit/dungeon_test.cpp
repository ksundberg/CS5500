#include <cmath>
#include <catch.hpp>
#include "logger.h"
#include "dungeon.h"

TEST_CASE("We have a dungeon to work with.")
{
  ChunkList chunks;
  Dungeon::makeDungeon(chunks);
  auto dungeon_length = Dungeon::dungeonBlockLength();

  SECTION("Out of bounds dungeon blocks are inactive.")
  {
    REQUIRE(!(Dungeon::isBlockActive(chunks, -1, -1, -1)));
  }

  SECTION("Dungeon calculates chunk distances correctly.")
  {
    auto a = new Chunk(0, 0, 0);
    auto b = new Chunk(1, 3, 2);
    auto shouldBeZero = fabs(glm::distance(a->getPosition(), b->getPosition()) -
                             sqrt(pow(1, 2) + pow(3, 2) + pow(2, 2)));
    REQUIRE(shouldBeZero < 0.001);
    delete a;
    delete b;
  }

  SECTION("Make sure isBlockActive can index without segfaulting.")
  {
    auto couldBeTrueOrFalse = Dungeon::isBlockActive(
      chunks, dungeon_length - 1, dungeon_length - 1, dungeon_length - 1);

    auto theTruth = true || couldBeTrueOrFalse;
    REQUIRE(theTruth);
  }
}
