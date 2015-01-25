#include <cstdlib>
#include "item.h"
#include "inventory.h"
#include "itemgen.h"

// Very basic item generation for now.
Inventory ItemGen::genItems()
{
  auto keys = {"Sword", "Shield", "Cantaloupe"};
  Inventory inventory(50); // Inventory with capacity 50.
  int max_count = 5;
  int max_durability = 100;
  for (auto k : keys)
  {
    inventory.addItem(
      Item(k, std::rand() % max_count + 1, std::rand() % max_durability + 1));
  }
  return inventory;
}
