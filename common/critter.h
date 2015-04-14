#ifndef __CRITTER_H_
#define __CRITTER_H_

#include "block.h"
#include "IVertexContainer.h"

#include <glm/glm.hpp>
#include <memory>

class Critter : public IVContainer
{
public:
  Critter(glm::vec3 pos, std::shared_ptr<IVContainer> container);
  virtual ~Critter();

  // Move the critter by the input vector
  void move(glm::vec3);
  void turn(glm::vec2 dir);

  glm::vec2 dir;

private:
  const std::vector<byte4>& _get_vertices() const override;
  const std::vector<GLuint>& _get_elements() const override;
  const glm::vec3& _get_position() const override;

  glm::vec3 _pos;
  std::shared_ptr<IVContainer> _container;
};
#endif //__CRITTER_H_
