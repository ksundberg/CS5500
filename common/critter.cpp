#include "logger.h"
#include "critter.h"

Critter::Critter(glm::vec3 p, std::shared_ptr<IVContainer> c)
  : dir({1, 1}), _pos(p), _container(c)
{
  LOG(INFO) << "Critter at" << _pos.x << " " << _pos.y;
}

Critter::~Critter()
{
}

const std::vector<byte4>& Critter::_get_vertices() const
{
  return _container->Vertices();
}

const std::vector<GLuint>& Critter::_get_elements() const
{
  return _container->Elements();
}

const glm::vec3& Critter::_get_position() const
{
  return _pos;
}

void Critter::move(glm::vec3 v)
{
  _pos.x += dir.x * v.x;
  _pos.z += dir.y * v.z;
  _pos.y = v.y;
}

void Critter::turn(glm::vec2 dir)
{
  this->dir = dir;
}
