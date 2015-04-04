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

  std::vector<std::shared_ptr<IVContainer>> Containers() const;

  std::vector<Block> blocks;

  void Update();

private:
  std::vector<std::shared_ptr<Critter>> critters;
};
#endif //__WORLD_H_
