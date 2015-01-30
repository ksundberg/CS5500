#include "Camera.h"

Camera::Camera(float x, float y)
{
    CameraPosition.x = x;
    CameraPosition.y = y;
    CameraPosition.z = GetHeight(x, y);
    CameraRotation = Vector3D(0.0, 0.0, 0.0);
}

void Camera::RotateCamera(Axis axis, float angle)
{
    switch( axis )
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

float Camera::GetHeight(float x, float y)
{
    return OtherGroupsClass.GetHeight(x, y);
}