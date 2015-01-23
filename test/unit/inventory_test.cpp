#include <string>
#include <catch.hpp>
#include <inventory.cpp>

SCENARIO(" All Items have a description ", "[Item]")
{
  GIVEN("An Item with 'Sword' as its name.")
  {
    Item item("Sword");
    REQUIRE(item.name.compare("Sword") == 0);

    ItemProperty prop = item.getItemProperty();
    REQUIRE(prop.description.size() > 0);
  }
}
