/*
 * File:   rectangular_prism.h
 * Author: patrick
 *
 * Created on February 16, 2015, 4:20 PM
 */

#ifndef RECTANGULAR_PRISM_H
#define RECTANGULAR_PRISM_H

class RectangularPrism
{
public:
  RectangularPrism(int x1, int y1, int z1, int l1, int w1, int h1)
    : x(x1), y(y1), z(z1), length(l1), width(w1), height(h1){};

  int getX();
  int getY();
  int getZ();

  int getLengthX();
  int getWidthY();
  int getHeightZ();

private:
  int x, y, z;
  int length, width, height;
};

#endif /* RECTANGULAR_PRISM_H */
