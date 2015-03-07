// http://buildnewgames.com/gamephysics/

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "block.h"
#include "vector3.h"
#include <vector>
#include <algorithm>
#include "tbb/parallel_for.h"

class PhysicsEngine
{
public:
  PhysicsEngine(float deltaTime);
  void UpdateSingle(Block block, Vector3 force);
  void UpdateChunk(std::vector<Block> blockList);

private:
  float dt;
  Vector3 CalculateGravity(Block block);
  Vector3 CalculateFriction(Block block);
  Vector3 CalculateAirDrag(Block block);
  Vector3 SumForces(Block block);
  bool IsFalling(Block block);
  bool IsMoving(Block block);
};

#endif