#ifndef Object_h
#define Object_h
#include <string>
#include <vector>
#include <mutex>

using namespace std;

//the base Object
//once set, cannot be changed
//thread safe
class TemplateObject
{
public:
    TemplateObject(std::string,int,int,int,bool,bool);
    std::string getName() const;
    int getHp() const;
    int getStrength() const;
    int getWeight() const;
    bool getIsFlamable() const;
    bool getIsWetable() const;
private:
    int baseHp, strength, weight;
    bool isFlamable, isWetable;
    std::string name;
};
//Singleton pattern
//thread safe
class TemplateObjectList
{
public:
	//Must be modifiable, so we need to get the instance by pointer
	static TemplateObjectList* getInstance();
    int addTemplate(TemplateObject);
    const TemplateObject getTemplate(int) const;
    int findTemplate(std::string) const;
    int getSize() const;
private:
	TemplateObjectList();
	static std::mutex creationLock;
	static TemplateObjectList * pInstance;
    std::vector<TemplateObject> list;
};
//Object used in world
//modifiable
//id refers to template location in the template list
//not thread safe
class Object
{
public:
	Object();
    Object(int,int,int,int,bool,bool);
    Object(int);
    int getId() const;
    int getHp() const;
    int getStrength() const;
    int getWeight() const;
    bool getStateFire() const;
    bool getStateWet() const;
	//Accessor functions that get properties of the template
	bool getFlamable() const;
	bool getWetable() const;
   
    void setHp(int);
    void setStrength(int);
    void setWeight(int);
    void setStateFire(bool);
    void setStateWet(bool);

private:
    int id,hp,strength,weight;
    bool stateFire, stateWet;
};





#endif