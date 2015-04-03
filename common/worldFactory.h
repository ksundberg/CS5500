#ifndef WorldFactory_h
#define WorldFactory_h

#include "noise/PerlinNoise.h"
#include "voxel/block.h"
#include "vector3.h"
#include "MaterialContainer.h"

// thread unsafe
class WorldFactory
{
public:
  WorldFactory(int, int, int);
  int getMinElevation() const;
  int getMaxElevation() const;
  int elevation(Vector3 v);
  BlockType computeBlockType(Vector3 globalXYZ);

private:
  Biosphere biosphere = Biosphere::getBasicBiosphere ();
  int minElevation, maxElevation;
  PerlinNoise noise;
  int noiseDepth;
};

#endif
