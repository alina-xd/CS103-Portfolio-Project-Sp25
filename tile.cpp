#include "tile.h"
using namespace std;

// constructor
Tile::Tile(){
    unit_=nullptr;
    building_=new Building();
    action_=false;
    team_=Team::NONE;
}

// constructor for capital tile
Tile::Tile(Team t){
    building_=new Building(BuildingType::CAPITAL);
    if(t==Team::KNIGHT){
        unit_=new Warrior(t);
    }
    else if(t==Team::WIZARD){
        unit_=new Warrior(t);
    }
    team_=t;
    action_=true;
}

// destructor
Tile::~Tile(){
    delete unit_;
    delete building_;
}

// sets unit on this tile
void Tile::setUnit(Unit* u){
    unit_= u;
}

void Tile::removeUnit(){
    unit_=nullptr;
}

// sets building on this tile
void Tile::setBuilding(Building* b){
    building_=b;
}

// sets actionable status to false
void Tile::useAction(){
    action_=false;
}

// sets actionable status to true
void Tile::resetAction(){
    action_=true;
}

bool Tile::hasUnit() const{
    return unit_!=nullptr;
}

bool Tile::hasBuilding() const{
    return building_!=nullptr;
}

bool Tile::hasAction() const{
    return action_;
}

bool Tile::isOccupied() const{
    return team_!=Team::NONE;
}

// sets team ownership of this tile
void Tile::setTeam(Team t){
    team_=t;
}

// returns the unit on this tile
Unit* Tile::getUnit() const{
    return unit_;
}

// returns the building on this tile
Building* Tile::getBuilding() const{
    return building_;
}

Team Tile::getTeam() const{
    return team_;
}

// return stringified symbol for the unit on this tile
std::string Tile::getUnitSymbol() const{
    if(unit_==nullptr){
        return "  ";
    }
    else return unit_->getSymbol();
}

// return stringified symbol for the building on this tile
std::string Tile::getBuildingSymbol() const{
    if(building_==nullptr){
        return "  ";
    }
    else return building_->getSymbol();
}

// return "!!" if action available, "  " if not
std::string Tile::getActionSymbol() const{
    if(action_){
        return "!!";
    }
    return "  ";
}

// return symbol of ownership of this tile
std::string Tile::getTeamSymbol() const{
    return TEAM_SYMBOLS[team_];
}
