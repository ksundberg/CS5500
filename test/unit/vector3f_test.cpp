#include <catch.hpp>

#include "vector3.h"

TEST_CASE("Vector blank creation/modification", "[Vector3]")
{
  Vector3 v_test;

  REQUIRE(v_test.x == 0);
  REQUIRE(v_test.y == 0);
  REQUIRE(v_test.z == 0);
}

TEST_CASE("Create Vector3 with arguments", "[Vector3(x,y,z)]")
{
  float x = 45.67;
  float y = 23.89;
  float z = 108.0;
  Vector3 v_test(x, y, z);

  REQUIRE(v_test.x == x);
  REQUIRE(v_test.y == y);
  REQUIRE(v_test.z == z);
}

TEST_CASE("Test vetor3f equals logic", "[Vector3(x1,y1,z1), Vector3(x2,y2,z2)]")
{
  float x = 12.3;
  float y = 23.4;
  float z = 34.5;
  float x1 = 12.2;
  Vector3 v_test1(x, y, z);
  Vector3 v_test2(x, y, z);

  REQUIRE(v_test1 == v_test1);
  v_test2.x = x1;
  REQUIRE(v_test2 != v_test1);
}
