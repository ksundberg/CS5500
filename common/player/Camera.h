#include <vector3.h>

enum Axis
{
  X,
  Y,
  Z
};

class Camera
{
public:
  Camera(float x, float y, float z);

private:
  void RotateCamera(Axis axis, float angle);
  Vector3 CameraPosition;
  Vector3 CameraRotation;
};
