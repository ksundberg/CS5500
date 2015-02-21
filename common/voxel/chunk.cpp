#include "block.h"
#include "chunk.h"

Chunk::Chunk(int x, int y, int z)
{
  X = x;
  Y = y;
  Z = z;
  // Block array creation
  mBlocks = new Block** [CHUNK_SIZE];
  for (int i = 0; i < CHUNK_SIZE; i++)
  {
    mBlocks[i] = new Block* [CHUNK_SIZE];

    for (int j = 0; j < CHUNK_SIZE; j++)
    {
      mBlocks[i][j] = new Block[CHUNK_SIZE];
    }
  }
}

Chunk::~Chunk()
{
  // Block array deletion
  for (int i = 0; i < CHUNK_SIZE; ++i)
  {
    for (int j = 0; j < CHUNK_SIZE; ++j)
    {
      delete[] mBlocks[i][j];
    }

    delete[] mBlocks[i];
  }
  delete[] mBlocks;
}

Vector3 Chunk::getPosition()
{
  return Vector3(X, Y, Z);
}

BlockType Chunk::get(int x, int y, int z)
{
  return mBlocks[x][y][z].get();
}

void Chunk::set(int x, int y, int z, BlockType type)
{
  mBlocks[x][y][z].set(type);
}

void Chunk::setAllBlocks(BlockType type)
{
  for (int i = 0; i < CHUNK_SIZE; i++)
  {
    for (int j = 0; j < CHUNK_SIZE; j++)
    {
      for (int k = 0; k < CHUNK_SIZE; k++)
      {
        mBlocks[i][j][k].set(type);
      }
    }
  }
}

void Chunk::update()
{
  // TODO: fill up this Chunk's vertex buffer object with new data.
}

void Chunk::render()
{
  // TODO: render this Chunk's vertex buffer object.
}
