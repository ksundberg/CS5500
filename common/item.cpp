#include <string>
#include <map>
#include "item.h"
#include "logger.h"

ItemManage::PropMap ItemManage::initMap()
{
  PropMap map;
  ItemProperty w = Weapon(10, 4.0, "A sword.", "sword.png", 10);
  map.insert(std::pair<std::string, ItemProperty>("Sword", w));
  return map;
}
ItemManage::PropMap ItemManage::properties = initMap();
ItemProperty ItemManage::default_property =
    ItemProperty(0, 0.0, "Unknown.", "unknown.png");

ItemProperty ItemManage::getProperty(std::string name)
{
  auto iter = properties.find(name);
  return (iter != properties.end()) ? iter->second : default_property;
}


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
  return ItemManage::getProperty(name);
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
