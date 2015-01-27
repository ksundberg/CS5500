#include "DisplayHelper.h"

DisplayHelper::DisplayHelper()
{}

void DisplayHelper::Render(float dt, Vector3D cameraPosisiton, Vector3D cameraRotation)
{
    auto chunkManager = ChunkManager();
    chunkManager.Update(dt, cameraPosisiton, cameraRotation);
}
