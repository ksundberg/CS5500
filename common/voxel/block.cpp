#include "block.h"

Block::Block()
{
}

Block::~Block()
{
}
BlockType Block::get()
{
  return type;
}

void Block::set(BlockType type_)
{
  type = type_;
}
