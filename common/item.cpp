#include <string>
#include "item.h"
#include "item_property.h"

Item::Item(std::string name_) : name(name_), count(1), durability(DUR_MAX)
{

}

Item::Item(std::string name_, int count_, int durability_)
: name(name_)
{
  this->count = (count_ >= COUNT_MIN) ? count_ : COUNT_MIN;
  if (DUR_MIN <= durability_ && durability_ <= DUR_MAX)
	  this->durability = durability_;
  else
	  this->durability = DUR_MAX;
}

Item::~Item()
{
}

ItemProperty Item::getItemProperty() const
{
  return ItemManage::getItemProperty(this->name);
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



