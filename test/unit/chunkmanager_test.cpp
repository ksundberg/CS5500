#include "catch.hpp"
#include "chunkmanager.h"

TEST_CASE("Chunck Manager update function test", "[float deltaTime, Vector3f cameraPosition, Vector3f cameraRotation)]")
{
	float deltaTime = 10.0;
	Vector3f camera_position(2, 3, 5);
	Vector3f camera_rotation(6, 5, 9);

	ChunkManager Manager_test;

	Manager_test.Update(deltaTime, camera_position, camera_rotation);
	REQUIRE(Manager_test.chunkRenderList == Manager_test.pChunkVisibilityList);

	ChunkList previous_render_list = Manager_test.chunkRenderList;
	ChunkList previous_visability_list = Manager_test.pChunkVisibilityList;

	camera_rotation.setX(70);
	camera_rotation.setY(130);
	camera_rotation.setZ(150);

	camera_position.setX(56.7);
	camera_position.setY(67.8);
	camera_position.setZ(87.5);

	Manager_test.Update(deltaTime, camera_position, camera_rotation);
	REQUIRE(Manager_test.chunkRenderList == Manager_test.pChunkVisibilityList);
}