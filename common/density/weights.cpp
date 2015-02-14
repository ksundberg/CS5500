#include "weights.h"


//Return a map of material densities, scaled by (x,y,z)
std::map<std::string, int> getXYZDensities(std::vector<Material> worldMap, int (*f) (Material) ){
    std::map<std::string, int> densities;
    std::for_each(worldMap.begin(),worldMap.end(),[&](Material m){
           densities[m.type] += f(m);
    });
    return densities;
}

//I'm not sure if this should be returning a float or a Material Density
//Do we need to know what type of material it was that was the highest?
MaterialDensity getMaterialDensity(std::map<std::string, int> densities, std::map<std::string, int> weights){

 //   std::accumulate(densities.begin(), densities.end(), 0, [&](std::pair<const std::basic_string<char>, int>& d1, std::pair<const std::basic_string<char>, int>& d2){
         
   // });
}

int main(){
    std::vector<Material> points;
    std::map<std::string, int> weights;
    std::map<std::string, int> densities;
    
    weights[std::string("Stone")] = 1;
    points.push_back(*(new Material(3,3,3, "Stone")));
    points.push_back(*(new Material(4,1,7, "muffin")));
 
    auto  xyzWeight =  [] (Material m){
        return m.z * 2;
    };
    
    auto materialWeight = [] (std::string type){
            if(type == "Stone")
                return 1.f;
            if(type == "Muffin")
                return 100.f;
    };

    densities = getXYZDensities(points, xyzWeight);
    auto density = getMaterialDensity(densities, weights);
    
    std::cout << densities[std::string("Stone")] << ":" << densities[std::string("muffin")]<<std::endl;

    return 0;
}
