#ifndef ITEM_PROPERTY_HEADER
#define ITEM_PROPERTY_HEADER

#include <string>
#include <unordered_map>

// An ItemProperty contains information true across all instances of an
// Item. For instance, all swords have the same description, so
// this sort of information can be shared across all items.

struct WeaponProperty
{
  const int default_attack;
  WeaponProperty(int default_attack_)
  : default_attack(default_attack_)
  {}
};

enum class BodyPart
{
  HEAD,
  BODY,
  LEGS,
  FEET
};

struct ArmorProperty
{
  const int default_defense;
  const BodyPart body_part;

  ArmorProperty(int default_defense_, BodyPart body_part_)
  : default_defense(default_defense_), body_part(body_part_)
  {}
};

struct ConsumableProperty
{
  const int health_points;
  ConsumableProperty(int health_points_)
  : health_points(health_points_)
  {}
};

struct ItemProperty
{
  ItemProperty(int v, int r, float w, std::string d, std::string i)
    : value(v), rarity(r), weight(w), description(d), image_file(i)
  {
  }
  const int value;
  const int rarity;
  const float weight;
  const std::string description;
  const std::string image_file;

  // May be set to nullptr if undefined for particular item.
  WeaponProperty* weapon_property;
  ArmorProperty* armor_property;
  ConsumableProperty* consumable_property;

};

class ItemManage
{
public:
  static ItemProperty getItemProperty(std::string name);
private:
  void initializeData();
  std::unordered_map<std::string, ItemProperty> properties;
};

#endif
