#ifndef _GRID_H_
#define _GRID_H_

#include <vector>
#include "wxwidget.h"
#include "Point.hpp"
#include "PerlinNoise.h"

class Grid
{
public:
  Grid(int w, int h, int d) : grid(w * h * d), width(w), height(h), depth(d){};
  const Point& at(int x, int y, int z) { return grid[idx(x, y, z)]; }
  void set(int x, int y, int z, const Point& v) { grid[idx(x, y, z)] = v; }
  int idx(int x, int y, int z)
  {
    return (x * width * height) + (y * height) + z;
  }

  void draw(wxDC&, int w, int h, int z);
  void drawDensityMap(
    wxDC& dc, int w, int h, double lowerBound, double upperBound);

  void generateTerrain();
  std::shared_ptr<matrix2d> getDensityMap(double lowerBound, double upperBound);

  std::vector<Point> grid;
  std::shared_ptr<matrix3d> noiseMap;
  int width;
  int height;
  int depth;
};

#endif //_GRID_H_
