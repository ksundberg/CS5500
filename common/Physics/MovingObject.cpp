#include "MovingObject.h"

MovingObject::MovingObject(std::string id, Vector3 iniPosition) : Id(id), currentPosition(iniPosition), isMoving(true)
{}