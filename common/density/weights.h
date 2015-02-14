#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>

struct rPrism{
    int x, y, z;
    int height, width, depth;
};


//This is a standin struct because I wasn't compiling with the rest of the project
//Should be close enough to only do some simple refactoring though
struct Material{
    int x;
    int y;
    int z;
    std::string type;
    Material(int x2, int y2, int z2, std::string type2){
        x = x2;
        y = y2;
        z = z2;
        type = type2;
    }
};

struct MaterialDensity{
  std::string type;
  float density; // 0-1 value
};

std::map<std::string, int> getXYZDensities(std::vector<Material> worldMap, int (*f) (Material) );

MaterialDensity getMaterialDensity(std::map<std::string, int> densities, std::map<std::string, int> weights);

