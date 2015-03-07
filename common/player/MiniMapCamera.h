#include <vector3.h>
enum Axis
{
  X,
  Y,
  Z
};

class MiniMapCamera
{
public:
  MiniMapCamera(float x, float y, float z);
  auto getDensityOfChunk = ()[]{

  };

private:
  Vector3 CameraPosition;
  Vector3 CameraRotation;
};
