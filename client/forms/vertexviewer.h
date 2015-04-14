#ifndef __I_VERTEXVIEWER_H_
#define __I_VERTEXVIEWER_H_

#include "IRenderable.h"
#include "IVertexContainer.h"
#include "graphics.h"

#include <vector>
#include <memory>

class VertexViewer : public IRenderable
{
public:
  VertexViewer() = delete;
  VertexViewer(const std::vector<std::shared_ptr<IVContainer>>& objs);
  virtual ~VertexViewer();

  // forbid copying
  VertexViewer(VertexViewer const&) = delete;
  VertexViewer& operator=(VertexViewer const&) = delete;

private:
  void _do_render(GraphicsContext& context, const glm::mat4& vp) const override;

  std::vector<std::shared_ptr<IVContainer>> _objs;
  std::vector<GLuint> _vbufs;
  std::vector<GLuint> _elembufs;
};

#endif //__I_VERTEXVIEWER_H_
