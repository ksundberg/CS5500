#ifndef ITEM_HEADER
#define ITEM_HEADER

#include <string>
#include <unordered_map>

struct Weapon
{
  const int default_attack;
  Weapon(int default_attack_) : default_attack(default_attack_) {}
};

enum class BodyPart
{
  HEAD,
  BODY,
  LEGS,
  FEET
};

struct Armor
{
  const int default_defense;
  const BodyPart body_part;

  Armor(int default_defense_, BodyPart body_part_)
    : default_defense(default_defense_), body_part(body_part_)
  {
  }
};

struct Usable
{
  const int health_points;
  Usable(int health_points_) : health_points(health_points_) {}
};

// An ItemProperty contains information true across all instances of an
// Item. For instance, all swords have the same description, so
// this sort of information can be shared across all items.
template <class T>
struct ItemProperty
{
  ItemProperty(int v,
               int r,
               float w,
               std::string d,
               std::string i,
               T* s)
    : value(v)
    , rarity(r)
    , weight(w)
    , description(d)
    , image_file(i)
    , spec(s)
  {
  }
  ~ItemProperty()
  {
    delete spec;
  }
  const int value;
  const int rarity;
  const float weight;
  const std::string description;
  const std::string image_file;
  const T* spec;
};

template <class T>
class Item
{
public:
  Item(std::string name_);
  Item(std::string name_, int count_, int durability_);

  // An item property can be either a Weapon, Armor, or Usable.
  ItemProperty<T> getItemProperty() const;
  std::string getName() const;
  int getCount() const;
  int getDurability() const;

private:
  const std::string name;
  int count;
  int durability;
  static const int DUR_MAX = 100;
  static const int DUR_MIN = 0;
  static const int COUNT_MIN = 1;
  static void initializeItems();
  static std::unordered_map<std::string, ItemProperty<Weapon>> weapon_specs;
  static std::unordered_map<std::string, ItemProperty<Armor>> armor_specs;
  static std::unordered_map<std::string, ItemProperty<Usable>> usable_specs;
};

#endif
