#include <cstdlib>
#include <vector>
#include <algorithm>
#include "item.h"
#include "inventory.h"
#include "itemgen.h"
#include "tbb/tbb.h"

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

  auto names = Item::getPropertyKeys();
  auto func = [names, &items](const tbb::blocked_range<int>& r)
  {
    for (int i = r.begin(); i < r.end(); ++i)
    {
      items[i] = Item(names[std::rand() % names.size()]);
    }
  };
  tbb::parallel_for(tbb::blocked_range<int>(0, items.size()), func);
  return items;
}
