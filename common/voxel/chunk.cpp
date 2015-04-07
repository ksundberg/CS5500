#include "logger.h"
#include "block.h"
#include "chunk.h"

Chunk::Chunk(int x, int y, int z) : X(x), Y(y), Z(z)
{
  mBlocks = new BlockType** [CHUNK_SIZE];
  for (int i = 0; i < CHUNK_SIZE; i++)
  {
    mBlocks[i] = new BlockType* [CHUNK_SIZE];

    for (int j = 0; j < CHUNK_SIZE; j++)
    {
      mBlocks[i][j] = new BlockType[CHUNK_SIZE];
    }
  }

  // Make sure blocks are inactive on startup.
  setAllBlocks(BlockType::Inactive);
}

Chunk::~Chunk()
{
  for (int i = 0; i < CHUNK_SIZE; ++i)
  {
    for (int j = 0; j < CHUNK_SIZE; ++j)
    {
      delete[] mBlocks[i][j];
    }

    delete[] mBlocks[i];
  }
  delete[] mBlocks;
}

glm::vec3 Chunk::getPosition()
{
  return glm::vec3(X, Y, Z);
}

BlockType Chunk::get(int x, int y, int z)
{
  return mBlocks[x][y][z];
}

void Chunk::set(int x, int y, int z, BlockType type)
{
  mBlocks[x][y][z] = type;
}

void Chunk::setAllBlocks(BlockType type)
{
  for (int i = 0; i < CHUNK_SIZE; i++)
  {
    for (int j = 0; j < CHUNK_SIZE; j++)
    {
      for (int k = 0; k < CHUNK_SIZE; k++)
      {
        mBlocks[i][j][k] = type;
      }
    }
  }
}

void Chunk::update()
{
  vertices.clear();
  auto negSquareX = [&](int i, int j, int k, BlockType type)
  {
    // Create vertices for the X side of a block, making the square we
    // draw perpendicular to the X-axis. We need two triangles to
    // cover this side's square, meaning we need 6 points.
    vertices.push_back(byte4(i, j, k, type));
    vertices.push_back(byte4(i, j, k + 1, type));
    vertices.push_back(byte4(i, j + 1, k, type));
    vertices.push_back(byte4(i, j + 1, k, type));
    vertices.push_back(byte4(i, j, k + 1, type));
    vertices.push_back(byte4(i, j + 1, k + 1, type));
  };

  auto negSquareY = [&](int i, int j, int k, BlockType type)
  {
    vertices.push_back(byte4(i, j, k, type));
    vertices.push_back(byte4(i + 1, j, k, type));
    vertices.push_back(byte4(i, j, k + 1, type));
    vertices.push_back(byte4(i, j, k + 1, type));
    vertices.push_back(byte4(i + 1, j, k, type));
    vertices.push_back(byte4(i + 1, j, k + 1, type));
  };

  auto negSquareZ = [&](int i, int j, int k, BlockType type)
  {
    vertices.push_back(byte4(i, j, k, type));
    vertices.push_back(byte4(i, j + 1, k, type));
    vertices.push_back(byte4(i + 1, j, k, type));
    vertices.push_back(byte4(i + 1, j, k, type));
    vertices.push_back(byte4(i, j + 1, k, type));
    vertices.push_back(byte4(i + 1, j + 1, k, type));
  };

  auto posSquareX = [&](int i, int j, int k, BlockType type)
  {
    vertices.push_back(byte4(i, j + 1, k + 1, type));
    vertices.push_back(byte4(i, j, k + 1, type));
    vertices.push_back(byte4(i, j + 1, k, type));
    vertices.push_back(byte4(i, j + 1, k, type));
    vertices.push_back(byte4(i, j, k + 1, type));
    vertices.push_back(byte4(i, j, k, type));
  };

  auto posSquareY = [&](int i, int j, int k, BlockType type)
  {
    vertices.push_back(byte4(i + 1, j, k + 1, type));
    vertices.push_back(byte4(i + 1, j, k, type));
    vertices.push_back(byte4(i, j, k + 1, type));
    vertices.push_back(byte4(i, j, k + 1, type));
    vertices.push_back(byte4(i + 1, j, k, type));
    vertices.push_back(byte4(i, j, k, type));
  };

  auto posSquareZ = [&](int i, int j, int k, BlockType type)
  {
    vertices.push_back(byte4(i + 1, j + 1, k, type));
    vertices.push_back(byte4(i, j + 1, k, type));
    vertices.push_back(byte4(i + 1, j, k, type));
    vertices.push_back(byte4(i + 1, j, k, type));
    vertices.push_back(byte4(i, j + 1, k, type));
    vertices.push_back(byte4(i, j, k, type));
  };

  for (int i = 0; i < CHUNK_SIZE; i++)
  {
    for (int j = 0; j < CHUNK_SIZE; j++)
    {
      for (int k = 0; k < CHUNK_SIZE; k++)
      {
        auto type = mBlocks[i][j][k];

        if (type)
        {
          auto upNotCovered = (j == (CHUNK_SIZE - 1) || !(mBlocks[i][j + 1][k]));
          auto downNotCovered = (j == 0 || !(mBlocks[i][j - 1][k]));
          auto rightNotCovered = (i == (CHUNK_SIZE - 1) || !(mBlocks[i + 1][j][k]));
          auto leftNotCovered = (i == 0 || !(mBlocks[i - 1][j][k]));
          auto frontNotCovered = (k == (CHUNK_SIZE - 1) || !(mBlocks[i][j][k + 1]));
          auto backNotCovered = (k == 0 || !(mBlocks[i][j][k - 1]));

          // Create vertices for all 6 sides of our block.
          if (leftNotCovered)
          {
            negSquareX(i, j, k, type);
          }

          if (rightNotCovered)
          {
            posSquareX(i + 1, j, k, type);
          }

          if (downNotCovered)
          {
            negSquareY(i, j, k, type);
          }

          if (upNotCovered)
          {
            posSquareY(i, j + 1, k, type);
          }

          if (backNotCovered)
          {
            negSquareZ(i, j, k, type);
          }

          if (frontNotCovered)
          {
            posSquareZ(i, j, k + 1, type);
          }
        }
      }
    }
  }

  // Upload the vertices.
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(
      GL_ARRAY_BUFFER, vertices.size() * sizeof(byte4), vertices.data(), GL_STATIC_DRAW);
}

void Chunk::render(GraphicsContext& context)
{
  if (vertices.size() >= 1)
  {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(context.attributeCoord(), 4, GL_BYTE, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
  }
  else
  {
    LOG(INFO) << "No vertices to display";
  }
}
