#include <string>
#include "item_property.h"

ItemProperty ItemManage::getItemProperty(std::string name)
{
  ItemProperty prop(10, 8, 20.0, name, "default.png");
  return prop;
}

void ItemManage::initializeData()
{

}
