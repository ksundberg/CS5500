#ifndef BLOCK_H
#define BLOCK_H

#include "vector3.h"

enum BlockType
{
  Inactive = 0,
  Ground,
  Water,
  Sand,
  Wood,
  Flowers,
  Ruby,
  Leaves,
  Stone,
  Grass,
  Brick,
  Party
};

class Block
{
public:
  Block();
  virtual ~Block();

  double mass;          // in kg
  Vector3 acceleration; // in m/s^2
  Vector3 velocity;     // in m/s
  Vector3 position;
  BlockType type;

};

#endif
