#include "vector3f.h"
#include <cmath>

Vector3f::Vector3f()
{
	X = 0;
	Y = 0;
	Z = 0;
}

Vector3f::Vector3f(const float x, const float y, const float z)
{
	X = x;
	Y = y;
	Z = z;
}

Vector3f::Vector3f(const float vect[3])
{
	X = vect[0];
	Y = vect[1];
	Z = vect[2];
}

float Vector3f::getX()
{
	return X;
}

void Vector3f::setX(const float newX)
{
	X = newX;
}

float Vector3f::getY()
{
	return Y;
}

void Vector3f::setY(const float newY)
{
	Y = newY;
}

float Vector3f::getZ()
{
	return Z;
}

void Vector3f::setZ(const float newZ)
{
	Z = newZ;
}

bool Vector3f::equals(Vector3f compare_to)
{
	bool xeq, yeq, zeq;
	xeq = X == compare_to.getX();
	yeq = Y == compare_to.getY();
	zeq = Z == compare_to.getZ();
	if ( xeq && yeq && zeq)
	{
		return true;
	}
	else
	{
		return false;
	}
}