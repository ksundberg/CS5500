#ifndef _GRID_H_
#define _GRID_H_

#include <vector>
#include "wxwidget.h"
#include "Point.hpp"

class Grid
{
public:
  Grid(int w, int h) : grid(w * h), width(w), height(h){};
  const Point& at(int x, int y) { return grid[idx(x, y)]; }
  void set(int x, int y, const Point& v) { grid[idx(x, y)] = v; }
  int idx(int x, int y) { return x + y * width; }

  void draw(wxDC&, int w, int h);

  std::vector<Point> grid;
  int width;
  int height;
};

#endif //_GRID_H_
