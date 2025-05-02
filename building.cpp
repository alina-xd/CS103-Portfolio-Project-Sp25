#include "building.h"
using namespace std;

// default constructor
Building::Building(){
    type_ = EMPTY;
}

// destructor
Building::~Building(){
}

// constructor with type
Building::Building(BuildingType t){
    type_= t;
}

// return stringified symbol of this building
std::string Building::getSymbol() const{
    return BUILDING_SYMBOLS[type_];
}

//can you upgrade the building or is it a capital
bool Building::canUpgrade(){
    if(type_ != BuildingType::CAPITAL&&type_!=BuildingType::CITY){ // isn't already highest level possible
        return true;
    }
    return false;
}
//upgrade the building 
bool Building::upgrade(){
    if(canUpgrade()){ //upgrade 
        if(type_ == BuildingType::VILLAGE){
            type_ = BuildingType::TOWN;
        }
        else if(type_==BuildingType::TOWN){
            type_ = BuildingType::CITY;
        }
        else if(type_ ==BuildingType::CITY){
            type_ = BuildingType::CAPITAL;
        }
        else if(type_==BuildingType::EMPTY){
            type_=BuildingType::VILLAGE;
        }
        return true;
    }
    return false;
}

int Building::getPoints() const{
    return (int)type_;
}

