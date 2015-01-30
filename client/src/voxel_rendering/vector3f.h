#ifndef VECTOR3F_H
#define VECTOR3F_H

class Vector3f
{
	private:
	float X;
	float Y;
	float Z;

	public:
	Vector3f();
	Vector3f(const float x, const float y, const float z);
	Vector3f(const float vect[3]);

	float getX();
	void setX(const float newX);

	float getY();
	void setY(const float newY);

	float getZ();
	void setZ(const float newZ);

	bool equals(Vector3f compare_to);
};


#endif