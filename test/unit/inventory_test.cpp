#include <string>
#include <catch.hpp>
#include <item.h>

SCENARIO(" All Items have a proper name, ItemProperty, count, and durability.", "[Item]")
{
  GIVEN("An Item with 'Sword' as its name.")
  {
    Item item("Sword");
    REQUIRE(item.getName().compare("Sword") == 0);

    REQUIRE(item.getCount() > 0);

    REQUIRE(0 <= item.getDurability());
    REQUIRE(item.getDurability() <= 100);


    ItemProperty prop = item.getItemProperty();
    REQUIRE(prop.description.size() > 0);
    REQUIRE(prop.value >= 0);
    REQUIRE(prop.weight >=0);
    REQUIRE(prop.image_file.size() > 0);
  }
}

