#ifndef __WORLD_H_
#define __WORLD_H_

#include "critter.h"
#include "block.h"

#include <memory>
#include <vector>

class World
{
public:
  static std::shared_ptr<World> Generate(int, int);

  std::vector<Block> blocks;
  std::vector<Critter> critters;
};
#endif //__WORLD_H_
