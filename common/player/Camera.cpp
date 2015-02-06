#include "Camera.h"

Camera::Camera(float x, float y, float z)
{
  CameraPosition.x = x;
  CameraPosition.y = y;
  CameraPosition.z = z;
  CameraRotation = Vector3(0.0, 0.0, 0.0);
}

void Camera::RotateCamera(Axis axis, float angle)
{
  switch (axis)
  {
  case X:
    CameraRotation.RotateAboutX(angle);
    break;
  case Y:
    CameraRotation.RotateAboutY(angle);
    break;
  case Z:
    CameraRotation.RotateAboutZ(angle);
    break;
  }
}
