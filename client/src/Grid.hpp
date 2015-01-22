#ifndef _GRID_H_
#define _GRID_H_

#include <vector>
#include "wxwidget.h"

class Grid
{
public:
  Grid(int w, int h) : grid(w * h), width(w), height(h){};
  double at(int x, int y) { return grid[idx(x, y)]; }
  void set(int x, int y, int v) { grid[idx(x, y)] = v; }
  int idx(int x, int y) { return x + y * width; }

  void draw(wxDC&);

  std::vector<double> grid;
  int width;
  int height;
};

#endif //_GRID_H_
