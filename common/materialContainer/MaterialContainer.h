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

class Material
{
private:
  std::string name;
  double freq;

public:
  Material(std::string name, double freq) : name(name), freq(freq) {}
  double getFreq() { return freq; }
  std::string getName() { return name; }
  static Material Coal();
  static Material Iron();
  static Material Soil();
  static Material Gravel();
  static Material Sand();
  static Material Diamond();
  static Material Stone();
  static Material Gold();
  Material getMaterial();
};

template <class T> class MaterialContainer
{
protected:
  // temp PerlinNoise until intergration with project PerlinNoise
  double PerlinNoise()
  {
    return (static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
  }

  std::string name;
  std::vector<T> contents;
  double freq; // likelihood of a material to show up on a scale of (0,1).
  double smoothness;
  double contentFreq;

  // set the probability of a material to get created
  void setContentFreq()
  {
    contentFreq = 0;
    for (T c : contents)
      contentFreq += c.getFreq();
  }

public:
  // MaterialContainer constructors and operator
  MaterialContainer(std::string name,
                    std::vector<T> contents,
                    double freq,
                    double smoothness)
    : name(name), contents(contents), freq(freq), smoothness(smoothness)
  {
    setContentFreq();
  }
  MaterialContainer(const MaterialContainer& MC)
    : name(MC.name)
    , contents(MC.contents)
    , freq(MC.freq)
    , smoothness(MC.smoothness)
    , contentFreq(MC.contentFreq)
  {
  }
  MaterialContainer& operator=(const MaterialContainer&) { return *this; }

  // decides what element to return based on noise input
  T getElement(double noise)
  {
    double tot = 0.0;
    auto target = contentFreq * noise;
    for (auto c : contents)
    {
      tot += c.getFreq();
      if (tot >= target) return c;
    }
    return contents[0];
  }

  // Returns frequency of an element
  double getFreq() { return freq; }

  // Returns rarity of an element
  double getRarity() { return 1 - freq; };

  // Get the material type of a block at an (x,y,z) coordinate
  virtual Material getMaterial()
  {
    double noise = PerlinNoise();
    T content = getElement(noise);
    return content.getMaterial();
  }
};

class Ground : public MaterialContainer<Material>
{
public:
  Material getMaterial();
  static Ground sand();
  static Ground oasis();

  static Ground ironDeposits();
  static Ground diamondDeposits();
  static Ground goldDeposits();
  static Ground noOre();

  static Ground soil();
  static Ground rockySoil();
  static Ground sandySoil();
  Ground(std::string name,
         std::vector<Material> contents,
         double freq,
         double smoothness)
    : MaterialContainer(name, contents, freq, smoothness)
  {
  }
};

class Biome : public MaterialContainer<Ground>
{
public:
  static Biome sandyDesert();
  static Biome mountain();
  static Biome fertileFarmland();
  Biome(std::string name,
        std::vector<Ground> contents,
        double freq,
        double smoothness)
    : MaterialContainer(name, contents, freq, smoothness)
  {
  }
};

class Biosphere : public MaterialContainer<Biome>
{
public:
  Biosphere(std::string name,
            std::vector<Biome> contents,
            double freq,
            double smoothness)
    : MaterialContainer(name, contents, freq, smoothness)
  {
  }

  static Biosphere getBasicBiosphere();
};

#endif
