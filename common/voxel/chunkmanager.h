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
  Vector3* pCameraPosition; // the previous camera position
  Vector3* pCameraRotation; // the previous camera rotation
  bool forceVisibilityUpdate = false;
  void insert(ChunkList, int index, Chunk* to_insert);
  // The following 4 constants will later be stored in a configuration file per
  // world and set on world load.
  // final removed
  const int NUM_CHUNKS_PER_FRAME = 20; // The maximum number of chunks to be
                                       // processed per frame(This must be an
                                       // even number for processing purposes)
  const int MAX_VIEW_DISTANCE = 4;
  const int MAX_CHUNKS_INDEX_X =
    100; // The maximum width of the world in chunks(1600 blocks)(index is for
         // use in chunk vector list calculations)(index goes from 0 to 99)
  const int MAX_CHUNKS_INDEX_Y =
    100; // The maximum depth of the world in chunks(1600 blocks)
  const int MAX_CHUNKS_INDEX_Z =
    16; // The maximum height of the world in chunks(256 blocks )

public:
  ChunkList chunkProcessingList; // A list for processing in the parallel for
                                 // loop in the update function
  ChunkList
    chunkRenderList; // A vector list of loaded Chunks that should be rendered
  ChunkList chunkRebuildList; // A vector list of chunks that require rebuilding
  ChunkList chunkUnloadList; // A vector list of Chunks that need to be unloaded
                             // from memory
  ChunkList
    nchunkVisibilityList; // A vector list of Chunks that could be rendered
  ChunkList pChunkVisibilityList; // A list for comparing to the new processing
                                  // list to determine which chunks should be
                                  // unloaded;
  ChunkList chunkMeshGenList; // A vector list of chunks that should have their
                              // meshes generated either because they have just
                              // been loaded or because they have been modified;

  ChunkManager(); // A constructor stub, in future it will accept a game
                  // context(specifically a game seed and save file)

  void Update(float deltaTime,
              Vector3 cameraPosition,
              Vector3 cameraRotation); // An game update function for the
                                       // rendering engine, it accepts the
                                       // change in time since the last frame, a
                                       // camera position, and a camera view
                                       // angle as a Vector3 of floats

  int translatePositionToIndex(Vector3 chunkPosition);
  Vector3* translateIndexToPosition(int chunkIndex);
  Vector3 translateCameraPositionToChunk(Vector3 cameraPosition);
};

#endif
