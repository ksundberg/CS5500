#include <string>
#include "item_property.h"

ItemProperty ItemManage::getItemProperty(std::string name)
{
  ItemProperty prop(0, 0, 0.0, name, "default.png", nullptr, nullptr, nullptr);
  return prop;
}

void ItemManage::initializeData()
{
}
