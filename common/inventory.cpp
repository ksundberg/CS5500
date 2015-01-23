#include <string>
#include "inventory.h"

Item::Item(std::string name_) : name(name_), count(1), durability(100)
{

}

Item::Item(std::string name_, int count_, int durability_)
: name(name_), count(count_), durability(durability_)
{

}

Item::~Item()
{
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


