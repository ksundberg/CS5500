#include <string>
#include "inventory.h"

Item::Item(std::string name_) : name(name_)
{
  // Items instantiate with default count and durability.
  count = 1;
  durability = 100;
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
