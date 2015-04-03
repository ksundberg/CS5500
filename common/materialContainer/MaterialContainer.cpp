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
  std::vector<std::shared_ptr<Biome>> vec;
  vec.push_back(Biome::sandyDesert());
  vec.push_back(Biome::mountain());
  vec.push_back(Biome::fertileFarmland());
  std::string name = "Biosphere";
  Biosphere bs(name, vec, 1.0, 50.0);
  return bs;
}

std::shared_ptr<Biome> Biome::sandyDesert()
{
  std::vector<std::shared_ptr<GroundContainer>> vec;
  vec.push_back(GroundContainer::noOre());
  vec.push_back(GroundContainer::sand());
  vec.push_back(GroundContainer::oasis());

  std::string name = "sandyDesert";
  return std::make_shared<Biome>(name, vec, .33, 10.0);
}

std::shared_ptr<Biome> Biome::mountain()
{
  std::vector<std::shared_ptr<GroundContainer>> vec;
  vec.push_back(GroundContainer::noOre());
  vec.push_back(GroundContainer::diamondDeposits());
  vec.push_back(GroundContainer::goldDeposits());
  vec.push_back(GroundContainer::ironDeposits());

  std::string name = "Mountain";
  return std::make_shared<Biome>(name, vec, .33, 10.0);
}

std::shared_ptr<Biome> Biome::fertileFarmland()
{
  std::vector<std::shared_ptr<GroundContainer>> vec;
  vec.push_back(GroundContainer::soil());
  vec.push_back(GroundContainer::rockySoil());
  vec.push_back(GroundContainer::sandySoil());

  std::string name = "fertileFarmland";
  return std::make_shared<Biome>(name, vec, .33, 10.0);
}

std::shared_ptr<GroundContainer> GroundContainer::sand()
{
  std::vector<std::shared_ptr<Material>> vec;
  vec.push_back(Material::Sand());

  std::string name = "sand";
  return std::make_shared<GroundContainer>(name, vec, .3, 5.0);

}

std::shared_ptr<GroundContainer> GroundContainer::oasis()
{
  std::vector<std::shared_ptr<Material>> vec;
  vec.push_back(Material::Sand());

  vec.push_back(Material::Soil());

  std::string name = "oasis";
  return std::make_shared<GroundContainer>(name, vec, .05, 5.0);
}

std::shared_ptr<GroundContainer> GroundContainer::ironDeposits()
{
  std::vector<std::shared_ptr<Material>> vec;
  vec.push_back(Material::Stone());
  vec.push_back(Material::Iron());

  std::string name = "ironDeposits";
  return std::make_shared<GroundContainer>(name, vec, .2, 5.0);
}

std::shared_ptr<GroundContainer> GroundContainer::goldDeposits()
{
  std::vector<std::shared_ptr<Material>> vec;
  vec.push_back(Material::Stone());
  vec.push_back(Material::Gold());
  vec.push_back(Material::Iron());

  std::string name = "goldDeposits";
  return std::make_shared<GroundContainer>(name, vec, .1, 5.0);
}

std::shared_ptr<GroundContainer> GroundContainer::diamondDeposits()
{
  std::vector<std::shared_ptr<Material>> vec;
  vec.push_back(Material::Stone());
  vec.push_back(Material::Diamond());
  vec.push_back(Material::Coal());

  std::string name = "diamondDeposits";
  return std::make_shared<GroundContainer>(name, vec, .03, 5.0);
}

std::shared_ptr<GroundContainer> GroundContainer::noOre()
{
  std::vector<std::shared_ptr<Material>> vec;
  vec.push_back(Material::Stone());
  vec.push_back(Material::Soil());
  vec.push_back(Material::Coal());
  vec.push_back(Material::Gravel());
  vec.push_back(Material::Sand());

  std::string name = "noOre";
  return std::make_shared<GroundContainer>(name, vec, .5, 10.0);
}

std::shared_ptr<GroundContainer> GroundContainer::soil()
{
  std::vector<std::shared_ptr<Material>> vec;
  vec.push_back(Material::Soil());

  std::string name = "soil";
  return std::make_shared<GroundContainer>(name, vec, .5, 10.0);
}

