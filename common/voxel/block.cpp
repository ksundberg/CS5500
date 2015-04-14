#include "block.h"

Block::Block(glm::vec3 p, BlockType t) : position(p), type(t)
{
  // Front verts
  // 1 2
  // 0 3

  // Back verts
  // 5 6
  // 4 7
  _verts = {
    byte4(0, 0, 0, t), // 0
    byte4(0, 1, 0, t), // 1
    byte4(1, 1, 0, t), // 2
    byte4(1, 0, 0, t), // 3

    byte4(0, 0, 1, t), // 4
    byte4(0, 1, 1, t), // 5
    byte4(1, 1, 1, t), // 6
    byte4(1, 0, 1, t), // 7
  };

  // I strongly dislike the way clang formats this
  _elems = {/*front*/ 0,
            1,
            2,
            0,
            2,
            3,
            /*back*/ 6,
            5,
            4,
            7,
            6,
            4,
            /*right*/ 3,
            2,
            6,
            3,
            6,
            7,
            /*left*/ 4,
            5,
            1,
            4,
            1,
            0,
            /*bottom*/ 4,
            0,
            3,
            4,
            3,
            7,
            /*left*/ 1,
            5,
            6,
            1,
            6,
            2};
}

Block::~Block()
{
}

const std::vector<byte4>& Block::_get_vertices() const
{
  return _verts;
}

const std::vector<GLuint>& Block::_get_elements() const
{
  return _elems;
}

const glm::vec3& Block::_get_position() const
{
  return position;
}
