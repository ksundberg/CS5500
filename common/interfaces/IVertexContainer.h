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

  std::vector<byte4> Vertices() const { return _get_vertices(); }
  glm::vec3 Position() const { return _get_position(); }

protected:
  // allow construction for only child classes
  IVContainer() {}

private:
  virtual std::vector<byte4> _get_vertices() const = 0;
  virtual glm::vec3 _get_position() const = 0;
};

#endif //__I_VCONTAINER_H_
