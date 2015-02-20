#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"
#include "vector3.h"

class Chunk
{
public:
  Chunk(int x, int y, int z);
  ~Chunk();

  void Update();
  void setAllBlocks(BlockType type);
  BlockType get(int x, int y, int z);
  void set(int x, int y, int z, BlockType type);
  Vector3 getPosition();

  /*
  ** Assuming the use of OpenGLRenderer class from JUCE  Currently commented out
  *to prevent compile errors
  ** void Render(OpenGLRenderer* pRenderer);
  ** To be added back in next sprint for rendering compatibility
  */

  static const int CHUNK_SIZE = 16;

private:
  // The blocks data
  Block*** mBlocks;
  int X; // World Chunk Position;
  int Y; // World Chunk Position;
  int Z; // World Chunk Position;
};

#endif
