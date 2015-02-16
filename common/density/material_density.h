#ifndef MATERIALDENSITY_H
#define MATERIALDENSITY_H

//#include "MaterialContainer.h"
#include <utility>
#include <map>
#include <string>

#include <functional>
#include <vector>

class Material
{
public:
  std::string name;
  double freq;
};

class material_density:public std::pair<std::string,double>
{
public:
  material_density(Material& m,double d):pair<std::string,double>(m.name,d){};
  material_density(std::string& str,double d):pair<std::string,double>(str,d){};
};

class material_density_Map:public std::map<std::string,double>
{
public:
  void add(Material& m,double d);
  void add(std::string str,double d);
  void add(material_density& md);
  void add(std::pair<const std::string,double>);
  double findDensity(Material& m);
  double findDensity(std::string str);
  material_density_Map operator+(material_density_Map& mdMap);
};

 material_density_Map parallel_reduce_MD(std::vector<material_density_Map> vec);

#endif