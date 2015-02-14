#include <cmath>
#include "dungeon.h"
#include "logger.h"

void Dungeon::makeDungeon(ChunkList& list)
{
  list.resize(DUNGEON_SIZE * DUNGEON_SIZE * DUNGEON_SIZE);
  for (int i = 0; i < DUNGEON_SIZE; i++)
  {
    for (int j = 0; j < DUNGEON_SIZE; j++)
    {
      for (int k = 0; k < DUNGEON_SIZE; k++)
      {
        list[index(i, j, k)] = new Chunk(i, j, k);
      }
    }
  }
  makeChunksActive(list);
  createRooms(list);
}

void Dungeon::makeChunksActive(ChunkList& chunkList)
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

bool Dungeon::isBlockActive(const ChunkList& list, int x, int y, int z)
{
  if (x < 0 || dungeonBlockLength() <= x || y < 0 ||
      dungeonBlockLength() <= y || z < 0 || dungeonBlockLength() <= z)
  {
    return false;
  }

  auto chunk =
    list[index(x / DUNGEON_SIZE, y / DUNGEON_SIZE, z / DUNGEON_SIZE)];

  return chunk->isBlockActive(
    x % DUNGEON_SIZE, y % DUNGEON_SIZE, z % DUNGEON_SIZE);
}


void Dungeon::createRooms(ChunkList& list)
{

  // Entrance is at the top of our dungeon cube.
  auto chunk1 =
    list[index(DUNGEON_SIZE / 2, DUNGEON_SIZE / 2, DUNGEON_SIZE - 1)];
  auto chunk2 = list[index(0, 0, DUNGEON_SIZE - 1)];
  createRoom(chunk1);
  createRoom(chunk2);
  connectRoom(list, chunk1, chunk2);
}

void Dungeon::connectRoom(ChunkList& list, Chunk* chunk1, Chunk* chunk2)
{
  auto pos1 = chunkToBlockDistance(chunk1->getPosition());
  auto pos2 = chunkToBlockDistance(chunk2->getPosition());

  auto dist = distanceBetween(pos1, pos2);
  
  std::cout << list.size() << std::endl;
  std::cout << "Point 1: "
            << " X: " << pos1.x << " Y: " << pos1.y << " Z: " << pos1.z
            << std::endl;
  std::cout << "Point 2: "
            << " X: " << pos2.x << " Y: " << pos2.y << " Z: " << pos2.z
            << std::endl;
  std::cout << "Block distance between: " << distanceBetween(pos1, pos2)
            << std::endl;

  
  std::cout << dist << std::endl;
  // Test making an entire row of rooms.

  auto incX = (pos1.x - pos2.x) / dist;
  auto incY = (pos1.y - pos2.y) / dist;
  auto incZ = (pos1.z - pos2.z) / dist;

  std::cout << incX << std::endl;

  auto i = pos1.x, j = pos1.y, k = pos1.z;
  while (i < pos2.x || j < pos2.y || k < pos2.z)
  {
    i += incX;
    j += incY;
    k += incZ;
    list[index(static_cast<int>(i) / DUNGEON_SIZE,
               static_cast<int>(j) / DUNGEON_SIZE,
               static_cast<int>(k) / DUNGEON_SIZE)]
      ->deactivateBlock(static_cast<int>(i) % DUNGEON_SIZE,
                        static_cast<int>(j) % DUNGEON_SIZE,
                        static_cast<int>(k) % DUNGEON_SIZE);
  }
  for (int i = 0; i < DUNGEON_SIZE; i++)
  {
    list[index(i, 0, DUNGEON_SIZE - 1)]->deactivateBlock(0, 0, 0);
  }
}

void Dungeon::createRoom(Chunk* chunk)
{
  // Rooms are just empty chunks for now.
  chunk->deactivateAllBlocks();
}

int Dungeon::dungeonBlockLength()
{
  return DUNGEON_SIZE * Chunk::CHUNK_SIZE;
}

void Dungeon::printDungeon(ChunkList& list)
{
  list.resize(DUNGEON_SIZE * DUNGEON_SIZE * DUNGEON_SIZE);
  for (int k = DUNGEON_SIZE - 1; k >= 0; k--)
  {
    std::cout << "-----" << k << "f-----------------------------------------"
              << std::endl;
    for (int j = DUNGEON_SIZE - 1; j >= 0; j--)
    {
      for (int i = 0; i < DUNGEON_SIZE; i++)
      {
        if (isChunkAllActive(list[index(i, j, k)]))
        {
          // Solid active chunk.
          std::cout << " . ";
        }
        else if (isChunkAnyActive(list[index(i, j, k)]))
        {
          // Path.
          std::cout << " o ";
        }
        else
        {
          // Room.
          std::cout << " R ";
        }
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

bool Dungeon::isChunkAllActive(Chunk* chunk)
{
  for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
  {
    for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
    {
      for (int k = 0; k < Chunk::CHUNK_SIZE; k++)
      {
        if (!(chunk->isBlockActive(i, j, k))) return false;
      }
    }
  }
  return true;
}

bool Dungeon::isChunkAnyActive(Chunk* chunk)
{
  for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
  {
    for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
    {
      for (int k = 0; k < Chunk::CHUNK_SIZE; k++)
      {
        if (chunk->isBlockActive(i, j, k)) return true;
      }
    }
  }
  return false;
}

float Dungeon::distanceBetween(Vector3 pos1, Vector3 pos2)
{
  return sqrt(pow(fabs(pos1.x - pos2.x), 2.0) +
              pow(fabs(pos1.y - pos2.y), 2.0) +
              pow(fabs(pos1.z - pos2.z), 2.0));
}

Vector3 Dungeon::chunkToBlockDistance(Vector3 incoming)
{
  Vector3 forYou;

  forYou.x = incoming.x * Chunk::CHUNK_SIZE;
  forYou.y = incoming.y * Chunk::CHUNK_SIZE;
  forYou.z = incoming.z * Chunk::CHUNK_SIZE;

  return forYou;
}
