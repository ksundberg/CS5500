// http://buildnewgames.com/gamephysics/

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "MovingObject.h"
#include <vector>
#include <algorithm>
#include "tbb/parallel_for.h"
#include "../object.h"
#include "../world.h"
#include "../util/vector3.h"
#include "../density/rectangular_prism.h"
#include <map>
#include <math.h>

class PhysicsEngine
{
public:
	PhysicsEngine();
	void Update(std::vector<int> blocks, int dt, bool unstable = false);
	void UpdateActive(int dt);
	void Create(RectangularPrism prism);
	void Destroy(RectangularPrism prism);
	void ApplyForce(RectangularPrism prism, Vector3 force);
private:
	void UpdateSingle(MovingObject& obj, int dt);
	Vector3 CalculateGravity(MovingObject obj);
	Vector3 CalculateFriction(MovingObject obj);
	Vector3 CalculateAirDrag(MovingObject obj);
	Vector3 SumForces(MovingObject obj);
	bool IsFalling(MovingObject obj);
	bool IsSliding(MovingObject obj);
	std::vector<std::string> activeList;
	void Remove(std::string id);
	std::map<std::string, MovingObject> objList;
	void UpdatePosition(MovingObject& obj);
};

#endif