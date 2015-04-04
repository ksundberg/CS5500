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
  const std::vector<byte4>& _get_vertices() const override;
  const std::vector<GLuint>& _get_elements() const override;
  const glm::vec3& _get_position() const override;

  std::vector<byte4> _verts;
  std::vector<GLuint> _elems;
};
#endif //__CRITTER_H_
