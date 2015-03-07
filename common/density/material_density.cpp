#include "material_density.h"
#include <tbb/tbb.h>

void MaterialDensityMap::add(Material& m, double d)
{
  add(m.name, d);
}

void MaterialDensityMap::add(std::string m, double d)
{
  if (count(m) == 0)
  {
    find(m)->second += d;
  }
  else
  {
    emplace(m, d);
  }
}

void MaterialDensityMap::add(MaterialDensity& md)
{
  add(md.first, md.second);
}

void MaterialDensityMap::add(std::pair<const std::string, double> md)
{
  add(md.first, md.second);
}

double MaterialDensityMap::findDensity(Material& m)
{
  return findDensity(m.name);
}

double MaterialDensityMap::findDensity(std::string str)
{
  if (count(str) > 0)
    return find(str)->second;
  else
    return 0.0;
}

MaterialDensityMap MaterialDensityMap::operator+(MaterialDensityMap& mdMap)
{
  MaterialDensityMap newMap;
  for (std::map<std::string, double>::iterator mapIt = mdMap.begin();
       mapIt != mdMap.end();
       ++mapIt)
  {
    newMap.add(mapIt->first, mapIt->second);
  }
  for (std::map<std::string, double>::iterator mapIt = this->begin();
       mapIt != this->end();
       ++mapIt)
  {
    newMap.add(mapIt->first, mapIt->second);
  }
  return newMap;
}

//////////////////////////////////////////////////////////////////////////////
// Material Density Functions

tbb::concurrent_vector<MaterialDensityMap> material_density::prism_2_mapVector(
  RectangularPrism prism,
  std::function<std::string(Coordinate)> coordinate2materialNameFunction,
  std::function<float(int, int, int)> xyzWeightingFunction)
{
  tbb::blocked_range3d<int, int, int> range(prism.getX(),
                                            prism.getX() + prism.getLengthX(),
                                            prism.getY(),
                                            prism.getY() + prism.getWidthY(),
                                            prism.getZ(),
                                            prism.getZ() + prism.getHeightZ());

  // ToDo:
  // I need to change input to be pass by reference
  // and I need to make sure my return variable isn't going out of scope
  // really I need to use the keyword new and a pointer
  // or I need to wrap this in some sort of RAII and change the return type to *
  // look-up shared_ptr
  tbb::concurrent_vector<MaterialDensityMap> concurrentMapVector;

  tbb::parallel_for(
    range,
    [&concurrentMapVector,
     coordinate2materialNameFunction,
     xyzWeightingFunction](const tbb::blocked_range3d<int, int, int> r)
    {

      int xBegin = r.pages().begin(), xEnd = r.pages().end(),
          yBegin = r.rows().begin(), yEnd = r.rows().end(),
          zBegin = r.cols().begin(), zEnd = r.cols().end();

      // for each sub range given to me by tbb
      for (int xIt = xBegin; xIt != xEnd; ++xIt)
      {
        for (int yIt = yBegin; yIt != yEnd; ++yIt)
        {
          for (int zIt = zBegin; zIt != zEnd; ++zIt)
          {
            Coordinate coordinate(xIt, yIt, zIt);
            std::string materialName =
              coordinate2materialNameFunction(coordinate);
            float weight = xyzWeightingFunction(xIt, yIt, zIt);
            MaterialDensityMap map;
            map.add(materialName, weight);
            concurrentMapVector.push_back(map);
          }
        }
      }
    });

  return concurrentMapVector;
}

MaterialDensityMap material_density::parallel_reduce_MD(
  tbb::concurrent_vector<MaterialDensityMap> vec)
{
  // ToDo: make this so that it is pass by reference
  // and make sure that variable being returned doesn't go out of scope

  return tbb::parallel_reduce(
    tbb::blocked_range<tbb::concurrent_vector<MaterialDensityMap>::iterator>(
      vec.begin(), vec.end()),
    MaterialDensityMap(),
    [](const tbb::blocked_range<
         tbb::concurrent_vector<MaterialDensityMap>::iterator>& r,
       MaterialDensityMap init) -> MaterialDensityMap
    {
      for (tbb::concurrent_vector<MaterialDensityMap>::iterator a = r.begin();
           a != r.end();
           ++a)
      {
        init = init + *a;
      }
      return init;
    },
    [](MaterialDensityMap x, MaterialDensityMap y) -> MaterialDensityMap
    {
      return x + y;
    });
}

struct Sum
{
  float value;
  Sum() : value(0) {}
  Sum(Sum& s, tbb::split sp)
  {
    (void)s;
    (void)sp;
    value = 0;
  }
  void operator()(const tbb::blocked_range<std::vector<float>::iterator>& r)
  {
    float temp = value;
    for (std::vector<float>::iterator a = r.begin(); a != r.end(); ++a)
    {
      temp += *a;
    }
    // TODO: compile error fix
    // value = temp;
  }
  void join(Sum& rhs) { value += rhs.value; }
};

float material_density::parallel_reduce_MDM(
  MaterialDensityMap& mdm,
  std::function<float(std::string)>& materialWeightingFunction)
{
  std::vector<float> massValues;
  for (auto iter = mdm.begin(); iter != mdm.end(); ++iter)
  {
    // to apply function materialWeightingFunction(std::string) to mdm values
    massValues.push_back(materialWeightingFunction(iter->first) * iter->second);
  }

  // use of struct Sum so that parallel_reduce will function
  Sum sum;
  tbb::parallel_reduce(tbb::blocked_range<std::vector<float>::iterator>(
                         massValues.begin(), massValues.end()),
                       sum);

  return sum.value;
}

///////////////////////////////////////////////////////////////////////////////
// Basic weightings functions that may be used in place of lambdas

std::string material_density::basicCoordinate2materialNameFunction(
  Coordinate coordinate)
{
  // This is a filler function until the World and Material are linked
  (void)coordinate;
  return "Stone";
}

float material_density::basicXYZWeightingFunction(int x, int y, int z)
{
  (void)x;
  (void)y;
  (void)z;
  return 1;
};

float material_density::basicMaterialWeightingFunction(std::string material)
{
  (void)material;
  return 1;
};
