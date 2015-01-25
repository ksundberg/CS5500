#include <cstdlib>
#include <vector>
#include "item.h"
#include "inventory.h"
#include "itemgen.h"

// Very basic item generation for now.
Inventory ItemGen::genItems()
{
  auto keys = {"Sword", "Shield", "Cantaloupe"};
  Inventory inventory(50); // Inventory with capacity 50.
  for (auto k : keys)
  {
    inventory.addItem(Item(k, std::rand() % 10 + 1, std::rand() % 100 + 1));
  }
  return inventory;
}
