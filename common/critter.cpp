#include "critter.h"

Critter::Critter(glm::vec3 p) : pos(p)
{
  _verts = {byte4(0, 0, 0, 3),
            byte4(0, 10, 0, 3),
            byte4(10, 10, 0, 3),
            byte4(10, 0, 0, 3)};

  _elems = {0, 1, 2, 0, 2, 3};
}

Critter::~Critter()
{
}

const std::vector<byte4>& Critter::_get_vertices() const
{
  return _verts;
}

const std::vector<GLuint>& Critter::_get_elements() const
{
  return _elems;
}

const glm::vec3& Critter::_get_position() const
{
  return pos;
}
