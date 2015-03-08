#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"
#include "vector3.h"
#include "graphics.h"

class Chunk
{
public:
  Chunk(int x, int y, int z);
  ~Chunk();

  void setAllBlocks(BlockType type);
  BlockType get(int x, int y, int z);
  void set(int x, int y, int z, BlockType type);
  glm::vec3 getPosition();
  void update();
  void render(GraphicsContext& context);

  static const int CHUNK_SIZE = 16;

  const int X; // World Chunk Position;
  const int Y; // World Chunk Position;
  const int Z; // World Chunk Position;
private:
  // The blocks data
  BlockType*** mBlocks;
  int vertex_count;
  GLuint vertex_buffer;
};

#endif
