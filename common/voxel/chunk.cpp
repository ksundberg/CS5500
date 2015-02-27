#include <iostream>
#include "block.h"
#include "chunk.h"

Chunk::Chunk(int x, int y, int z) : X(x), Y(y), Z(z)
{
  // Block array creation
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
  // Block array deletion
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

Vector3 Chunk::getPosition()
{
  return Vector3(X, Y, Z);
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
  // Max number of vertices a block could have is 36.
  byte4 vertex[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 36];
  int vindex = 0;

  auto squareX = [&](int i, int j, int k, BlockType type)
  {
    // Create vertices for the X side of a block, making the square we
    // draw perpendicular to the X-axis. We need two triangles to
    // cover this side's square, meaning we need 6 points.
    vertex[vindex++] = byte4(i, j, k, type);
    vertex[vindex++] = byte4(i, j, k + 1, type);
    vertex[vindex++] = byte4(i, j + 1, k, type);
    vertex[vindex++] = byte4(i, j + 1, k, type);
    vertex[vindex++] = byte4(i, j, k + 1, type);
    vertex[vindex++] = byte4(i, j + 1, k + 1, type);
  };

  auto squareY = [&](int i, int j, int k, BlockType type)
  {
    // Vertices for a square perpendicular to the Y-axis.
    vertex[vindex++] = byte4(i, j, k, type);
    vertex[vindex++] = byte4(i + 1, j, k, type);
    vertex[vindex++] = byte4(i, j, k + 1, type);
    vertex[vindex++] = byte4(i, j, k + 1, type);
    vertex[vindex++] = byte4(i + 1, j, k, type);
    vertex[vindex++] = byte4(i + 1, j, k + 1, type);
  };

  auto squareZ = [&](int i, int j, int k, BlockType type)
  {
    // Vertices for a square perpendicular to the Z-axis.
    vertex[vindex++] = byte4(i, j, k, type);
    vertex[vindex++] = byte4(i, j + 1, k, type);
    vertex[vindex++] = byte4(i + 1, j, k, type);
    vertex[vindex++] = byte4(i + 1, j, k, type);
    vertex[vindex++] = byte4(i, j + 1, k, type);
    vertex[vindex++] = byte4(i + 1, j + 1, k, type);
  };

  for (int i = 0; i < CHUNK_SIZE; i++)
  {
    for (int j = 0; j < CHUNK_SIZE; j++)
    {
      for (int k = 0; k < CHUNK_SIZE; k++)
      {
        auto type = mBlocks[i][j][k];

        // BlockType::Inactive is 0; this tests if our block is non-empty.
        if (type)
        {
          // Create vertices for all 6 sides of our block.

          if (0 == i || !(mBlocks[i - 1][j][k]))
          {
            // Square in the negative x direction.
            squareX(i, j, k, type);
          }

          if ((CHUNK_SIZE - 1) == i || !(mBlocks[i + 1][j][k]))
          {
            // Now for the positive x.
            squareX(i + 1, j, k, type);
          }

          if (0 == j || !(mBlocks[i][j - 1][k]))
          {
            // Negative y direction.
            squareY(i, j, k, type);
          }

          if ((CHUNK_SIZE - 1) == j || !(mBlocks[i][j + 1][k]))
          {
            // Positive y direction
            squareY(i, j + 1, k, type);
          }

          if (0 == k || !(mBlocks[i][j][k - 1]))
          {
            // Negative z direction.
            squareZ(i, j, k, type);
          }

          if ((CHUNK_SIZE - 1) == k || !(mBlocks[i][j][k + 1]))
          {
            // Positive z direction.
            squareZ(i, j, k + 1, type);
          }
        }
      }
    }
  }
  vertex_count = vindex;

  // Upload the vertices.
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(
    GL_ARRAY_BUFFER, vertex_count * sizeof *vertex, vertex, GL_STATIC_DRAW);
}

void Chunk::render()
{
  GLint attribute_coord = 0;
  if (vertex_count >= 1)
  {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(attribute_coord, 4, GL_BYTE, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
  }
}
