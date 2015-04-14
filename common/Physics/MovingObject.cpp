#include "MovingObject.h"

MovingObject::MovingObject(std::string id, Vector3 iniPosition)
    : currentPosition(iniPosition)
    , isMoving(true)
    , Id(id)
{}
