#include "chunkmanager.h"
#include <vector>
#include <math.h>
#include "tbb/parallel_for.h"
#include "tbb/task_scheduler_init.h"

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
  if (0 > x || x >= CMX * Chunk::CHUNK_SIZE || 0 > y ||
      y >= CMY * Chunk::CHUNK_SIZE || 0 > z || z >= CMZ * Chunk::CHUNK_SIZE)
  {
    return BlockType::Inactive;
  }
  else
  {
    return chunks[index(x / Chunk::CHUNK_SIZE,
                        y / Chunk::CHUNK_SIZE,
                        z / Chunk::CHUNK_SIZE)]->get(x % CMX, y % CMY, z % CMZ);
  }
}

void ChunkManager::set(int x, int y, int z, BlockType type)
{
  if (0 > x || x >= CMX * Chunk::CHUNK_SIZE || 0 > y ||
      y >= CMY * Chunk::CHUNK_SIZE || 0 > z || z >= CMZ * Chunk::CHUNK_SIZE)
  {
    return;
  }
  auto chunk = chunks[index(
    x / Chunk::CHUNK_SIZE, y / Chunk::CHUNK_SIZE, z / Chunk::CHUNK_SIZE)];

  // Set this Chunk's specified voxel to its new type.
  chunk->set(x % CMX, y % CMY, z % CMZ, type);

  // Schedule this chunk to be updated.
  chunksToUpdate.insert(chunk);
}

int ChunkManager::index(int x, int y, int z)
{
  return x * CMY * CMZ + y * CMZ + z;
}

void ChunkManager::update()
{
  for(auto &c: chunksToUpdate)
  {
    c->update();
  }

  chunksToUpdate.clear();
}

void ChunkManager::render(TestGLContext& context)
{
  context.DrawRotatedCube(30.0, 30.0, 0.2f, 0.1f, 0.3f);
}
