#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(float deltaTime) : dt(deltaTime)
{
}

void PhysicsEngine::UpdateSingle(Block block, Vector3 force)
{
  Vector3 position(0.0f, 0.0f, 0.0f); // will come from block datastructure
  auto mass = block.mass;
  auto lastAcceleration = block.acceleration;
  auto velocity = block.velocity;

  position += (velocity * dt) + (lastAcceleration * (0.5f * dt * dt));
  auto newAcceleration = force / mass;
  auto avgAcceleration = (lastAcceleration + newAcceleration) / 2.0f;
  velocity += avgAcceleration * dt;

  block.velocity = velocity;
  block.acceleration = avgAcceleration;

  // Somehow apply position move to voxel datastructure
  // datastructure has not been implemented yet
}

void PhysicsEngine::UpdateChunk(std::vector<Block> blockList)
{
  // Position of blocks is held in block datastructure which hasn't been
  // implemented yet.
  // std::sort(blockList.begin(), blockList.end(), [](){}); //sort block list
  // based on lowest height

  std::vector<Vector3> forceList;

  for (unsigned j = 0; j < blockList.size(); ++j)
  {
    forceList.push_back(SumForces(blockList[j]));
  }

  tbb::parallel_for(tbb::blocked_range<int>(0, blockList.size()),
                    [&](const tbb::blocked_range<int>& r)
                    {
    for (int i = r.begin(); i < r.end(); ++i)
    {
      UpdateSingle(blockList[i], forceList[i]);
    }
  });
}

Vector3 PhysicsEngine::CalculateGravity(Block block)
{
  // F = ma
  auto mass = block.mass;

  float force = (mass * 9.81f) * -1.0f;

  Vector3 temp(0.0f, 0.0f, force);

  return temp;
}

Vector3 PhysicsEngine::CalculateAirDrag(Block block)
{
  // set up constant values
  auto area = 1.0f; // 1 meter?
  auto drag = 1.05f; // wiki drag coefficient for cube
  auto rho = 1.2f; // air density

  auto vel = block.velocity;

  // calculate drag in just z for now
  auto force = (vel * vel) * (0.5f * rho * drag * area);

  Vector3 temp(0.0f, 0.0f, force);

  // return resulting force vector
  return temp;
}

Vector3 PhysicsEngine::CalculateFriction(Block block)
{
  // Could read in coefficients of frictions from the materials guys but
  // for now we'll just use 0.5 (wood on wood)
  Vector3 direction = block.velocity.Normalize() * -1.0f;

  float friction = block.mass * 9.81f * 0.5f;

  // friction will always opose the direction the block is moving
  return direction * friction;
}

Vector3 PhysicsEngine::SumForces(Block block)
{
  // Find all the forces on a given object
  Vector3 forces(0.0f, 0.0f, 0.0f);

  // if falling Calculate Force due to gravity and factor in air drag
  if (block.velocity.z < 0.0f || block.velocity.z > 0.0f)
  {
    forces = CalculateGravity(block);
    forces += CalculateAirDrag(block);
  }
  // if moving (but not in freefall) calculate friction
  else if (IsMoving(block))
  {
    forces = CalculateFriction(block);
  }
  // sum up the Vector for all

  return forces;
}

bool PhysicsEngine::IsFalling(Block block)
{
  // Will need to lookup block position in the block datastructure
  // and determine if the other blocks around it can support it.
  // This will be a stencil

  // Since this datastructure doesn't exist yet...
  auto remove_warning = block.IsActive();
  return !remove_warning;
}

bool PhysicsEngine::IsMoving(Block block)
{
  if (block.velocity.x > 0.0f || block.velocity.y > 0.0f ||
      block.velocity.x < 0.0f || block.velocity.y < 0.0f)
    return true;
  else
    return false;
}