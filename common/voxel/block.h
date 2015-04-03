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
  // We really should delete this and force a block to only be constructed when
  // we know its type and position
  // ie. Block() = delete;
  Block();
  Block(Vector3 p, BlockType t) : position(p), type(t) {}
  virtual ~Block();

  // important members
  Vector3 position;
  BlockType type;

  // unimportant members
  double mass;          // in kg
  Vector3 acceleration; // in m/s^2
  Vector3 velocity;     // in m/s
};

#endif
