#include "material_density.h"
#include <vector>
#include <tbb/tbb.h>

void
MaterialDensityMap::add (Material& m, double d)
{
  add (m.name, d);
}

void
MaterialDensityMap::add (std::string m, double d)
{
  if (count (m) == 0)
    {
      find (m)->second += d;
    }
  else
    {
      emplace (m, d);
    }
}

void
MaterialDensityMap::add (MaterialDensity& md)
{
  add (md.first, md.second);
}

void
MaterialDensityMap::add (std::pair<const std::string, double> md)
{
  add (md.first, md.second);
}

double
MaterialDensityMap::findDensity (Material& m)
{
  return findDensity (m.name);
}

double
MaterialDensityMap::findDensity (std::string str)
{
  if (count (str) > 0)
    return find (str)->second;
  else
    return 0.0;
}

MaterialDensityMap MaterialDensityMap::operator+ (MaterialDensityMap& mdMap)
{
  MaterialDensityMap newMap;
  for (std::map<std::string, double>::iterator mapIt = mdMap.begin (); mapIt != mdMap.end (); ++mapIt)
    {
      newMap.add (mapIt->first, mapIt->second);
    }
  for (std::map<std::string, double>::iterator mapIt = this->begin (); mapIt != this->end (); ++mapIt)
    {
      newMap.add (mapIt->first, mapIt->second);
    }
  return newMap;
}

//////////////////////////////////////////////////////////////////////////////
//Material Density Functions

std::vector<MaterialDensityMap>
material_density::prism_2_mapVector (RectangularPrism prism, std::function<std::string (Coordinate) > coordinate2materialNameFunction, std::function<float(int, int, int) > xyzWeightingFunction)
{
  tbb::blocked_range3d<int, int, int> range (prism.getX (), prism.getX () + prism.getLengthX (),
                                             prism.getY (), prism.getY () + prism.getWidthY (),
                                             prism.getZ (), prism.getZ () + prism.getHeightZ ());

  return tbb::parallel_reduce
          (
           range,
           std::vector<MaterialDensityMap>(),
           [coordinate2materialNameFunction, xyzWeightingFunction](const tbb::blocked_range3d<int, int, int> r, std::vector<MaterialDensityMap> init)->std::vector<MaterialDensityMap>
             {

               int xBegin = r.pages ().begin (),
                       xEnd = r.pages ().end (),
                       yBegin = r.rows ().begin (),
                       yEnd = r.rows ().end (),
                       zBegin = r.cols ().begin (),
                       zEnd = r.cols ().end ();

           //for each sub range given to me by tbb
           for (int xIt = xBegin; xIt != xEnd; ++xIt)
                 {
           for (int yIt = yBegin; yIt != yEnd; ++yIt)
                     {
           for (int zIt = zBegin; zIt != zEnd; ++zIt)
                         {
           Coordinate coordinate (xIt, yIt, zIt);
           std::string materialName = coordinate2materialNameFunction (coordinate);
           float weight = xyzWeightingFunction (xIt, yIt, zIt);
           MaterialDensityMap map;
           map.add (materialName, weight);
           init.push_back (map);
                         }
                     }
                 }

           //return the fully initialized mapVector
           return init;
             },
           [](std::vector<MaterialDensityMap> vecA, std::vector<MaterialDensityMap> vecB)->std::vector<MaterialDensityMap>
             {
               //return the concatenation of two vectors
               vecA.insert (vecA.end (), vecB.begin (), vecB.end ());
               return vecA;
             }
           );
}

MaterialDensityMap
material_density::parallel_reduce_MD (std::vector<MaterialDensityMap> vec)
{
  return tbb::parallel_reduce
          (
           tbb::blocked_range<std::vector<MaterialDensityMap>::iterator>(vec.begin (), vec.end ()),
           MaterialDensityMap (),
           [](const tbb::blocked_range<std::vector<MaterialDensityMap>::iterator>& r, MaterialDensityMap init)->MaterialDensityMap
             {
               for (std::vector<MaterialDensityMap>::iterator a = r.begin (); a != r.end (); ++a)
                 init = init + *a;
               return init;
             },
           [](MaterialDensityMap x, MaterialDensityMap y)->MaterialDensityMap
             {
               return x + y;
             }
           );
}

float
material_density::parallel_reduce_MDM (MaterialDensityMap mdm, std::function<float(std::string) > materialWeightingFunction)
{
  //Soren's ToDo: reduce the MaterialDensityMap to a float using the materialWeightingFunction

  //voided variables so that compiler doesn't complain about unused variables
  //can be removed when variables are actually used
  (void) mdm;
  (void) materialWeightingFunction;

  return 0;
}


///////////////////////////////////////////////////////////////////////////////
// Basic weightings functions that may be used in place of lambdas

std::string
material_density::basicCoordinate2materialNameFunction (Coordinate coordinate)
{
  //This is a filler function until the World and Material are linked
  (void) coordinate;
  return "Stone";
}

float
material_density::basicXYZWeightingFunction (int x, int y, int z)
{
  (void) x;
  (void) y;
  (void) z;
  return 1;
};

float
material_density::basicMaterialWeightingFunction (std::string material)
{
  (void) material;
  return 1;
};

