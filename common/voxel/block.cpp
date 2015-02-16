#include "block.h"

Block::Block()
{
}

Block::~Block()
{
}
bool Block::IsActive()
{
  return mActive;
}

void Block::SetActive(bool active)
{
  mActive = active;
}
