#include <cmath>
#include <time.h>
#include "logger.h"
#include "dungeon.h"
#include <memory>

void Dungeon::makeDungeon(ChunkList& list)
{
  list.resize(DUNGEON_SIZE * DUNGEON_SIZE * DUNGEON_SIZE);
  for (int i = 0; i < DUNGEON_SIZE; i++)
  {
    for (int j = 0; j < DUNGEON_SIZE; j++)
    {
      for (int k = 0; k < DUNGEON_SIZE; k++)
      {
        list[index(i, j, k)] = std::make_shared<Chunk>(
          i * Chunk::CHUNK_SIZE, j * Chunk::CHUNK_SIZE, k * Chunk::CHUNK_SIZE);
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
    c->setAllBlocks(BlockType::Ground);
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

  auto chunk = list[index(
    x / Chunk::CHUNK_SIZE, y / Chunk::CHUNK_SIZE, z / Chunk::CHUNK_SIZE)];

  return chunk->get(x % DUNGEON_SIZE, y % DUNGEON_SIZE, z % DUNGEON_SIZE);
}

void Dungeon::createRooms(ChunkList& list)
{
  // Entrance is at the top of our dungeon cube.

  std::vector<std::shared_ptr<Chunk>> roomList;
  struct roomPair
  {
    std::shared_ptr<Chunk> chunka;
    std::shared_ptr<Chunk> chunkb;
  };
  std::vector<roomPair> connectList;
  roomPair pair;
  std::shared_ptr<Chunk> closestChunk;
  // float closestDist;
  std::shared_ptr<Chunk> currentChunk;
  srand(time(NULL));
  int j;
  unsigned int i;
  int roomcount;
  int x, y, z; // location
  // make entrance
  x = DUNGEON_SIZE / 2;
  y = DUNGEON_SIZE / 2;
  z = DUNGEON_SIZE - 1;
  auto chunkrand = list[index(x, y, z)];
  createRoom(chunkrand);
  roomList.push_back(chunkrand);
  roomcount = DUNGEON_SIZE * DUNGEON_SIZE * DUNGEON_SIZE * .05;

  // Create random rooms
  for (j = DUNGEON_SIZE - 1; j >= 0; j--)
  {

    z = j; // floor j

    for (i = 0; i < (unsigned int)(roomcount / DUNGEON_SIZE); i++)
    {
      y = rand() % DUNGEON_SIZE;
      x = rand() % DUNGEON_SIZE;
      chunkrand = list[index(x, y, z)];
      roomList.push_back(chunkrand);
      createRoom(chunkrand);
      if (roomList.size() > 1)
      {
        closestChunk = roomList[roomList.size() - 1];
        currentChunk = roomList[roomList.size() - 2];
        pair.chunka = closestChunk;
        pair.chunkb = currentChunk;
        connectList.push_back(pair);
      }
    }

    // Till vector is empty, connect all rooms on this floor
    for (i = 0; i < connectList.size(); i++)
    {
      connectRoom(list, connectList[i].chunka, connectList[i].chunkb);
    }
    connectList.clear();
  }
}

void Dungeon::connectRoom(ChunkList& list,
                          std::shared_ptr<Chunk> chunk1,
                          std::shared_ptr<Chunk> chunk2)
{
  auto pos1 = chunk1->getPosition();
  auto pos2 = chunk2->getPosition();

  auto unit = glm::normalize(pos2 - pos1);

  auto start = pos1;

  auto in_dungeon = [](glm::vec3 v)
  {
    return (0 < v.x && v.x < DUNGEON_SIZE * Chunk::CHUNK_SIZE - 1 && 0 < v.y &&
            v.y < DUNGEON_SIZE * Chunk::CHUNK_SIZE - 1 && 0 < v.x &&
            v.x < DUNGEON_SIZE * Chunk::CHUNK_SIZE - 1);
  };

  while (glm::distance(start, pos2) > 1.0 && in_dungeon(start))
  {
    start += unit;
    list[index((static_cast<int>(start.x)) / Chunk::CHUNK_SIZE,
               (static_cast<int>(start.y)) / Chunk::CHUNK_SIZE,
               (static_cast<int>(start.z)) / Chunk::CHUNK_SIZE)]
      ->set((static_cast<int>(start.x)) % DUNGEON_SIZE,
            (static_cast<int>(start.y)) % DUNGEON_SIZE,
            (static_cast<int>(start.z)) % DUNGEON_SIZE,
            BlockType::Inactive);
  }
}

void Dungeon::createRoom(std::shared_ptr<Chunk> chunk)
{
  // Rooms are just empty chunks for now.
  chunk->setAllBlocks(BlockType::Inactive);
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
  std::cout << "Dungeon representation:" << std::endl;
  std::cout << " . represents solid chunks." << std::endl;
  std::cout << " R represents a room." << std::endl;
  std::cout << " o represents a path." << std::endl;
  std::cout
    << "\nEach solid chunk should be a 16 x 16 x 16 container of voxels."
    << std::endl;
  std::cout << "\nA room is also a 16 x 16 x 16 container of voxels, but"
            << "\nall of its voxels are inactive (air)." << std::endl;
  std::cout << "\nA path chunk is a mixture of both air and solid voxels."
            << std::endl;
}

bool Dungeon::isChunkAllActive(std::shared_ptr<Chunk> chunk)
{
  for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
  {
    for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
    {
      for (int k = 0; k < Chunk::CHUNK_SIZE; k++)
      {
        if (!(chunk->get(i, j, k))) return false;
      }
    }
  }
  return true;
}

bool Dungeon::isChunkAnyActive(std::shared_ptr<Chunk> chunk)
{
  for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
  {
    for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
    {
      for (int k = 0; k < Chunk::CHUNK_SIZE; k++)
      {
        if (chunk->get(i, j, k)) return true;
      }
    }
  }
  return false;
}
