#include <string>
#include <catch.hpp>
#include <item.h>

SCENARIO(" All Items have a proper name, count, and durability.", "[Item]")
{
  GIVEN("An Item with 'Sword' as its name.")
  {
    Item item("Sword");
    REQUIRE(item.getName().compare("Sword") == 0);

    REQUIRE(item.getCount() > 0);
    REQUIRE(0 <= item.getDurability());
    REQUIRE(item.getDurability() <= 100);

    Item item2("Sword", 1, 100);

    REQUIRE(item2.getCount() == 1);
    REQUIRE(item2.getDurability() == 100);

    auto prop = item.getProperty();

  }

  GIVEN("An Item with incorrect arguments to it's constructor.")
  {
    Item item("Cantaloupe", -30, 200);

    REQUIRE(item.getCount() > 0);
    REQUIRE(0 <= item.getDurability());
    REQUIRE(item.getDurability() <= 100);

    Item item2("Orange", -1000, -200);

    REQUIRE(item2.getCount() > 0);
    REQUIRE(0 <= item2.getDurability());
    REQUIRE(item2.getDurability() <= 100);
  }
}

SCENARIO(" All Items have a proper ItemProperty. ")
{
  GIVEN("An Item without a defined property.")
  {
    Item item("Undefined item with a strange name");
    auto prop = item.getProperty();
    REQUIRE(prop.value == 0);
  }

  GIVEN("An Item with a defined property.")
  {
    Item item("Sword");
    auto prop = item.getProperty();
    REQUIRE(prop.value==10);
  }
}
