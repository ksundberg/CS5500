//
// MaterialContainer.cpp
// created by David Griffin and Soren Rasmussen
// 1/24/2015
// for project: CS5500
//

#include "MaterialContainer.h"
#include <vector>

Biosphere Biosphere::getBasicBiosphere()
{
  std::vector<Biome> vec;
  vec.push_back(Biome::sandyDesert());
  vec.push_back(Biome::mountain());
  vec.push_back(Biome::fertileFarmland());
  std::string name = "Biosphere";
  Biosphere bs(name, vec, 1.0, 50.0);
  return bs;
}

Biome Biome::sandyDesert()
{
  std::vector<Ground> vec;
  vec.push_back(Ground::noOre());
  vec.push_back(Ground::sand());
  vec.push_back(Ground::oasis());

  std::string name = "sandyDesert";
  Biome bi(name, vec, .33, 10.0);
  return bi;
}

Biome Biome::mountain()
{
  std::vector<Ground> vec;
  vec.push_back(Ground::noOre());
  vec.push_back(Ground::diamondDeposits());
  vec.push_back(Ground::goldDeposits());
  vec.push_back(Ground::ironDeposits());

  std::string name = "Mountain";
  Biome bi(name, vec, .33, 10.0);
  return bi;
}

Biome Biome::fertileFarmland()
{
  std::vector<Ground> vec;
  vec.push_back(Ground::soil());
  vec.push_back(Ground::rockySoil());
  vec.push_back(Ground::sandySoil());

  std::string name = "fertileFarmland";
  Biome bi(name, vec, .33, 10.0);
  return bi;
}

Ground Ground::sand()
{
  std::vector<Material> vec;
  vec.push_back(Material::Sand());

  std::string name = "sand";
  Ground g(name, vec, .3, 5.0);
  return g;
}

Ground Ground::oasis()
{
  std::vector<Material> vec;
  vec.push_back(Material::Sand());

  vec.push_back(Material::Soil());

  std::string name = "oasis";
  Ground g(name, vec, .05, 5.0);
  return g;
}

Ground Ground::ironDeposits()
{
  std::vector<Material> vec;
  vec.push_back(Material::Stone());
  vec.push_back(Material::Iron());

  std::string name = "ironDeposits";
  Ground g(name, vec, .2, 5.0);
  return g;
}

Ground Ground::goldDeposits()
{
  std::vector<Material> vec;
  vec.push_back(Material::Stone());
  vec.push_back(Material::Gold());
  vec.push_back(Material::Iron());

  std::string name = "goldDeposits";
  Ground g(name, vec, .1, 5.0);
  return g;
}

Ground Ground::diamondDeposits()
{
  std::vector<Material> vec;
  vec.push_back(Material::Stone());
  vec.push_back(Material::Diamond());
  vec.push_back(Material::Coal());

  std::string name = "diamondDeposits";
  Ground g(name, vec, .03, 5.0);
  return g;
}

Ground Ground::noOre()
{
  std::vector<Material> vec;
  vec.push_back(Material::Stone());
  vec.push_back(Material::Soil());
  vec.push_back(Material::Coal());
  vec.push_back(Material::Gravel());
  vec.push_back(Material::Sand());

  std::string name = "noOre";
  Ground g(name, vec, .5, 10.0);
  return g;
}

Ground Ground::soil()
{
  std::vector<Material> vec;
  vec.push_back(Material::Soil());

  std::string name = "soil";
  Ground g(name, vec, .5, 10.0);
  return g;
}

Ground Ground::rockySoil()
{
  std::vector<Material> vec;
  vec.push_back(Material::Stone());
  vec.push_back(Material::Soil());
  vec.push_back(Material::Gravel());

  std::string name = "rockySoil";
  Ground g(name, vec, .2, 10.0);
  return g;
}

Ground Ground::sandySoil()
{
  std::vector<Material> vec;
  vec.push_back(Material::Sand());
  vec.push_back(Material::Soil());

  std::string name = "sandySoil";
  Ground g(name, vec, .2, 10.0);
  return g;
}

Material Ground::getMaterial()
{
  double noise = PerlinNoise();
  return getElement(noise);
}

Material Material::Coal()
{
  return Material("Coal", .2);
}
Material Material::Iron()
{
  return Material("Iron", .1);
}
Material Material::Soil()
{
  return Material("Soil", 1.0);
}
Material Material::Gravel()
{
  return Material("Gravel", .2);
}
Material Material::Sand()
{
  return Material("Sand", .7);
}
Material Material::Diamond()
{
  return Material("Diamond", .05);
}
Material Material::Stone()
{
  return Material("Stone", .6);
}
Material Material::Gold()
{
  return Material("Gold", .1);
}

Material Material::getMaterial()
{
  return Material(*this);
}
