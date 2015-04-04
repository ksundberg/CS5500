#ifndef __CRITTER_H_
#define __CRITTER_H_

#include "IVertexContainer.h"
#include <glm/glm.hpp>

class Critter : public IVContainer
{
public:
  Critter(glm::vec3 pos);
  virtual ~Critter();

  glm::vec3 pos;

private:
  std::vector<byte4> _get_vertices() const override;
  glm::vec3 _get_position() const override;
};
#endif //__CRITTER_H_
