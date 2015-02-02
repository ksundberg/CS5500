//Implementation found on http://www.terathon.com/code/vector3d.html
class Vector3D
{
    public:
        float x;
        float y;
        float z;
        
        Vector3D();
        
        Vector3D(float r, float s, float t);
        
        Vector3D& Set(float r, float s, float t);
        
        Vector3D& operator +=(const Vector3D& vector);
        
        Vector3D& operator -=(const Vector3D& vector);
        
        Vector3D& operator *=(float t);
        
        Vector3D& operator /=(float t);
        
        Vector3D& operator &=(const Vector3D& vector);
        
        Vector3D operator -() const;
        
        Vector3D operator +(const Vector3D& vector) const;
        
        Vector3D operator -(const Vector3D& vector) const;
        
        Vector3D operator *(float t) const;
        
        Vector3D operator /(float t) const;
        
        float operator *(const Vector3D& vector) const;
        
        Vector3D operator %(const Vector3D& vector) const;
        
        Vector3D operator &(const Vector3D& vector) const;
        
        bool operator ==(const Vector3D& vector) const;
        
        bool operator !=(const Vector3D& vector) const;
        
        Vector3D& Normalize();
        
        Vector3D& RotateAboutX(float angle);
        Vector3D& RotateAboutY(float angle);
        Vector3D& RotateAboutZ(float angle);
        Vector3D& RotateAboutAxis(float angle, const Vector3D& axis);
};