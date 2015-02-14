#include <string>
#include "item.h"
#include "logger.h"

Item::PropMap Item::initMap()
{
  // TODO: support deserialization for ItemProperties.
  // ItemProperty values are hard coded for now.
  PropMap map;
  Weapon sword{10, 4.0, "A sword.", "sword.png", 10};
  map.emplace("Sword", sword);

  Armor shield{20, 4.0, "A shield.", "shield.png", 10, BodyPart::ARM};
  map.emplace("Shield", shield);

  Usable cantaloupe{1, 1.0, "A cantaloupe.", "cantaloupe.png", 2};
  map.emplace("Cantaloupe", cantaloupe);
  return map;
}

Item::PropMap Item::properties = initMap();

std::vector<std::string> Item::getValidItemNames()
{
  std::vector<std::string> keys;
  for (auto pair : properties)
  {
    keys.push_back(pair.first);
  }
  return keys;
}

ItemProperty Item::default_property{0, 0.0, "Unknown.", "unknown.png"};

Item::Item() : name("Unknown"), count(COUNT_MIN), durability(DUR_MAX)
{
}
Item::Item(std::string name_)
  : name(name_), count(COUNT_MIN), durability(DUR_MAX)
{
}

Item::Item(std::string name_, int count_, int durability_) : name(name_)
{
  this->count = (count_ >= COUNT_MIN) ? count_ : COUNT_MIN;
  this->durability =
    (DUR_MIN <= durability_ && durability_ <= DUR_MAX) ? durability_ : DUR_MAX;
}

void Item::operator=(const Item& incoming)
{
  name = incoming.getName();
  count = incoming.getCount();
  durability = incoming.getDurability();
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
