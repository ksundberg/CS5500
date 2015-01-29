#ifndef  CATCH_CONFIG_MAIN
#define  CATCH_CONFIG_MAIN
#endif

#include "vector3f.h"
#include "catch.hpp"

TEST_CASE("Vector blank creation/modification", "[vector3f]")
{
	Vector3f v_test;

	REQUIRE(v_test.getX() == 0);
	REQUIRE(v_test.getY() == 0);
	REQUIRE(v_test.getZ() == 0);

	SECTION("Modify a Vector3f")
	{

		float x1 = 23.5;
		float y1 = 49.7;
		float z1 = 76.89;

		v_test.setX(x1);
		REQUIRE(v_test.getX() == x1);

		v_test.setY(y1);
		REQUIRE(v_test.getY() == y1);

		v_test.setZ(z1);
		REQUIRE(v_test.getZ() == z1);
	}
}

TEST_CASE("Create vector3f with arguments", "[Vector3f(x,y,z)]")
{
	float x = 45.67;
	float y = 23.89;
	float z = 108.0;
	Vector3f v_test(x, y, z); 

	REQUIRE(v_test.getX() == x);
	REQUIRE(v_test.getY() == y);
	REQUIRE(v_test.getZ() == z);
}

TEST_CASE("Test vetor3f equals logic", "[Vector3f(x1,y1,z1), Vector3f(x2,y2,z2)]")
{
	float x = 12.3;
	float y = 23.4;
	float z = 34.5;
	float x1 = 12.2;
	Vector3f v_test1(x, y, z);
	Vector3f v_test2(x, y, z);

	REQUIRE(v_test1.equals(v_test1) == true);
	v_test2.setX(x1);
	REQUIRE(v_test2.equals(v_test1) == false);
}