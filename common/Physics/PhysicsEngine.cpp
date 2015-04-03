#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{}

void PhysicsEngine::Create(RectangularPrism prism)
{
	for (int i = prism.getX(); i < prism.getLengthX(); ++i)
	{
		for (int j = prism.getY(); j < prism.getWidthY(); ++j)
		{
			for (int k = prism.getZ(); k < prism.getHeightZ(); ++k)
			{
				auto position = Vector3((float)i, (float)j, (float)k);
				objList[position] = MovingObject(position);
				activeList.push_back(position);
			}
		}
	}
}

void PhysicsEngine::Destroy(RectangularPrism prism)
{
	for (int i = prism.getX(); i < prism.getLengthX(); ++i)
	{
		for (int j = prism.getY(); j < prism.getWidthY(); ++j)
		{
			for (int k = prism.getZ(); k < prism.getHeightZ(); ++k)
			{
				auto position = Vector3((float)i, (float)j, (float)k);
				objList.erase(position);
				Remove(position);
			}
		}
	}
}

void PhysicsEngine::UpdateSingle(MovingObject& obj, int dt)
{
	Vector3 defaultVector(0.0f, 0.0f, 0.0f);
	obj.changeInPosition = defaultVector;
	Vector3 force = SumForces(obj);

	if (force != defaultVector)
	{
		if (!obj.isMoving)
		{
			obj.isMoving = true;
			activeList.push_back(obj.Id);
		}
		auto mass = obj.mass;
		auto lastAcceleration = obj.acceleration;
		auto velocity = obj.velocity;

		obj.changeInPosition += (velocity * dt) + (lastAcceleration * (0.5f * dt * dt));
		auto newAcceleration = force / mass;
		auto avgAcceleration = (lastAcceleration + newAcceleration) / 2.0f;
		velocity += avgAcceleration * dt;

		obj.velocity = velocity;
		obj.acceleration = avgAcceleration;
		UpdatePosition(obj);
	}
	else
	{
		if (obj.isMoving)
		{
			obj.isMoving = false;
			Remove(obj.Id);
		}
	}
}

//set unstable = true if you want all the blocks in the list to be considered in motion
void PhysicsEngine::Update(RectangularPrism prism, int dt, bool unstable = false)
{
	std::vector<Vector3> blocks;

	for (int i = prism.getX(); i < prism.getLengthX(); ++i)
	{
		for (int j = prism.getY(); j < prism.getWidthY(); ++j)
		{
			for (int k = prism.getZ(); k < prism.getHeightZ(); ++k)
			{
				auto position = Vector3((float)i, (float)j, (float)k);
				blocks.push_back(position);
			}
		}
	}

	if (!unstable)
	{
		//Find which blocks are moving and update
		tbb::parallel_for(tbb::blocked_range<int>(0, blocks.size()),
			[&](const tbb : blocked_range<int>& r)
		{
			for (int i = r.begin(); i < r.end(); ++i)
			{
				if (objList[blocks[i]].isMoving)
				{
					UpdateSingle(objList[blocks[i]], dt);
				}
			}
		});
	}
	else
	{
		//Consider all blocks in motion and run physics on all
		tbb::parallel_for(tbb::blocked_range<int>(0, blocks.size()),
			[&](const tbb : blocked_range<int>& r)
		{
			for (int i = r.begin(); i < r.end(); ++i)
			{
				UpdateSingle(objList[blocks[i]], dt);
			}
		});
	}
}

void PhysicsEngine::UpdateActive(int dt)
{
	tbb::parallel_for(tbb::blocked_range<int>(0, activeList.size()),
		[&](const tbb : blocked_range<int>& r)
	{
		for (int i = r.begin(); i < r.end(); ++i)
		{
			UpdateSingle(objList[activeList[i]], dt);
		}
	});
}

void PhysicsEngine::Remove(Vector3 id)
{
	for (int i = 0; i < activeList.size(); ++i)
	{
		if (activeList[i] == id)
		{
			activeList.erase(activeList.begin() + i);
			return;
		}
	}
}

Vector3 PhysicsEngine::CalculateGravity(MovingObject obj)
{
	// F = ma
	auto mass = obj.mass;

	float force = (mass * 9.81f) * -1.0f;

	Vector3 temp(0.0f, 0.0f, force);

	return temp;
}

Vector3 PhysicsEngine::CalculateAirDrag(MovingObject obj)
{
	// set up constant values
	auto area = 1.0f;  // 1 meter?
	auto drag = 1.05f; // wiki drag coefficient for cube
	auto rho = 1.2f;   // air density

	auto vel = obj.velocity;

	// calculate drag in just z for now
	auto force = (vel * vel) * (0.5f * rho * drag * area);

	Vector3 temp(0.0f, 0.0f, force);

	// return resulting force vector
	return temp;
}

Vector3 PhysicsEngine::CalculateFriction(MovingObject obj)
{
	// Could read in coefficients of frictions from the materials guys but
	// for now we'll just use 0.5 (wood on wood)
	Vector3 direction = obj.velocity.Normalize() * -1.0f;

	float friction = obj.mass * 9.81f * 0.5f;

	// friction will always opose the direction the object is moving
	return direction * friction;
}

Vector3 PhysicsEngine::SumForces(MovingObject obj)
{
	// Find all the forces on a given object
	Vector3 forces(0.0f, 0.0f, 0.0f);

	// if falling Calculate Force due to gravity and factor in air drag
	if (IsFalling(obj))
	{
		forces = CalculateGravity(obj);
		forces += CalculateAirDrag(obj);
	}
	else
	{
		obj.velocity.z = 0.0f;

		// if moving in x or y along ground calculate friction
		if (IsSliding(obj))
		{
			forces = CalculateFriction(obj);
		}
	}

	return forces;
}

bool PhysicsEngine::IsFalling(MovingObject obj)
{
	// Will need to lookup object position in the object datastructure
	// and determine if the other blocks around it can support it.
	// This will be a stencil

	// Since this datastructure doesn't exist yet...
	auto remove_warning = (obj.velocity.z + 0.0f);
	return remove_warning == 0.0f;
}

bool PhysicsEngine::IsSliding(MovingObject obj)
{
	if (obj.velocity.x > 0.0f || obj.velocity.y > 0.0f ||
		obj.velocity.x < 0.0f || obj.velocity.y < 0.0f)
		return true;
	else
		return false;
}

void PhysicsEngine::UpdatePosition(MovingObject& obj)
{
	Vector3 defaultVector(0.0f, 0.0f, 0.0f);

	auto newPosition = obj.Id + obj.changeInPosition;
	MovingObject newBlock(newPosition);
	newBlock.acceleration = obj.acceleration;
	newBlock.velocity = obj.velocity;
	newBlock.isMoving = obj.isMoving;
	newBlock.mass = obj.mass;

	obj.acceleration = defaultVector;
	obj.velocity = defaultVector;
	obj.isMoving = false;
	obj.mass = 0;

	objList[newBlock.Id] = newBlock;

	//Lookup block by Id and update position
}
