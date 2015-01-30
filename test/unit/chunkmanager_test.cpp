#include <catch.hpp>
#include "chunkmanager.h"

TEST_CASE("Chunk Manager update function test", "[float deltaTime, Vector3 cameraPosition, Vector3 cameraRotation)]")
{
	float deltaTime = 10.0;
	Vector3 camera_position(2, 3, 5);
	Vector3 camera_rotation(6, 5, 9);

	ChunkManager Manager_test;

	Manager_test.Update(deltaTime, camera_position, camera_rotation);
	REQUIRE(Manager_test.chunkRenderList == Manager_test.pChunkVisibilityList);

	ChunkList previous_render_list = Manager_test.chunkRenderList;
	ChunkList previous_visability_list = Manager_test.pChunkVisibilityList;

	camera_rotation.x = 70;
	camera_rotation.y = 130;
	camera_rotation.z = 150;

	camera_position.x = 56.7;
	camera_position.y = 67.8;
	camera_position.z = 87.5;

	Manager_test.Update(deltaTime, camera_position, camera_rotation);
	REQUIRE(Manager_test.chunkRenderList == Manager_test.pChunkVisibilityList);
}
