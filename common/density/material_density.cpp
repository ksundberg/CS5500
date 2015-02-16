#include "material_density.h"
#include <vector>
#include <tbb/tbb.h>

void material_density_Map::add(Material& m,double d)
{
  add(m.name,d);
}

void material_density_Map::add(std::string m,double d)
{
  if(count(m)==0)
    find(m)->second+=d;
  else
    emplace(m,d);
}

void material_density_Map::add(material_density& md)
{
  add(md.first,md.second);
}

void material_density_Map::add(std::pair<const std::string,double> md)
{
  add(md.first,md.second);
}

double material_density_Map::findDensity(Material& m)
{
  return findDensity(m.name);
}

double material_density_Map::findDensity(std::string str)
{
  if(count(str)>0)
    return find(str)->second;
  else
    return 0.0;
}

material_density_Map material_density_Map::operator+(material_density_Map& mdMap)
{
  material_density_Map newMap;
  for(auto& md=mdMap.begin();md!=mdMap.end();++md)
  {
    newMap.add(*md);
  }
  for(auto& md=this->begin();md!=this->end();++md)
  {
    newMap.add(*md);
  }
  return newMap;
}

material_density_Map parallel_reduce_MD(std::vector<material_density_Map> vec)
{
  return tbb::parallel_reduce
  ( 
    tbb::blocked_range<std::vector<material_density_Map>::iterator>(vec.begin(), vec.end()), 
      material_density_Map(), 
      [](const tbb::blocked_range<std::vector<material_density_Map>::iterator>& r, material_density_Map init)->material_density_Map
      {
        for( std::vector<material_density_Map>::iterator a=r.begin(); a!=r.end(); ++a ) 
          init = init+*a;
          return init;
      },
      []( material_density_Map x, material_density_Map y )->material_density_Map{return x+y;}
  ); 
}
