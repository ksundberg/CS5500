#ifndef Inventory_h
#define Inventory_h

#include <string>
#include <unordered_map>

// An ItemProperty contains information true across all instances of an
// Item. For instance, all swords have the same description, so
// this sort of information can be shared across all items.
struct ItemProperty
{
  ItemProperty(int v, float w, std::string d, std::string i)
    : value(v), weight(w), description(d), image_file(i)
  {
  }
  const int value;
  const float weight;
  const std::string description;
  const std::string image_file;
};

class Item
{
public:
  Item(std::string name_);
  ~Item();
  int getCount() const;
  void setCount(int);
  int getDurability() const;
  void setDurability(int);
  ItemProperty getItemProperty() const;
  std::string getName() const;


private:
  const std::string name;
  ItemProperty defaultItemProperty() const;
  int count;
  int durability;
  // For now, all Items share an unordered_map that
  // maps names to their respective ItemProperty.
  static std::unordered_map<std::string, ItemProperty> properties;
};

enum class WearType
{
  HEAD,
  BODY,
  LEGS,
  FEET
};

// Wearables represent clothing, armor, etc.
class Wearable : Item
{
public:
  Wearable(std::string name_, int defense_, WearType bodyPart_);
  int getDefense() const;
  void setDefense(int);
  WearType getBodyPart() const;

private:
  const WearType bodyPart;
  int defense;
};

// Equippables only have an attack stat for now.
class Equippable : Item
{
public:
  Equippable(std::string name_, int attack_);
  int getAttack() const;
  void setAttack(int);

private:
  int attack;
};

// Consumables can be eaten. For now, they just add a health point value.
class Consumable : Item
{
public:
  Consumable(std::string name_, int health_);
  int getHealth() const;
  void setHealth(int);

private:
  int health;
};

#endif
