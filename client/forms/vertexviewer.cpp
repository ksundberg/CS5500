#include "vertexviewer.h"

VertexViewer::~VertexViewer()
{
}

VertexViewer::VertexViewer(
  const std::vector<std::shared_ptr<IVContainer>>& objs)
  : _objs(objs)
{
  _vbufs.resize(_objs.size());
  _vcount.resize(_objs.size());
  int i = 0;
  for (auto& obj : _objs)
  {
    auto verts = obj->Vertices();
    glGenBuffers(1, &_vbufs[i]);
    glBindBuffer(GL_ARRAY_BUFFER, _vbufs[i]);
    glBufferData(GL_ARRAY_BUFFER,
                 verts.size() * sizeof(GLuint),
                 verts.data(),
                 GL_STATIC_DRAW);
    _vcount[i] = verts.size();
    i++;
  }
}

void VertexViewer::_do_render(GraphicsContext& context,
                              const glm::mat4& vp) const
{
  int i = 0;
  for (auto& obj : _objs)
  {
    auto position = obj->Position();
    auto model = glm::translate(glm::mat4(1.0f), position);
    auto mvp = vp * model;
    glUniformMatrix4fv(context.mvp(), 1, GL_FALSE, &mvp[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, _vbufs[i]);
    glVertexAttribPointer(context.attributeCoord(), 4, GL_BYTE, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, _vcount[i]);
    i++;
  }
}
