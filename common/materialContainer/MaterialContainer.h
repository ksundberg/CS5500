//
// MaterialContainer.h
// created by David Griffin and Soren Rasmussen
// 1/24/2015
// for project: CS5500
//

#ifndef MATERIALCONTAINER_H
#define MATERIALCONTAINER_H
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <type_traits>
#include <map>
#include <memory>
#include "PerlinNoise.h"
#include "block.h"



extern const double GROUND_OFFSET;
extern const double GROUND_SMOOTHNESS;
extern const double BIOME_OFFSET;
extern const double BIOME_SMOOTHNESS;
extern const double BIOSPHERE_OFFSET;
extern const double BIOSPHERE_SMOOTHNESS;


class Material
{
private:
  std::string name;
  BlockType type;
  double freq;
  static std::map <std::string, std::shared_ptr<Material>> materialMap;
public:
  Material(std::string inName, BlockType inType, double inFreq) : name(inName), type(inType), freq(inFreq) {}
  static std::shared_ptr<Material> makenew(std::string name, BlockType type, double freq);
  double getFreq() { return freq; }
  std::string getName() { return name; }
  std::shared_ptr<Material> getMaterial(int x, int y, int z);
  BlockType getType(){ return type; }
  void setType(BlockType BT){ type = BT; }
  static std::shared_ptr<Material> getFromType(BlockType BT);
  static std::shared_ptr<Material> Coal();
  static std::shared_ptr<Material> Iron();
  static std::shared_ptr<Material> Soil();
  static std::shared_ptr<Material> Gravel();
  static std::shared_ptr<Material> Sand();
  static std::shared_ptr<Material> Diamond();
  static std::shared_ptr<Material> Stone();
  static std::shared_ptr<Material> Gold();
  static std::shared_ptr<Material> Default();
};

template <class T> class MaterialContainer
{
 protected:
  double translate(int v){return((v+offset)* smoothness);}
  static PerlinNoise noise;
  // temp PerlinNoise until intergration with project PerlinNoise
  double PN(int x, int y, int z)
  {
    static const int DEPTH=5;
    return noise.turbulence3D(translate(x), translate(y), translate(z), DEPTH);
    //return (static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
  }

  std::string name;
  std::vector<std::shared_ptr<T>> contents;
  double freq; // likelihood of a material to show up on a scale of (0,1).
  double smoothness;
  double contentFreq;
  double offset;

  // set the probability of a material to get created
  void setContentFreq()
  {
    contentFreq = 0;
    for (auto c : contents) contentFreq += c->getFreq();
  }

 public:
  // MaterialContainer constructors and operator
  MaterialContainer(std::string name, std::vector<std::shared_ptr<T>> contents, double freq, double smoothness, double offset)
    :name(name), contents(contents), freq(freq), smoothness(smoothness), offset(offset)
  {
    setContentFreq();
  }
  MaterialContainer(const MaterialContainer& MC)
    : name(MC.name)
    , contents(MC.contents)
    , freq(MC.freq)
    , smoothness(MC.smoothness)
    , contentFreq(MC.contentFreq)
    , offset(MC.offset)
    {}
  MaterialContainer& operator=(const MaterialContainer&) { return *this; }

  // decides what element to return based on noise input
  std::shared_ptr<T> getElement(double noise)
  {
    double tot = 0.0;
    auto target = contentFreq * noise;
    for (uint i = 0;i< contents.size();++i)
      {
	    tot += contents[i]->getFreq();
	    if (tot >= target) return contents[i];
      }
    return contents[0];
  }

  // Returns frequency of an element
  double getFreq() { return freq; }

  // Returns rarity of an element
  double getRarity() { return 1 - freq; };

  // Get the material type of a block at an (x,y,z) coordinate
  virtual std::shared_ptr<Material> getMaterial(int x, int y, int z)
  {
    double noise = PN(x, y, z);
    std::shared_ptr<T> content = getElement(noise);
    return content->getMaterial(x, y, z);
  }
};

class GroundContainer : public MaterialContainer<Material>
{
 public:
  std::shared_ptr<Material> getMaterial(int x, int y, int z);
  static std::shared_ptr<GroundContainer> sand();
  static std::shared_ptr<GroundContainer> oasis();

  static std::shared_ptr<GroundContainer> ironDeposits();
  static std::shared_ptr<GroundContainer> diamondDeposits();
  static std::shared_ptr<GroundContainer> goldDeposits();
  static std::shared_ptr<GroundContainer> noOre();

  static std::shared_ptr<GroundContainer> soil();
  static std::shared_ptr<GroundContainer> rockySoil();
  static std::shared_ptr<GroundContainer> sandySoil();
  GroundContainer(std::string name,
         std::vector<std::shared_ptr<Material>> contents,
         double freq,
         double smoothness)
    : MaterialContainer(name, contents, freq, GROUND_SMOOTHNESS, GROUND_OFFSET)
    {
      (void) smoothness;
    }
};

class Biome : public MaterialContainer<GroundContainer>
{
 public:
  static std::shared_ptr<Biome> sandyDesert();
  static std::shared_ptr<Biome> mountain();
  static std::shared_ptr<Biome> fertileFarmland();
  Biome(std::string name,
        std::vector<std::shared_ptr<GroundContainer>> contents,
        double freq,
        double smoothness)
    : MaterialContainer(name, contents, freq, BIOME_SMOOTHNESS, BIOME_OFFSET)
    {
      (void) smoothness;
    }
};

class Biosphere : public MaterialContainer<Biome>
{
 public:
  Biosphere(std::string name,
            std::vector<std::shared_ptr<Biome>> contents,
            double freq,
            double smoothness)
    : MaterialContainer(name, contents, freq, BIOSPHERE_SMOOTHNESS, BIOSPHERE_OFFSET)
    {
      (void) smoothness;
    }
   BlockType GetBlockType(int x, int y, int z){
     return getMaterial(x,y,z)-> getType();
   }
  static Biosphere getBasicBiosphere();
};



#endif
