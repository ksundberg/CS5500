#ifndef WorldFactory_h
#define WorldFactory_h

#include "noise/PerlinNoise.h"

// thread unsafe
class WorldFactory
{
public:
  WorldFactory(int, int);
  int getMinElevation() const;
  int getMaxElevation() const;
  int elevation(int x, int y, PerlinNoise noise, int noiseDepth);

private:
  int minElevation, maxElevation;
};
#endif