std::shared_ptr<GroundContainer> GroundContainer::rockySoil()
{
  std::vector<std::shared_ptr<Material>> vec;
  vec.push_back(Material::Stone());
  vec.push_back(Material::Soil());
  vec.push_back(Material::Gravel());

  std::string name = "rockySoil";
  return std::make_shared<GroundContainer>(name, vec, .2, 10.0);
}

std::shared_ptr<GroundContainer> GroundContainer::sandySoil()
{
  std::vector<std::shared_ptr<Material>> vec;
  vec.push_back(Material::Sand());
  vec.push_back(Material::Soil());

  std::string name = "sandySoil";
  return std::make_shared<GroundContainer>(name, vec, .2, 10.0);
}

std::shared_ptr<Material> GroundContainer::getMaterial(int x, int y, int z)
{
  double noise = PN(x, y, z);
  return getElement(noise);
}

std::shared_ptr<Material> Material::makenew(std::string name, BlockType type, double freq){
  materialMap.insert(std::pair<std::string,std::shared_ptr<Material>>(name,std::make_shared<Material>(name,type,freq)));
  return materialMap[name];
}

std::shared_ptr<Material> Material::getFromType(BlockType BT)
{
  switch(BT)
  {
    case BlockType::Coal:
       return Material::Coal(); 
     
     case BlockType::Iron:
       return Material::Iron(); 

     case BlockType::Ground:
       return Material::Soil(); 

     case BlockType::Gravel:
       return Material::Gravel(); 

     case BlockType::Sand:
       return Material::Sand(); 

     case BlockType::Diamond:
       return Material::Diamond(); 

     case BlockType::Stone:
       return Material::Stone(); 

     case BlockType::Gold:
       return Material::Gold();

     default:
       return Material::Default(); 
  }
}


std::shared_ptr<Material> Material::Default()
{
  if(materialMap.count("None")>0)
    return materialMap["None"]; 

  return Material::makenew("None", BlockType::Inactive, .2);
}
std::shared_ptr<Material> Material::Coal()
{
  if(materialMap.count("Coal")>0)
    return materialMap["Coal"]; 
  return Material::makenew("Coal", BlockType::Coal, .2);
}
std::shared_ptr<Material> Material::Iron()
{
  if(materialMap.count("Iron")>0)
    return materialMap["Iron"]; 
  return Material::makenew("Iron", BlockType::Iron, .1);
}
std::shared_ptr<Material> Material::Soil()
{
  if(materialMap.count("Soil")>0)
    return materialMap["Soil"]; 
  return Material::makenew("Soil", BlockType::Ground, 1.0);
}
std::shared_ptr<Material> Material::Gravel()
{
  if(materialMap.count("Gravel")>0)
    return materialMap["Gravel"]; 
  return Material::makenew("Gravel", BlockType::Gravel, .2);
}
std::shared_ptr<Material> Material::Sand()
{
  if(materialMap.count("Sand")>0)
    return materialMap["Sand"]; 
  return Material::makenew("Sand", BlockType::Sand, .7);
}
std::shared_ptr<Material> Material::Diamond()
{
  if(materialMap.count("Diamond")>0)
    return materialMap["Diamond"]; 
  return Material::makenew("Diamond", BlockType::Diamond, .05);
}
std::shared_ptr<Material> Material::Stone()
{
  if(materialMap.count("Stone")>0)
    return materialMap["Stone"]; 
  return Material::makenew("Stone", BlockType::Stone, .6);
}
std::shared_ptr<Material> Material::Gold()
{
  if(materialMap.count("Gold")>0)
    return materialMap["Gold"]; 
  return Material::makenew("Gold", BlockType::Gold, .1);
}

std::shared_ptr<Material> Material::getMaterial(int x, int y, int z)
{
  (void) x;
  (void) y;
  (void) z;
  return Default();
}

const double GROUND_OFFSET=2e5;
const double GROUND_SMOOTHNESS=2;

const double BIOME_OFFSET=1e5;
const double BIOME_SMOOTHNESS=1e-1;

const double BIOSPHERE_OFFSET=0;
const double BIOSPHERE_SMOOTHNESS=1e-3;
