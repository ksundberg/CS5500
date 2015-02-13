#ifndef DUNGEON_HEADER
#define DUNGEON_HEADER
#include <vector>
#include "chunk.h"

#endif

/*
  1. Create a 3D array of Chunk objects.
  2. Randomly select rooms, store locations in a list.
  3. Iterate through locations, expanding to different sizes,
     but only if a location is sufficiently far enough away
     from another location. Delete locations that are too close
     to a previously successful room.
  4. Create a minimum spanning tree to connect leftover rooms.
  5. Connect rooms to each other based on tree.
  TODO: figure out how to add chests and enemies.
  
 */

class Dungeon {
 private: 
  int index(int x, int y, int z);
  void makeChunksActive(std::vector<Chunk*> &chunkList);
  std::vector<Chunk*> chunks;
 public:
  Dungeon();
  ~Dungeon();
  // Index 256 x 256 x 256 dungeon for active blocks.
  bool isActive(int x, int y, int z);
  static const int DUNGEON_SIZE = 16;
};
