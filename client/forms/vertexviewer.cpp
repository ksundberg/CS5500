#include "logger.h"
#include "vertexviewer.h"

#include <glm/gtc/type_ptr.hpp>

VertexViewer::~VertexViewer()
{
}

VertexViewer::VertexViewer(
  const std::vector<std::shared_ptr<IVContainer>>& objs)
  : _objs(objs)
{
  _vbufs.resize(_objs.size());
  _elembufs.resize(_objs.size());
  unsigned long i = 0;
  for (auto& obj : _objs)
  {
    auto verts = obj->Vertices();
    glGenBuffers(1, &_vbufs[i]);
    glBindBuffer(GL_ARRAY_BUFFER, _vbufs[i]);
    glBufferData(GL_ARRAY_BUFFER,
                 verts.size() * sizeof(byte4),
                 verts.data(),
                 GL_STATIC_DRAW);

    auto elems = obj->Elements();
    glGenBuffers(1, &_elembufs[i]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elembufs[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 elems.size() * sizeof(GLuint),
                 elems.data(),
                 GL_STATIC_DRAW);

    i++;
  }
}

void VertexViewer::_do_render(GraphicsContext& context,
                              const glm::mat4& vp) const
{
  for (size_t i = 0; i < _objs.size(); i++)
  {
    auto model = glm::translate(glm::mat4(1.f), _objs[i]->Position());
    auto mvp = vp * model;
    glUniformMatrix4fv(context.mvp(), 1, GL_FALSE, glm::value_ptr(mvp));

    glBindBuffer(GL_ARRAY_BUFFER, _vbufs[i]);
    glVertexAttribPointer(context.attributeCoord(), 4, GL_BYTE, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elembufs[i]);
    glDrawElements(
      GL_TRIANGLES, _objs[i]->Elements().size(), GL_UNSIGNED_INT, 0);
  }
}
