#ifndef BLOCK_H
#define BLOCK_H

#include "vector3.h"

enum BlockType
{
  BlockTypeDefault
};

class Block
{
public:
  Block();
  ~Block();

  bool IsActive();
  void SetActive(bool active);

  double mass;          // in kg
  Vector3 acceleration; // in m/s^2
  Vector3 velocity;     // in m/s

private:
  bool mActive;

  //		BlockType mBlockType;
};

#endif