#ifndef _VECTOR3_H_
#define _VECTOR3_H_

//Implementation found on http://www.terathon.com/code/vector3d.html
class Vector3
{
    public:
        float x;
        float y;
        float z;
        
        Vector3();
        
        Vector3(float r, float s, float t);
        
        Vector3& Set(float r, float s, float t);
        
        Vector3& operator +=(const Vector3& vector);
        
        Vector3& operator -=(const Vector3& vector);
        
        Vector3& operator *=(float t);
        
        Vector3& operator /=(float t);
        
        Vector3& operator &=(const Vector3& vector);
        
        Vector3 operator -() const;
        
        Vector3 operator +(const Vector3& vector) const;
        
        Vector3 operator -(const Vector3& vector) const;
        
        Vector3 operator *(float t) const;
        
        Vector3 operator /(float t) const;
        
        float operator *(const Vector3& vector) const;
        
        Vector3 operator %(const Vector3& vector) const;
        
        Vector3 operator &(const Vector3& vector) const;
        
        bool operator ==(const Vector3& vector) const;
        
        bool operator !=(const Vector3& vector) const;
        
        Vector3& Normalize();
        
        Vector3& RotateAboutX(float angle);
        Vector3& RotateAboutY(float angle);
        Vector3& RotateAboutZ(float angle);
        Vector3& RotateAboutAxis(float angle, const Vector3& axis);
};

#endif //_VECTOR3_H_
