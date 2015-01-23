#include <string>
#include <catch.hpp>
#include <inventory.cpp>

SCENARIO(" All Items have a name, ItemProperty, count, and durability.", "[Item]")
{
  GIVEN("An Item with 'Sword' as its name.")
  {
    Item item("Sword");
    REQUIRE(item.getName().compare("Sword") == 0);

    REQUIRE(item.getCount() > 0);

    REQUIRE(item.getDurability() >= 0);


    ItemProperty prop = item.getItemProperty();
    REQUIRE(prop.description.size() > 0);
    REQUIRE(prop.value >= 0);
    REQUIRE(prop.weight >=0);
    REQUIRE(prop.image_file.size() > 0);
  }
}


SCENARIO(" All Wearables have a defense stat bigger than or equal to 0. " )
{
  GIVEN("　A Wearable named 'T-Shirt'. ")
  {
    Armor shirt("T-Shirt");
    REQUIRE(shirt.getDefense() >= 0);

    Armor sweater("Turtleneck", 1, 100, -20);
    REQUIRE(sweater.getDefense() >= 0);

  }
}
