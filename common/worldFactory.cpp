#include "worldFactory.h"

WorldFactory::WorldFactory(int minElevation, int maxElevation, int noiseDepth)
{
  this->minElevation = minElevation;
  this->maxElevation = maxElevation;
  this->noise = PerlinNoise();
  this->noiseDepth = noiseDepth;
  //this->biosphere = Biosphere::getBasicBiosphere();
}

int WorldFactory::getMinElevation() const
{
  return minElevation;
}

int WorldFactory::getMaxElevation() const
{
  return maxElevation;
}

int WorldFactory::elevation(Vector3 v)
{
  double weight = noise.turbulence2D(v.x, v.y, noiseDepth);
  return minElevation * (1 - weight) + maxElevation * weight;
}

BlockType WorldFactory::computeBlockType(Vector3 globalXYZ){
   if(globalXYZ.z <= elevation(globalXYZ))
       return BlockType::Inactive;
   return biosphere.GetBlockType(globalXYZ.x,globalXYZ.y,globalXYZ.z);
}
