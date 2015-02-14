#ifndef ITEM_HEADER
#define ITEM_HEADER

#include <string>
#include <vector>
#include <unordered_map>

// An ItemProperty contains information true across all instances of an
// Item. For instance, all swords have the same description, so
// this sort of information can be shared across all items.
struct ItemProperty
{
  const int value;
  const float weight;
  const std::string description;
  const std::string image_file;
  ItemProperty(int v, float w, std::string d, std::string i)
    : value(v), weight(w), description(d), image_file(i)
  {
  }
};

struct Weapon : ItemProperty
{
  const int default_attack;
  Weapon(int v, float w, std::string d, std::string i, int da)
    : ItemProperty(v, w, d, i), default_attack(da)
  {
  }
};

enum class BodyPart
{
  HEAD,
  BODY,
  LEGS,
  FEET,
  ARM
};

struct Armor : ItemProperty
{
  const int default_defense;
  const BodyPart body_part;
  Armor(int v, float w, std::string d, std::string i, int dd, BodyPart b)
    : ItemProperty(v, w, d, i), default_defense(dd), body_part(b)
  {
  }
};

struct Usable : ItemProperty
{
  const int health_points;
  Usable(int v, float w, std::string d, std::string i, int hp)
    : ItemProperty(v, w, d, i), health_points(hp)
  {
  }
};

class Item
{
public:
  Item();
  Item(std::string name_);
  Item(std::string name_, int count_, int durability_);
  void operator=(const Item& incoming);

  // An item property can be either a Weapon, Armor, or Usable.
  ItemProperty getProperty() const;
  std::string getName() const;
  int getCount() const;
  int getDurability() const;

  // Hash ItemProperty values by an Item's name.
  typedef std::unordered_map<std::string, ItemProperty> PropMap;

  static std::vector<std::string> getValidItemNames();

private:
  std::string name;
  int count;
  int durability;
  static const int DUR_MAX = 100;
  static const int DUR_MIN = 0;
  static const int COUNT_MIN = 1;
  static PropMap properties;
  static ItemProperty default_property;
  static PropMap initMap();
};

#endif
