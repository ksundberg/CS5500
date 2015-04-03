#ifndef __CRITTER_H_
#define __CRITTER_H_

#include "vector3.h"

class Critter
{
public:
  Critter(Vector3 pos);
  virtual ~Critter();

  Vector3 pos;
};
#endif //__CRITTER_H_
