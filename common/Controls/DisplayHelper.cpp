#include <chunkmanager.h>
#include "DisplayHelper.h"

DisplayHelper::DisplayHelper()
{
}

void DisplayHelper::Render(float dt,
                           Vector3 cameraPosisiton,
                           Vector3 cameraRotation)
{
  auto chunkManager = ChunkManager();
  auto chunkManagerMini = ChunkManager();
  chunkManager.Update(dt, cameraPosisiton, cameraRotation);
  chunkManagerMini.Update(dt, cameraPosisiton, cameraRotation);
}
