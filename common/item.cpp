#include <string>
#include "item.h"
#include "logger.h"

Item::PropMap Item::initMap()
{
  PropMap map;
  ItemProperty w = Weapon(10, 4.0, "A sword.", "sword.png", 10);
  map.insert(std::pair<std::string, ItemProperty>("Sword", w));
  return map;
}
Item::PropMap Item::properties = initMap();
ItemProperty Item::default_property =
    ItemProperty(0, 0.0, "Unknown.", "unknown.png");


Item::Item(std::string name_)
  : name(name_), count(COUNT_MIN), durability(DUR_MAX)
{
}

Item::Item(std::string name_, int count_, int durability_) : name(name_)
{
  this->count = (count_ >= COUNT_MIN) ? count_ : COUNT_MIN;
  if (DUR_MIN <= durability_ && durability_ <= DUR_MAX)
    this->durability = durability_;
  else
    this->durability = DUR_MAX;
}

ItemProperty Item::getProperty() const
{
  auto iter = properties.find(name);
  return (iter != properties.end()) ? iter->second : default_property;
}


std::string Item::getName() const
{
  return this->name;
}

int Item::getCount() const
{
  return this->count;
}


int Item::getDurability() const
{
  return this->durability;
}
