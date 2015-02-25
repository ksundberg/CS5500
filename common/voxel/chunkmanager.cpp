#include "chunkmanager.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>

ChunkManager::ChunkManager()
{
  chunks.resize(index(CMX, CMY, CMZ));
}

BlockType ChunkManager::get(int x, int y, int z)
{
  if (0 > x || x >= CMX * Chunk::CHUNK_SIZE || 0 > y ||
      y >= CMY * Chunk::CHUNK_SIZE || 0 > z || z >= CMZ * Chunk::CHUNK_SIZE)
  {
    // Out of bounds.
    return BlockType::Inactive;
  }
  auto cmx = x / Chunk::CHUNK_SIZE;
  auto cmy = y / Chunk::CHUNK_SIZE;
  auto cmz = z / Chunk::CHUNK_SIZE;

  x %= CMX;
  y %= CMY;
  z %= CMZ;

  if(chunks[index(cmx, cmy, cmz)] == nullptr)
  {
    // Chunk hasn't been allocated yet.
    return BlockType::Inactive;
  }

  return chunks[index(cmx, cmy, cmz)]->get(x, y, z);
}

void ChunkManager::set(int x, int y, int z, BlockType type)
{
  if (0 > x || x >= CMX * Chunk::CHUNK_SIZE || 0 > y ||
      y >= CMY * Chunk::CHUNK_SIZE || 0 > z || z >= CMZ * Chunk::CHUNK_SIZE)
  {
    return;
  }
  auto cmx = x / Chunk::CHUNK_SIZE;
  auto cmy = y / Chunk::CHUNK_SIZE;
  auto cmz = z / Chunk::CHUNK_SIZE;

  x %= CMX;
  y %= CMY;
  z %= CMZ;

  // Allocate this chunk if it doesn't exist yet.
  if(chunks[index(cmx, cmy, cmz)] == nullptr)
    chunks[index(cmx,cmy,cmz)] = std::make_shared<Chunk>(x, y, z);

  auto chunk = chunks[index(cmx,cmy,cmz)];

  // Set this Chunk's specified voxel to its new type.
  chunk->set(x % CMX, y % CMY, z % CMZ, type);

  // Schedule this chunk to be updated.
  chunksToUpdate.insert(chunk);
}

int ChunkManager::index(int x, int y, int z)
{
  return x * CMY * CMZ + y * CMZ + z;
}

void ChunkManager::update()
{
  for(auto &c: chunksToUpdate)
  {
    c->update();
  }

  chunksToUpdate.clear();
}

void ChunkManager::render(TestGLContext& context)
{
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  auto program = context.shaderProgram();
  GLuint MatrixID = glGetUniformLocation(program, "mvp");
  glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

  // Camera matrix
  glm::mat4 View = glm::lookAt(
    glm::vec3(24, 20, 10), // Camera is at (4,3,3), in World Space
    glm::vec3(0, 0, 0), // and looks at the origin
    glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
  // Model matrix : an identity matrix (model will be at the origin)
  glm::mat4 Model = glm::mat4(1.0f);
  // Our ModelViewProjection : multiplication of our 3 matrices
  glm::mat4 MVP = Projection * View * Model;

  // Send our transformation to the currently bound shader, 
  // in the "MVP" uniform
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);

  // DRAW ONE CHUNK.
  chunks[index(0, 0, 0)]->render();

}
