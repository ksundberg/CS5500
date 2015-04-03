
#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "../util/vector3.h"

class MovingObject
{
public:
	MovingObject(Vector3 iniPosition);
	double mass;          // in kg
	Vector3 acceleration; // in m/s^2
	Vector3 velocity;     // in m/s
	Vector3 changeInPosition;
	bool isMoving;
	Vector3 Id;
};

#endif
