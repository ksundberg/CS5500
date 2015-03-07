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
  ~Block();

  BlockType get();
  void set(BlockType type);

  double mass;          // in kg
  Vector3 acceleration; // in m/s^2
  Vector3 velocity;     // in m/s

private:
  BlockType type;

  //		BlockType mBlockType;
};

#endif
