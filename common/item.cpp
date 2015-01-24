#include <string>
#include "item.h"

template <class T>
Item<T>::Item(std::string name_)
  : name(name_), count(COUNT_MIN), durability(DUR_MAX)
{
}

template <class T>
Item<T>::Item(std::string name_, int count_, int durability_) : name(name_)
{
  this->count = (count_ >= COUNT_MIN) ? count_ : COUNT_MIN;
  if (DUR_MIN <= durability_ && durability_ <= DUR_MAX)
    this->durability = durability_;
  else
    this->durability = DUR_MAX;
}

template <class T>
ItemProperty<T> Item<T>::getItemProperty() const
{
  return ItemProperty<T>(0, 0, 0.0, "Nothing.", "unknown.png", nullptr);
}


template <class T>
std::string Item<T>::getName() const
{
  return this->name;
}

template <class T>
int Item<T>::getCount() const
{
  return this->count;
}


template <class T>
int Item<T>::getDurability() const
{
  return this->durability;
}

// For now: declarations so we can keep the header and cpp separate.
template Item<Weapon>::Item(std::string);
template Item<Weapon>::Item(std::string, int, int);
template std::string Item<Weapon>::getName() const;
template int Item<Weapon>::getCount() const;
template int Item<Weapon>::getDurability() const;
template ItemProperty<Weapon> Item<Weapon>::getItemProperty() const;

template Item<Armor>::Item(std::string);
template Item<Armor>::Item(std::string, int, int);
template std::string Item<Armor>::getName() const;
template int Item<Armor>::getCount() const;
template int Item<Armor>::getDurability() const;
template ItemProperty<Armor> Item<Armor>::getItemProperty() const;

template Item<Usable>::Item(std::string);
template Item<Usable>::Item(std::string, int, int);
template std::string Item<Usable>::getName() const;
template int Item<Usable>::getCount() const;
template int Item<Usable>::getDurability() const;
template ItemProperty<Usable> Item<Usable>::getItemProperty() const;
