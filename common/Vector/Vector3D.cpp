#include "Vector3D.h"
#include <math.h>

Vector3D::Vector3D()
{}

Vector3D::Vector3D(float newX, float newY, float newZ)
    :x(newX),
    y(newY),
    z(newZ)
{}

Vector3D& Vector3D::Set(float newX, float newY, float newZ)
{
    x = newX;
    y = newY;
    z = newZ;
    return (*this);
}

Vector3D& Vector3D::operator +=(const Vector3D& vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return (*this);
}

Vector3D& Vector3D::operator -=(const Vector3D& vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    return (*this);
}

Vector3D& Vector3D::operator *=(float t)
{
    x *= t;
    y *= t;
    z *= t;
    return (*this);
}

Vector3D& Vector3D::operator /=(float t)
{
    float f = 1.0F / t;
    x *= f;
    y *= f;
    z *= f;
    return (*this);
}

Vector3D& Vector3D::operator &=(const Vector3D& vector)
{
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;
    return (*this);
}
        
Vector3D Vector3D::operator -() const
{
    return (Vector3D(-x, -y, -z));
}
        
Vector3D Vector3D::operator +(const Vector3D& vector) const
{
    return (Vector3D(x + vector.x, y + vector.y, z + vector.z));
}
        
Vector3D Vector3D::operator -(const Vector3D& vector) const
{
    return (Vector3D(x - vector.x, y - vector.y, z - vector.z));
}
        
Vector3D Vector3D::operator *(float t) const
{
    return (Vector3D(x * t, y * t, z * t));
}
        
Vector3D Vector3D::operator /(float t) const
{
    float f = 1.0F / t;
    return (Vector3D(x * f, y * f, z * f));
}
        
float Vector3D::operator *(const Vector3D& vector) const
{
    return (x * vector.x + y * vector.y + z * vector.z);
}
        
Vector3D Vector3D::operator %(const Vector3D& vector) const
{
    return (Vector3D(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x));
}
        
Vector3D Vector3D::operator &(const Vector3D& vector) const
{
    return (Vector3D(x * vector.x, y * vector.y, z * vector.z));
}
        
bool Vector3D::operator ==(const Vector3D& vector) const
{
    return ((x == vector.x) && (y == vector.y) && (z == vector.z));
}
        
bool Vector3D::operator !=(const Vector3D& vector) const
{
    return ((x != vector.x) || (y != vector.y) || (z != vector.z));
}
        
Vector3D& Vector3D::Normalize()
{
    return (*this /= sqrtf(x * x + y * y + z * z));
}
        
Vector3D& Vector3D::RotateAboutX(float angle)
{
    float angleSin = sinf(angle);
    float angleCos = cosf(angle);
    
    float newY = angleCos * y - angleSin * z;
    float newZ = angleCos * z + angleSin * y;
    
    y = newY;
    z = newZ;
    
    return (*this);
}

Vector3D& Vector3D::RotateAboutY(float angle)
{
    float angleSin = sinf(angle);
    float angleCos = cosf(angle);
    
    float newX = angleCos * x + angleSin * z;
    float newZ = angleCos * z - angleSin * x;
    
    x = newX;
    z = newZ;
    
    return (*this);
}

Vector3D& Vector3D::RotateAboutZ(float angle)
{
    float angleSin = sinf(angle);
    float angleCos = cosf(angle);
    
    float newX = angleCos * x - angleSin * y;
    float newY = angleCos * y + angleSin * x;
    
    x = newX;
    y = newY;
    
    return (*this);
}

Vector3D& Vector3D::RotateAboutAxis(float angle, const Vector3D& axis)
{
    float angleSin = sinf(angle);
    float angleCos = cosf(angle);
    float tempConst = 1.0F - angleCos;
    
    float newX = x * (angleCos + tempConst * axis.x * axis.x) + y * (tempConst * axis.x * axis.y - angleSin * axis.z) + z * (tempConst * axis.x * axis.z + angleSin * axis.y);
    float newY = x * (tempConst * axis.x * axis.y + angleSin * axis.z) + y * (angleCos + tempConst * axis.y * axis.y) + z * (tempConst * axis.y * axis.z - angleSin * axis.x);
    float newZ = x * (tempConst * axis.x * axis.z - angleSin * axis.y) + y * (tempConst * axis.y * axis.z + angleSin * axis.x) + tempConst * (angleCos + tempConst * axis.z * axis.z);
    
    x = newX;
    y = newY;
    z = newZ;
    
    return (*this);
}