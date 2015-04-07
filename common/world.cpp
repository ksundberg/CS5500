#include "logger.h"
#include <tbb/tbb.h>

#include "world.h"
#include "PerlinNoise.h"



std::shared_ptr<Block> World::_critterBlock = nullptr;

std::vector<std::shared_ptr<IVContainer>> World::Containers() const
{
  auto containers = std::vector<std::shared_ptr<IVContainer>>();
  for (auto c : critters)
    containers.emplace_back(std::dynamic_pointer_cast<IVContainer>(c));

  return containers;
}

std::shared_ptr<World> World::Generate(int size, int height, int critterCount)
{
  std::srand(std::time(0));
  if (_critterBlock == nullptr)
    _critterBlock =
      std::make_shared<Block>(glm::vec3(0, 0, 0), BlockType::Grass);

  auto world = std::make_shared<World>();
  world->_noise = PerlinNoise::matrix2D(size, size, height);
  world->blocks.reserve(size * size * height);
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
    {
      int h = (*world->_noise)[i][j] * height;
      for (int k = 0; k <= h; k++)
        world->blocks.emplace_back(std::make_shared<Block>(
          glm::vec3(float(i), float(k), float(j)), BlockType(k)));
    }

  world->critters.reserve(critterCount);
  for (int i = 0; i < critterCount; i++)
    world->critters.emplace_back(std::make_shared<Critter>(
      glm::vec3(int(std::rand()) % size, 0, int(std::rand()) % size),
      std::dynamic_pointer_cast<IVContainer>(_critterBlock)));

  world->_size = size;
  world->_height = height;
  return world;
}

// Called every update loop
tbb::queuing_rw_mutex mutex;

void World::Update()
{
  tbb::parallel_for(
    tbb::blocked_range<int>(0, critters.size()),
    [=](const tbb::blocked_range<int>& ri)
    {
      for (int i = ri.begin(); i != ri.end(); i++)
      {
        auto c = critters[i];
        auto p = c->Position();
        if (int(p.x) <= 0 || int(p.x) >= _size)
        {
          c->dir.x = -c->dir.x;
          if (p.x >= _size)
          {
            p.x = _size - 0.1;
          }
          else
          {
            p.x = 0.1;
          }
        }
        if (int(p.z) <= 0 || int(p.z) >= _size)
        {
          c->dir.y = -c->dir.y;
          if (p.z >= _size)
            p.z = _size - 0.1;
          else
            p.z = 0.1;
        }
        if (std::rand() % 100 == 0) c->dir.x = std::rand() % 3 - 1;
        if (std::rand() % 100 == 0) c->dir.y = std::rand() % 3 - 1;

        double critterYPosition = (*_noise)[int(p.x)][int(p.z)] * _height + 1;
        c->move(glm::vec3(0.1, critterYPosition, 0.1));

        // Collision detection
        for (auto c2 : critters)
        {
          tbb::queuing_rw_mutex::scoped_lock lock(mutex, false);
          auto p1 = c->Position();
          auto p2 = c2->Position();

          if ((abs(p1.x - p2.x) * 2 < 2) && (abs(p1.y - p2.y) * 2 < 2) &&
              (abs(p1.z - p2.z) * 2 < 2))
          {
            if (c != c2)
            {
              c->dir.x *= -1;
              c->dir.y *= -1;
              lock.upgrade_to_writer();
              c->move(glm::vec3(0.2, critterYPosition, 0.2));
              break;
            }
          }
        }
      }
    });
}
