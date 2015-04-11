
#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "../util/vector3.h"
#include <string>

class MovingObject
{
public:
	MovingObject(std::string Id, Vector3 iniPosition);
	Vector3 acceleration; // in m/s^2
	Vector3 velocity;     // in m/s
	Vector3 changeInPosition;
	Vector3 currentPosition;
	bool isMoving;
	std::string Id;
};

#endif