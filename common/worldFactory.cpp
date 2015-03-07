#include "worldFactory.h"

WorldFactory::WorldFactory(int tempMinElevation, int tempMaxElevation)
{
  minElevation = tempMinElevation;
  maxElevation = tempMaxElevation;
}

int WorldFactory::getMinElevation() const
{
  return minElevation;
}

int WorldFactory::getMaxElevation() const
{
  return maxElevation;
}

int WorldFactory::elevation(int x, int y, PerlinNoise noise, int noiseDepth)
{
  double weight = noise.turbulence2D(x, y, noiseDepth);
  return minElevation * (1 - weight) + maxElevation * weight;
}
