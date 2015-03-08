#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

// Class dependencies
#include <vector>
#include <unordered_set>
#include <memory>
#include <tbb/concurrent_vector.h>
#include <tbb/blocked_range.h>
#include "chunk.h"
#include "vector3.h"
#include "graphics.h"

// typedefs
typedef tbb::concurrent_vector<std::shared_ptr<Chunk>> ChunkList;
typedef std::unordered_set<std::shared_ptr<Chunk>> ChunkQueue;
typedef tbb::blocked_range<ChunkList::iterator> chunkListRange;

class ChunkManager
{
private:
  int index(int x, int y, int z);
  // Chunks are a 16 x 16 x 16 containers of voxels.  The ChunkManager
  // is sort of a super Chunk, in that it contains 16 x 16 x 16 of
  // these Chunks. The reason this is done instead of using a 256 x
  // 256 x 256 container of voxels is for optimization concerns. We
  // only want to store rendering data for each Chunk, rather than
  // each voxel.
  ChunkList chunks;
  ChunkQueue chunksToUpdate;

  static const int CMX = 16; // The maximum width of the world in chunks.
  static const int CMY = 16; // The maximum depth of the world in chunks.
  static const int CMZ = 16; // The maximum height of the world in chunks.

public:
  ChunkManager();
  BlockType get(int x, int y, int z);
  void set(int x, int y, int z, BlockType type);
  void update();
  void render(GraphicsContext& context, const glm::mat4& vp);
  static const int BOUNDX = CMX * Chunk::CHUNK_SIZE;
  static const int BOUNDY = CMY * Chunk::CHUNK_SIZE;
  static const int BOUNDZ = CMZ * Chunk::CHUNK_SIZE;
};
#endif
