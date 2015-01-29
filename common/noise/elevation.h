#ifndef elevation_h
#define elevation_h

#include "PerlinNoise.h"

double elevation (double x, double y, double minElevation, double maxElevation, PerlinNoise noise, int noiseDepth);

#endif
