#include "chunkmanager.h"
#include <vector>
#include <math.h>
#include "tbb/parallel_for.h"
#include "tbb/task_scheduler_init.h"

/*
The insert methods have been replaced with a blind write to memory in the future
we need to insert error checking to make sure
that the index exists and we need to double check index calculations to make
sure that chunks don't overlap each other in these
arrays does not happen doing this assumes that it is safe to overwrite an index.
*/

ChunkManager::ChunkManager()
{
  chunks.resize(index(CMX, CMY, CMZ));
  for (int i = 0; i < CMX; i++)
  {
    for (int j = 0; j < CMY; j++)
    {
      for (int k = 0; k < CMZ; k++)
      {
        chunks[index(i, j, k)] = std::make_shared<Chunk>(i, j, k);
      }
    }
  }
}

BlockType ChunkManager::get(int x, int y, int z)
{
  return chunks[index(x / Chunk::CHUNK_SIZE,
                      y / Chunk::CHUNK_SIZE,
                      z / Chunk::CHUNK_SIZE)]->get(x % CMX, y % CMY, z % CMZ);
}

void ChunkManager::set(int x, int y, int z, BlockType type)
{
  chunks[index(
           x / Chunk::CHUNK_SIZE, y / Chunk::CHUNK_SIZE, z / Chunk::CHUNK_SIZE)]
    ->set(x % CMX, y % CMY, z % CMZ, type);
}

int ChunkManager::index(int x, int y, int z)
{
  return x * CMY * CMZ + y * CMZ + z;
}
