#ifndef __WORLD_H_
#define __WORLD_H_

#include "critter.h"
#include "block.h"

#include <memory>
#include <vector>

class World
{
public:
  static std::shared_ptr<World> Generate(int, int, int);

  std::vector<std::shared_ptr<IVContainer>> Containers() const;

  std::vector<std::shared_ptr<Block>> blocks;

  void Update();

private:
  // TODO: add renderable that does gl instancing instead of using the
  // vertexviewer
  static std::shared_ptr<Block> _critterBlock;
  std::vector<std::shared_ptr<Critter>> critters;
  int _size;
  int _height;
  std::shared_ptr<std::vector<std::vector<double>>> _noise;
};
#endif //__WORLD_H_
