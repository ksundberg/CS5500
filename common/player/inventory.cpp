#include "item.h"
#include "inventory.h"
Inventory::Inventory(int size) : capacity(size)
{
}
Inventory::~Inventory()
{
}
bool Inventory::addItem(Item item)
{
  if (inventory.size() < capacity)
  {
    inventory.push_back(item);
    return true;
  }
  else
  {
    return false;
  }
}
Item Inventory::takeItem(unsigned int index)
{
  Item remItem;
  boundsCheck(index);
  remItem = inventory[index];
  inventory.erase(inventory.begin() + index);
  return remItem;
}
Item Inventory::getItem(unsigned int index)
{
  boundsCheck(index);
  return inventory[index];
}
void Inventory::boundsCheck(unsigned int index)
{
  if (index >= inventory.size())
  {
    std::string errMsg = "Error inventory item does not exist";
    throw(errMsg);
  }
}
unsigned int Inventory::getSize()
{
  return inventory.size();
}
std::vector<Item> Inventory::getAllItems()
{
  std::vector<Item> inv(inventory);
  return inv;
}
