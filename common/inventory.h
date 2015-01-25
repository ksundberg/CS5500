#ifndef INVENTORY_HEADER
#define INVENTORY_HEADER
#include <vector>
#include "item.h"
class Inventory
{
public:
  Item takeItem(unsigned int index);
  bool addItem(Item item);
  Item getItem(unsigned int index);
  std::vector<Item> getAllItems();
  Inventory(int size);
  unsigned int getSize();
  ~Inventory();

private:
  std::vector<Item> inventory;
  const unsigned int capacity;
  void boundsCheck(unsigned int index);
};

#endif
