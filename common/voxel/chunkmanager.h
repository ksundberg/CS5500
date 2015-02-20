#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

// Class dependencies
#include <vector>
#include <memory>
#include "chunk.h"
#include "vector3.h"
#include "tbb/concurrent_vector.h"
#include "tbb/blocked_range.h"

// typedefs
typedef tbb::concurrent_vector<std::shared_ptr<Chunk>> ChunkList;
typedef tbb::blocked_range<ChunkList::iterator> chunkListRange;

class ChunkManager
{
private:
  int index(int x, int y, int z);
  ChunkList chunks;
  const int CMX =
    16; // The maximum width of the world in chunks(1600 blocks)(index is for
        // use in chunk vector list calculations)(index goes from 0 to 99)
  const int CMY = 16; // The maximum depth of the world in chunks(1600 blocks)
  const int CMZ = 16; // The maximum height of the world in chunks(256 blocks )

public:
  ChunkManager();
  BlockType get(int x, int y, int z);
  void set(int x, int y, int z, BlockType type);
};
#endif
