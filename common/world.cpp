#include "World.h"
#include "Object.h"
#include <vector>
#include <algorithm>
Coordinate::Coordinate(int ax=0, int ay=0, int az=0)
{
    x=ax,y=ay,z=az;
}
Coordinate & Coordinate::operator+=(const Coordinate & right)
{
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
	return *this;
}
const Coordinate Coordinate::operator+(const Coordinate & right) const
{
    Coordinate temp = *this;
	temp+=right;
    return temp;
}
Coordinate & Coordinate::operator-=(const Coordinate & right)
{
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;
	return *this;
}
const Coordinate Coordinate::operator-(const Coordinate & right) const
{
    Coordinate temp = *this;
	temp-=right;
    return temp;
}
//z is up and down
//add paralell fill
World::World(int tempX=1,int tempY=1, int tempZ=1)
{
    sizeX=tempX;
    sizeY=tempY;
    sizeZ=tempZ;
    std::vector<Object> list;
    list.resize(tempZ);
    std::vector<std::vector<Object>> listOList;
    listOList.resize(tempY);
    std::vector<std::vector<std::vector<Object>>> listOListOList;
    listOListOList.resize(tempX);
    //std::fill(list.begin(),list.end(), temp.getTemplate(0));
    std::fill(listOList.begin(),listOList.end(), list);
    std::fill(listOListOList.begin(),listOListOList.end(), listOList);
    map=listOListOList;
}

//If out of bounds the object returned with have an id==-1
Object World::getObject(Coordinate position, Coordinate offset = Coordinate(0,0,0)) const
 {
     position += offset;

	 //Wrapping X, Y
	 position.x = (position.x % sizeX);
	 position.y = (position.y % sizeY);
	 //Out of bounds Z
	 if(position.z >= sizeZ || position.z < 0)
	 {
		 return Object();
	 }

     return map[position.x][position.y][position.z];
 }

 Object World::getObject(int posX, int posY, int posZ, int offX=0, int offY=0, int offZ=0) const
 {
	 return getObject(Coordinate(posX, posY, posZ), Coordinate(offX, offY, offZ));
 }

 int World::getSizeX() const
 {
	 return sizeX;
 }

 int World::getSizeY() const
 {
	 return sizeY;
 }

 int World::getSizeZ() const
 {
	 return sizeZ;
 }

 Coordinate World::getSize() const
 {
	 return Coordinate(sizeX, sizeY, sizeZ);
 }