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
  if (x < 0 || dungeonBlockLength() <= x || y < 0 || dungeonBlockLength() <= y || z < 0 ||
      dungeonBlockLength() <= z)
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
  auto pos1 = createRoom(list[index(DUNGEON_SIZE / 2, DUNGEON_SIZE / 2, DUNGEON_SIZE - 1)]);
  auto pos2 = createRoom(list[index(0, 0, DUNGEON_SIZE - 1)]);
  connectRoom(list, pos1, pos2);
}

void Dungeon::connectRoom(ChunkList& list, Point3D pos1, Point3D pos2)
{
  std::cout << list.size() << std::endl;
  std::cout << "Point 1: " << " X: " << std::get<0>(pos1) << " Y: " << std::get<1>(pos1) << " Z: " <<  std::get<2>(pos1) << std::endl;
  std::cout << "Point 2: " << " X: " << std::get<0>(pos2) << " Y: " << std::get<1>(pos2) << " Z: " <<  std::get<2>(pos2) << std::endl;
}

Point3D Dungeon::createRoom(Chunk* chunk)
{
  // Rooms are just empty chunks for now.
  chunk->deactivateAllBlocks();
  auto pos = chunk->getPosition();
  return std::make_tuple(
    static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(pos.z));
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
    std::cout << "-----" << k << "f-----------------------------------------" << std::endl;
    for (int i = 0; i < DUNGEON_SIZE; i++)
    {
      for (int j = 0; j < DUNGEON_SIZE; j++)
      {
        if (isChunkAllActive(list, i, j, k))
        {
          std::cout << " . ";
        }
        else
        {
          std::cout << " R ";
        }
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

bool Dungeon::isChunkAllActive(const ChunkList &list, int x, int y, int z)
{
  auto chunk = list[index(x, y, z)];
  for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
  {
    for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
    {
      for (int k = 0; k < Chunk::CHUNK_SIZE; k++)
      {
        if(!(chunk->isBlockActive(i, j, k)))
          return false;
      }
    }
  }
  return true;
}
