#include "critter.h"

Critter::Critter(glm::vec3 p) : pos(p)
{
}

Critter::~Critter()
{
}

std::vector<byte4> Critter::_get_vertices() const
{
  return {byte4(0, 0, 0, 3),
          byte4(0, 10, 0, 3),
          byte4(10, 10, 0, 3),
          byte4(0, 0, 0, 3),
          byte4(10, 10, 0, 3),
          byte4(10, 0, 0, 3)};
}

glm::vec3 Critter::_get_position() const
{
  return pos;
}
