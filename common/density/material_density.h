#ifndef MATERIALDENSITY_H
#define MATERIALDENSITY_H

//#include "MaterialContainer.h"
#include <utility>
#include <map>
#include <string>

#include <functional>
#include <tbb/concurrent_vector.h>

#include "rectangular_prism.h"
#include "../world.h"

class Material
{
public:
  std::string name;
  double freq;
};

class MaterialDensity : public std::pair<std::string, double>
{
public:
  MaterialDensity(Material& m, double d)
    : pair<std::string, double>(m.name, d){};

  MaterialDensity(std::string& str, double d)
    : pair<std::string, double>(str, d){};
};

class MaterialDensityMap : public std::map<std::string, double>
{
public:
  void add(Material& m, double d);
  void add(std::string str, double d);
  void add(MaterialDensity& md);
  void add(std::pair<const std::string, double>);
  double findDensity(Material& m);
  double findDensity(std::string str);
  MaterialDensityMap operator+(MaterialDensityMap& mdMap);
};

namespace material_density
{
// basic functions that can be used in place of lambda functions if desired
std::string basicCoordinate2materialNameFunction(Coordinate coordinate);
float basicXYZWeightingFunction(int x, int y, int z);
float basicMaterialWeightingFunction(std::string material);

// takes a prism, a way to get materials, and a way to get xyz weigtings and
// returns a vector of reducible materialDensity maps
tbb::concurrent_vector<MaterialDensityMap> prism_2_mapVector(
  RectangularPrism prism,
  std::function<std::string(Coordinate)> coordinate2materialNameFunction,
  std::function<float(int, int, int)> xyzWeightingFunction);

// takes a vector of materialDensityMaps and reduces them to a single
// MaterialDensityMap
MaterialDensityMap parallel_reduce_MD(
  tbb::concurrent_vector<MaterialDensityMap> vec);

// takes a MaterialDensityMap and a way to get materialWeightings and returns a
// float
float parallel_reduce_MDM(
  MaterialDensityMap& mdm,
  std::function<float(std::string)>& materialWeightingFunction);
}

#endif