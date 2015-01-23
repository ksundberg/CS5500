#include <string>
#include "inventory.h"

Item::Item(std::string name_) : name(name_)
{
  // Items instantiate with default count and durability.
  count = 1;
  durability = 100;
}

Item::Item(std::string name_, int count_, int durability_)
: name(name_), count(count_), durability(durability_)
{

}

Item::~Item()
{
}

ItemProperty Item::getItemProperty() const
{
  return this->defaultItemProperty();
}

ItemProperty Item::defaultItemProperty() const
{
  return ItemProperty(0, 0, "Unknown Item.", "unknown.png");
}

std::string Item::getName() const
{
  return this->name;
}

int Item::getCount() const
{
  return this->count;
}

void Item::setCount(int count)
{
  this->count = count;
}

int Item::getDurability() const
{
  return this->durability;
}

void Item::setDurability(int durability)
{
  this->durability = durability;
}

