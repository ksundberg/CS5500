#ifndef BLOCK_H
#define BLOCK_H

#include "graphics.h"
#include "IVertexContainer.h"

#include <vector>

enum BlockType
{
  Inactive = 0,
  Ground,
  Water,
  Sand,
  Wood,
  Flowers,
  Ruby,
  Leaves,
  Stone,
  Grass,
  Brick,
  Party,
  Coal,
  Iron,
  Gravel,
  Diamond,
  Gold
};

class Block : public IVContainer
{
public:
  Block() = delete;
  Block(glm::vec3 p, BlockType t);
  virtual ~Block();

  // forbid copying
  Block(Block const&) = delete;
  Block& operator=(Block const&) = delete;

  glm::vec3 position;
  BlockType type;

private:
  const std::vector<byte4>& _get_vertices() const override;
  const std::vector<GLuint>& _get_elements() const override;
  const glm::vec3& _get_position() const override;

  std::vector<byte4> _verts;
  std::vector<GLuint> _elems;
};

#endif
