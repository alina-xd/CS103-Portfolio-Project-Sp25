#include "unit.h"
#include "tile.h"
#include <cmath>
#include "asset.h"

/*
Unit functions
*/

// default constructor
// theoretically shouldn't be called
Unit::Unit(){
    team_ = Team::NONE;
    move_range_=1;
    attack_range_=1;
    // attack_=false;
    // occupy_ =false;
}

// constructor with team assigned
Unit::Unit(Team t):
Unit()
{
    team_= t;
    if(t==Team::KNIGHT){
        setX(0);
        setY(0);
    }
    else if(t==Team::WIZARD){
        setX(BOARD_LENGTH-1);
        setY(BOARD_WIDTH-1);
    }
}

UnitType Unit::getType() const{
    return type_;
}

// return stringified symbol of this unit
std::string Unit::getSymbol() const{
    return UNIT_SYMBOLS[team_][type_];
}

// return the team this unit belongs to
Team Unit::getTeam() const{
    return team_;
}
/*check actions */
bool Unit::canMove(int x, int y) const{
//check if tile is empty
    // if(isOccupied()){
    //     return false;
    // }
    //get the distance between where unit is now and where it wants to move
    int space_x = abs(x - getX());
    int space_y = abs(y - getY()); 
    int total_move = space_x + space_y;
//check if the total distance to move is allowed based on the type of unit
    if(total_move > move_range_||total_move<=0){
        return false;
    }
    return true;
}

bool Unit::canAttack(Unit* other){
    // get the distance between where unit is now and where it wants to move
    int space_x = abs(other->getX() - getX());
    int space_y = abs(other->getY() - getY()); 
    int total_dist = space_x + space_y;
    // check if the total distance to move is allowed based on the type of unit
    if(total_dist > attack_range_){
        return false;
    }
    return true;
}

void Unit::attack(Unit* other){
    int newX=other->getX();
    int newY=other->getY();
    move(newX,newY);
}

void Unit::move(int x,int y){
    setX(x);
    setY(y);
}

/*
Warrior functions
*/

// default constructor
Warrior::Warrior(){
    type_=UnitType::WARRIOR;
}

// constructor with team assigned
Warrior::Warrior(Team t):
Unit(t)
{
    type_=UnitType::WARRIOR;
}

/*
Rider functions
*/

// default constructor
Rider::Rider():
Unit()
{
    type_=UnitType::RIDER;
    move_range_=2;
    attack_range_=2;
}

Rider::Rider(Team t):
Unit(t)
{
    type_=UnitType::RIDER;
    move_range_=2;
    attack_range_=2;
}

/*
Shooter functions
*/

// default constructor
Shooter::Shooter(){
    type_=UnitType::SHOOTER;
    attack_range_=2;
}

Shooter::Shooter(Team t):
Unit(t)
{
    type_=UnitType::SHOOTER;
    attack_range_=2;
}

void Shooter::attack(Unit* other){
    
}
