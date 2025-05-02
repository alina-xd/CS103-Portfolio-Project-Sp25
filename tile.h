/*
represents one single tile
*/
#ifndef TILE_H
#define TILE_H
#include "unit.h"
#include "building.h"

class Tile{
    public:
    // default ctor
    Tile();
    // // ctor with params
    Tile(Team t);
    Tile(Team t,int x,int y);
    // destructor
    ~Tile();

    // getters
    Unit* getUnit() const;
    Building* getBuilding() const;
    Team getTeam() const;
    bool hasUnit() const;
    bool hasBuilding() const;
    bool isOccupied() const;
    bool hasAction() const;


    // setters
    void setUnit(Unit* u);
    void setBuilding(Building* b);
    void useAction();
    void resetAction();
    void setTeam(Team t);
    void removeUnit();

    // return stringified attributes
    std::string getUnitSymbol() const;
    std::string getActionSymbol() const; // return "!!" if action available, "  " if not
    std::string getBuildingSymbol() const;
    std::string getTeamSymbol() const;


    private:
    // top-left: Unit (if any)
    Unit* unit_;
    // top-right: Action indicator
    bool action_;
    // lower-left: Building (if any)
    Building* building_;
    // lower-right: Team ownership
    Team team_;
};
#endif
