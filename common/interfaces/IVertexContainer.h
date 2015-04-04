#ifndef __I_VCONTAINER_H_
#define __I_VCONTAINER_H_

#include "graphics.h"
#include <vector>

class IVContainer
{
public:
  virtual ~IVContainer();

  // forbid copying
  IVContainer(IVContainer const&) = delete;
  IVContainer& operator=(IVContainer const&) = delete;

  const std::vector<byte4>& Vertices() const { return _get_vertices(); }
  const std::vector<GLuint>& Elements() const { return _get_elements(); }
  const glm::vec3& Position() const { return _get_position(); }

protected:
  // allow construction for only child classes
  IVContainer() {}

private:
  virtual const std::vector<byte4>& _get_vertices() const = 0;
  virtual const std::vector<GLuint>& _get_elements() const = 0;
  virtual const glm::vec3& _get_position() const = 0;
};

#endif //__I_VCONTAINER_H_
