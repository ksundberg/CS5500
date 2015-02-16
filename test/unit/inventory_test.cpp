#include <string>
#include <vector>
#include <catch.hpp>
#include "item.h"
#include "inventory.h"
#include "itemgen.h"
#include "logger.h"

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

    Item item3;
    item3 = item2;
    REQUIRE(item2.getName() == item3.getName());
    REQUIRE(item2.getCount() == item3.getCount());
    REQUIRE(item2.getDurability() == item3.getDurability());
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
    REQUIRE(prop.value == 10);
    REQUIRE(prop.image_file.compare("sword.png") == 0);
  }
}

SCENARIO(" Can add Items to an inventory. ")
{
  GIVEN("An Inventory and an Item.")
  {

    Item shield("Shield");
    Inventory inv(30);
    REQUIRE(inv.getSize() == 0);
    inv.addItem(shield);
    REQUIRE(inv.getSize() == 1);
    REQUIRE(inv.getItem(0).getName() == "Shield");
    REQUIRE(inv.takeItem(0).getName() == "Shield");
    REQUIRE(inv.getSize() == 0);
  }

  GIVEN("An Inventory with a small capacity.")
  {
    Inventory inv(1);
    Item a("Apple");
    Item b("Banana");
    REQUIRE(inv.addItem(a) == true);
    REQUIRE(inv.addItem(b) == false);
  }
  GIVEN("An Inventory is indexed out of bounds.")
  {
    Inventory inv(5);
    try
    {
      Item a = inv.takeItem(5);
    }
    catch (std::string errMsg)
    {
      REQUIRE(errMsg.compare("Error inventory item does not exist") == 0);
    }
  }
  GIVEN("We want all items from an Inventory")
  {
    Inventory inv(3);
    Item a("Apple");
    Item b("Banana");
    Item c("Coconut");
    inv.addItem(a);
    inv.addItem(b);
    inv.addItem(c);
    std::vector<Item> copied = inv.getAllItems();
    REQUIRE(copied[0].getName().compare("Apple") == 0);
    REQUIRE(copied[1].getName().compare("Banana") == 0);
    REQUIRE(copied[2].getName().compare("Coconut") == 0);
  }
}

SCENARIO("We want to generate items in parallel.")
{
  GIVEN("A large number of items to generate.")
  {
    std::vector<Item> items = ItemGen::genNItems(1000);

    REQUIRE(items.size() == 1000);
    REQUIRE(items[0].getName().size() > 0);
    REQUIRE(items[999].getName().size() > 0);
  }
}

TEST_CASE(" There is at least one name that maps to an ItemProperty ")
{
  auto keys = Item::getValidItemNames();
  REQUIRE(keys.size() > 0);
}
