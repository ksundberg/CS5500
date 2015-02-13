#include <catch.hpp>
#include "dungeon.h"
#include "logger.h"

TEST_CASE("The bottom of a dungeon contains active blocks.")
{
  Dungeon dungeon;
  REQUIRE(dungeon.isActive(0,0,0));
}
