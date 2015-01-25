#ifndef ITEMGEN_HEADER
#define ITEMGEN_HEADER
#include <vector>
#include "inventory.h"
#include "item.h"

namespace ItemGen
{
Inventory genItems();
std::vector<Item> genNItems(unsigned int n);
std::vector<Item> genNItems(unsigned int n);
};
#endif
