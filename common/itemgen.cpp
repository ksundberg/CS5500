#include <cstdlib>
#include <vector>
#include <algorithm>
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

// Extra gen function to demo a map pattern.
std::vector<Item> ItemGen::genNItems(unsigned int n)
{
  std::vector<Item> items;
  items.resize(n);
  auto func = [](Item& i)
  {
    i = Item("Balloon");
  };
  for_each(items.begin(), items.end(), func);
  return items;
}
