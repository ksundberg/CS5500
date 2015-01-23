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

SCENARIO(" The durability and count of Items can change. ")
{
  GIVEN(" An Item named 'Cantaloupe' with count 3 and durability 8.")
  {
    Item item("Cantaloupe", 3, 8);
    REQUIRE(item.getCount() == 3);
    item.setCount(5);
    REQUIRE(item.getCount() == 5);

    REQUIRE(item.getDurability() == 8);
    item.setDurability(100);
    REQUIRE(item.getDurability() == 100);
  }
}
