#include "block.h"
#include "chunk.h"

Chunk::Chunk(int x, int y, int z)
{
  X = x;
  Y = y;
  Z = z;
  // Block array creation
  mBlocks = new Block** [CHUNK_SIZE];
  for (int i = 0; i < CHUNK_SIZE; i++)
  {
    mBlocks[i] = new Block* [CHUNK_SIZE];

    for (int j = 0; j < CHUNK_SIZE; j++)
    {
      mBlocks[i][j] = new Block[CHUNK_SIZE];
    }
  }
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

bool Chunk::IsLoaded()
{
  return loaded;
}

void Chunk::load()
{
  // A stub for chunk loading code
  loaded = true; // Assumes successful load to advance program test
}

bool Chunk::IsSetup()
{
  return setupd;
}

void Chunk::setup()
{
  // A stub for chunk loading code
  setupd = true; // Assumes successful setup to advance program test
}

bool Chunk::getRebuild()
{
  return rebuild;
}

void Chunk::setRebuild()
{
  rebuild = true;
}

int Chunk::getIndex()
{
  return index;
}

void Chunk::setIndex(int ind)
{
  index = ind;
}

Vector3 Chunk::getPosition()
{
  return Vector3(X, Y, Z);
}

void Chunk::Update(float /*dt*/)
{
  // A function stub for Chunk update code to be called from the Chunk Manager
}

/*
**	See header file for comments regarding this function
**	void Chunk::Render(OpenGLRenderer* pRenderer)
**	{
**		//A function stub for the render call from the Chunk Manager
**	}
*/

void Chunk::activateBlock(int x, int y, int z)
{
  mBlocks[x][y][z].SetActive(true);
}
void Chunk::deactivateBlock(int x, int y, int z)
{
  mBlocks[x][y][z].SetActive(false);
}
bool Chunk::isBlockActive(int x, int y, int z)
{
  return mBlocks[x][y][z].IsActive();
}

void Chunk::activateAllBlocks()
{
  for (int i = 0; i < CHUNK_SIZE; i++)
  {
    for (int j = 0; j < CHUNK_SIZE; j++)
    {
      for (int k = 0; k < CHUNK_SIZE; k++)
      {
        mBlocks[i][j][k].SetActive(true);
      }
    }
  }
}

void Chunk::deactivateAllBlocks()
{
  for (int i = 0; i < CHUNK_SIZE; i++)
  {
    for (int j = 0; j < CHUNK_SIZE; j++)
    {
      for (int k = 0; k < CHUNK_SIZE; k++)
      {
        mBlocks[i][j][k].SetActive(false);
      }
    }
  }
}
