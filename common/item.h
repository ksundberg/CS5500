#ifndef ITEM_HEADER
#define ITEM_HEADER

#include <string>
#include <unordered_map>
#include "item_property.h"

class Item
{
public:
  Item(std::string name_);
  Item(std::string name_, int count_, int durability_);
  ~Item();
  ItemProperty getItemProperty() const;
  std::string getName() const;
  int getCount() const;
  int getDurability() const;


private:
  const std::string name;
  int count;
  int durability;
  const int DUR_MAX = 100;
  const int DUR_MIN = 0;
  const int COUNT_MIN = 1;
};



#endif
