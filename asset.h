#ifndef ASSET_H
#define ASSET_H
#include <string>

const int BOARD_LENGTH= 4;
const int BOARD_WIDTH= 4;

/*
enum of team
*/
enum Team{
    NONE=0,KNIGHT,WIZARD
};
enum UnitType{
    WARRIOR=0, RIDER, SHOOTER
};
enum BuildingType{
    EMPTY=0,VILLAGE, TOWN, CITY, CAPITAL
};

// team names
const std::string TEAM_NAMES[5]={"","KNIGHT","WIZARD"};

// unit costs
const int UNIT_COSTS[5]={-1,5,8,8};

// symbols for Team
// NONE, KNIGHT, WIZARD
const std::string TEAM_SYMBOLS[5]={"  ","🟥","🟦"};

// symbols for Unit
// row: Team
// column Unit type
const std::string UNIT_SYMBOLS[5][5]={
    {"  ","  ","  "},
    {"🪖","🐎","🏹"},
    {"🔮","🦄","🪄"}
};
const std::string BUILDING_SYMBOLS[10]={"  ","🛖","🏠","🏢","🏰"};

/*
abstract base class for anything owned by a Team
children: Unit, Building
*/
class Asset{
    public:
    // getters
    int getX() const; // return x position
    int getY() const; // return y position

    // setters
    void setX(int x);
    void setY(int y);

    private:
    int x_;
    int y_;
};
#endif

