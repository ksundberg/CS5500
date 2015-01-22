#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <algorithm>

class Point
{
public:
  Point() {}

  Point(double x, double y, double z)
  {
    data[0] = x;
    data[1] = y;
    data[2] = z;
  }

  Point(const Point& copy)
  {
    for (int i = 0; i < 3; i++)
      data[i] = copy.data[i];
  }

  Point& operator=(const Point& copy)
  {
    for (int i = 0; i < 3; i++)
      data[i] = copy.data[i];
    return *this;
  }

  ~Point() {}

  double x() const { return data[0]; }
  double y() const { return data[1]; }
  double z() const { return data[2]; }

  double length() const
  {
    return sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
  }
  Point operator+(const Point& p) const
  {
    return Point(data[0] + p.data[0], data[1] + p.data[1], data[2] + p.data[2]);
  }

  Point& operator*(double v)
  {
    data[0] *= v;
    data[1] *= v;
    data[2] *= v;
    return *this;
  }
  Point& operator*(const Point& v)
  {
    data[0] *= v.x();
    data[1] *= v.y();
    data[2] *= v.z();
    return *this;
  }

private:
  double data[3];
};

inline Point Min(const Point& p1, const Point& p2)
{
  return Point(std::min(p1.x(), p2.x()),
               std::min(p1.y(), p2.y()),
               std::min(p1.z(), p2.z()));
}

inline Point Max(const Point& p1, const Point& p2)
{
  return Point(std::max(p1.x(), p2.x()),
               std::max(p1.y(), p2.y()),
               std::max(p1.z(), p2.z()));
}

#endif //_POINT_HPP_
