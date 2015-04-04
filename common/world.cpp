#include "world.h"

#include "PerlinNoise.h"

std::vector<std::shared_ptr<IVContainer>> World::Containers() const
{
  auto containers = std::vector<std::shared_ptr<IVContainer>>();
  for (auto c : critters)
    containers.emplace_back(std::dynamic_pointer_cast<IVContainer>(c));

  return containers;
}

std::shared_ptr<World> World::Generate(int size, int height)
{
  auto world = std::make_shared<World>();
  auto noiseMap = PerlinNoise::matrix2D(size, size, height);
  world->blocks.reserve(size * size * height);
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
    {
      int h = (*noiseMap)[i][j] * height;
      for (int k = 0; k <= h; k++)
        world->blocks.emplace_back(
          Block({float(i), float(k), float(j)}, BlockType(k)));
    }

  world->critters.emplace_back(std::make_shared<Critter>(glm::vec3(0, -12, 0)));

  return world;
}

//Called every update loop
void World::Update()
{
}
