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
  void update(std::shared_ptr<Chunk> down,
              std::shared_ptr<Chunk> up,
              std::shared_ptr<Chunk> left,
              std::shared_ptr<Chunk> right,
              std::shared_ptr<Chunk> back,
              std::shared_ptr<Chunk> front);

  void render(GraphicsContext& context);

  static const int CHUNK_SIZE = 16;

  const float X; // World Chunk Position;
  const float Y; // World Chunk Position;
  const float Z; // World Chunk Position;
private:
  // The blocks data
  BlockType*** mBlocks;
  GLuint vertex_buffer;
  std::vector<byte4> vertices;
};

#endif
