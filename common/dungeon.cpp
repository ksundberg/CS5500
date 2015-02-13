#include "dungeon.h"
#include "logger.h"

Dungeon::Dungeon()
{
  chunks.resize(DUNGEON_SIZE * DUNGEON_SIZE * DUNGEON_SIZE);
  for (int i = 0; i < DUNGEON_SIZE; i++)
  {
    for (int j = 0; j < DUNGEON_SIZE; j++)
    {
      for (int k = 0; k < DUNGEON_SIZE; k++)
      {
        chunks[index(i, j, k)] = new Chunk(i, j, k);
      }
    }
  }
  makeChunksActive(chunks);
  createRooms(chunks);
}

Dungeon::~Dungeon()
{
  chunks.clear();
}

void Dungeon::makeChunksActive(std::vector<Chunk*> &chunkList)
{
  for (auto& c : chunkList)
  {
    c->activateAllBlocks();
  }
}

int Dungeon::index(int x, int y, int z)
{
  return x * DUNGEON_SIZE * DUNGEON_SIZE + y * DUNGEON_SIZE + z;
}

bool Dungeon::isBlockActive(int x, int y, int z)
{
  if (x < 0 || blockCount() <= x || y < 0 || blockCount() <= y || z < 0 ||
      blockCount() <= z)
  {
    return false;
  }
  auto chunk_x = x / DUNGEON_SIZE, chunk_y = y / DUNGEON_SIZE,
       chunk_z = y / DUNGEON_SIZE;

  auto chunk = chunks[index(chunk_x, chunk_y, chunk_z)];

  auto block_x = x - chunk_x * DUNGEON_SIZE,
       block_y = y - chunk_y * DUNGEON_SIZE,
       block_z = z - chunk_z * DUNGEON_SIZE;

  return chunk->isBlockActive(block_x, block_y, block_z);
}

void Dungeon::createRooms(std::vector<Chunk*> &chunkList)
{

  // Entrance is at the top of our dungeon cube.
  createRoom(
    chunkList[index(DUNGEON_SIZE / 2, DUNGEON_SIZE / 2, DUNGEON_SIZE - 1)]);
}

void Dungeon::createRoom(Chunk* chunk)
{
  // Rooms are just empty chunks for now.
  chunk->deactivateAllBlocks();
}

int Dungeon::blockCount()
{
  return DUNGEON_SIZE * Chunk::CHUNK_SIZE;
}
