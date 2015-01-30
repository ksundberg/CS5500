#include "elevation.h"

double elevation (double x, double y, double minElevation, double maxElevation, PerlinNoise noise, int noiseDepth){
  double weight = noise.turbulence2D(x, y, noiseDepth);
  return minElevation * (1-weight) + maxElevation * weight;
}
