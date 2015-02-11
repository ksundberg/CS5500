#ifndef DUNGEON_HEADER
#define DUNGEON_HEADER

#endif

/*
  1. Create a 2D array of block objects.
  2. Randomly select rooms, store locations in a list.
  3. Iterate through locations, expanding to different sizes,
     but only if a location is sufficiently far enough away
     from another location. Delete locations that are too close
     to a previously successful room.
  4. Create a minimum spanning tree to connect leftover rooms.
  5. Connect rooms to each other based on tree.
  TODO: figure out how to add chests and enemies.
  
 */
