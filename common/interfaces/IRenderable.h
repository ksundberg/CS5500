#ifndef __I_RENDERABLE_H_
#define __I_RENDERABLE_H_

#include "graphics.h"

class IRenderable
{
public:
  virtual ~IRenderable();

  // forbid copying
  IRenderable(IRenderable const&) = delete;
  IRenderable& operator=(IRenderable const&) = delete;

  void Render(GraphicsContext& context, const glm::mat4& vp) const
  {
    return _do_render(context, vp);
  }

protected:
  // allow construction for only child classes
  IRenderable() {}

private:
  virtual void _do_render(GraphicsContext& context,
                          const glm::mat4& vp) const = 0;
};

#endif //__I_RENDERABLE_H_
