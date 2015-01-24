#include "../common/Vector/Vector3D.h"

enum Axis
{
    X,
    Y,
    Z
};

class Camera
{
    public:
        Camera(float x, float y);
    private:
        void RotateCamera(Axis axis, float angle);
        float GetHeight(float x, float y);
        float dt;
        Vector3D CameraPosition;
        Vector3D CameraRotation;
};