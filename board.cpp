#include <string>
#include <vector>
#include <iostream>
#include "tile.h"
#include "board.h"
using namespace std;

// constructor
Board::Board(){
    for(int i=0;i<BOARD_LENGTH;i++){
        vector<Tile*> v;
        for(int j=0;j<BOARD_WIDTH;j++){
            Tile* t;
            if(i==0&&j==0){
                t=new Tile(Team::KNIGHT);
                // Building* b=new Building(BuildingType::CAPITAL);
                // Unit* u=new Warrior(Team::KNIGHT);
                // t->setBuilding(b);
                // t->setUnit(u);
                // // units_.push_back(u);
                // // buildings_.push_back(b);
                // t->resetAction();
                // t->setTeam(Team::KNIGHT);
            }
            else if(i==BOARD_LENGTH-1&&j==BOARD_WIDTH-1){
                t=new Tile(Team::WIZARD);
                // Building* b=new Building(BuildingType::CAPITAL);
                // Unit* u=new Warrior(Team::WIZARD);
                // t->setBuilding(b);
                // t->setUnit(u);
                // // units_.push_back(u);
                // // buildings_.push_back(b);
                // t->resetAction();
                // t->setTeam(Team::WIZARD);
            }
            else{
                t=new Tile();
            }
            v.push_back(t);
        }
        board_grid_.push_back(v);
    }
    // cout<<board_grid_.size()<<endl;
    // cout<<board_grid_[0].size()<<endl;
}

// destructor
Board::~Board(){
    for(int i=0; i< BOARD_LENGTH; i++){
        for(int j=0; j< BOARD_WIDTH; j++){
            delete board_grid_[i][j];
        }
    }
}

bool Board::attackUnit(int x1,int y1,int x2,int y2){
    //check out of bounds
    if(x1<0||x1>= BOARD_LENGTH||x2<0||x2>= BOARD_LENGTH){
        cout<<"Index out of bounds."<<endl;
        return false;
    }
    if(y1<0||y1>= BOARD_WIDTH||y2<0||y2>= BOARD_WIDTH){
        cout<<"Index out of bounds."<<endl;
        return false;
    }
    Tile* t1=board_grid_[x1][y1];
    Tile* t2=board_grid_[x2][y2];
    // checks if attacker and target exist
    if(!t1->hasUnit()){
        cout<<"Attacker UNIT does not exist."<<endl;
        return false; 
    }
    if(!t2->hasUnit()){
        cout<<"Target UNIT does not exist."<<endl;
        return false;
    }
    if(!t1->hasAction()){
        cout<<"Attacker UNIT has no actions left."<<endl;
        return false;
    }
    Unit* u1=t1->getUnit();
    Unit* u2=t2->getUnit();
    if(!u1->canAttack(u2)){
        cout<<"Target is too far away."<<endl;
        return false; // checks if attacker can attack target
    }
    // check Rider conditions
    if(u1->getType()==UnitType::RIDER){
        if((x2==x1-2)&&(board_grid_[x1-1][y1]->hasUnit())||
            (x2==x1+2)&&(board_grid_[x1+1][y1]->hasUnit())||
            (y2==y1-2)&&(board_grid_[x1][y1-1]->hasUnit())||
            (y2==y1+2)&&(board_grid_[x1][y1+1]->hasUnit())||
            (x2==x1-1)&&(y2==y1-1)&&(board_grid_[x1][y1-1]->hasUnit())&&(board_grid_[x1-1][y1]->hasUnit())||
            (x2==x1+1)&&(y2==y1-1)&&(board_grid_[x1][y1-1]->hasUnit())&&(board_grid_[x1+1][y1]->hasUnit())||
            (x2==x1-1)&&(y2==y1+1)&&(board_grid_[x1][y1+1]->hasUnit())&&(board_grid_[x1-1][y1]->hasUnit())||
            (x2==x1+1)&&(y2==y1+1)&&(board_grid_[x1][y1+1]->hasUnit())&&(board_grid_[x1+1][y1]->hasUnit())){
            cout<<"RIDER cannot jump over another UNIT."<<endl;
            return false;
        }
    }

    u1->attack(u2); // attack
    if(u1->getType()!=UnitType::SHOOTER){ // Shooter does not move while attacking
        t1->removeUnit(); // remove unit at attacker tile
        t2->setUnit(u1); // place attacker at target tile
        t2->setTeam(u1->getTeam()); // occupy target tile
    }
    else{
        t2->removeUnit();
    }
    t1->useAction();
    t2->useAction();
    return true;
}

bool Board::moveUnit(int x1,int y1,int x2,int y2){
    //check out of bounds
    if(x1<0||x1>= BOARD_LENGTH||x2<0||x2>= BOARD_LENGTH){
        cout<<"Index out of bounds."<<endl;
        return false;
    }
    if(y1<0||y1>= BOARD_WIDTH||y2<0||y2>= BOARD_WIDTH){
        cout<<"Index out of bounds."<<endl;
        return false;
    }
    Tile* t1=board_grid_[x1][y1];
    Tile* t2=board_grid_[x2][y2];
    if(!t1->hasAction()){
        cout<<"This UNIT has no actions left."<<endl;
        return false; // tile not actionable
    }
    if(!t1->hasUnit()){
        cout<<"This tile has no UNIT."<<endl;
        return false; // tile no unit
    }
    if(t2->hasUnit()){
        cout<<"destination tile occupied by another UNIT."<<endl;
        return false; // there's already a unit at destination
    }
    Unit* u=t1->getUnit();
    if(!u->canMove(x2,y2)){
        cout<<"Destination is too far away."<<endl;
        return false; // checks if unit can move to destination
    }
    if(u->getType()==UnitType::RIDER){
        if((x2==x1-2)&&(board_grid_[x1-1][y1]->hasUnit())||
            (x2==x1+2)&&(board_grid_[x1+1][y1]->hasUnit())||
            (y2==y1-2)&&(board_grid_[x1][y1-1]->hasUnit())||
            (y2==y1+2)&&(board_grid_[x1][y1+1]->hasUnit())||
            (x2==x1-1)&&(y2==y1-1)&&(board_grid_[x1][y1-1]->hasUnit())&&(board_grid_[x1-1][y1]->hasUnit())||
            (x2==x1+1)&&(y2==y1-1)&&(board_grid_[x1][y1-1]->hasUnit())&&(board_grid_[x1+1][y1]->hasUnit())||
            (x2==x1-1)&&(y2==y1+1)&&(board_grid_[x1][y1+1]->hasUnit())&&(board_grid_[x1-1][y1]->hasUnit())||
            (x2==x1+1)&&(y2==y1+1)&&(board_grid_[x1][y1+1]->hasUnit())&&(board_grid_[x1+1][y1]->hasUnit())){
            cout<<"RIDER cannot jump over another UNIT."<<endl;
            return false;
        }
    }
    u->move(x2,y2); // move the unit
    t1->removeUnit(); // removes the unit at starting grid
    t2->setUnit(u); // set unit at destination grid
    t2->setTeam(u->getTeam()); // occupy destination grid
    t1->useAction();
    t2->useAction();
    return true;
}

bool Board::upgradeBuilding(int x,int y){
    Tile* t=board_grid_[x][y];
    if(!t->hasBuilding()){
        cout<<"There's no BUILDING on this tile."<<endl;
        return false; // no building at location
    }
    if(!t->hasUnit()){
        cout<<"There's no UNIT on this tile."<<endl;
        return false; // no unit
    }
    if(!t->hasAction()){
        cout<<"This UNIT has no actions left."<<endl;
        return false; // not actionable
    }
    Building* b=t->getBuilding();
    if(!b->canUpgrade()){
        cout<<"This BUILDING cannot be upgraded."<<endl;
        return false; // check if building is upgradable
    }
    b->upgrade();
    t->useAction();

    return true;
}

bool Board::spawnUnit(Team t,UnitType utype){
    int x,y;
    if(t==Team::KNIGHT){
        x=0;
        y=0;
    }
    else if(t==Team::WIZARD){
        x=BOARD_LENGTH-1;
        y=BOARD_WIDTH-1;
    }
    else{
        cout<<"Invalid team."<<endl;
    }
    Tile* temp=board_grid_[x][y];
    if(temp->hasUnit()){
        cout<<"Your CAPITAL is not empty."<<endl;
        return false;
    }
    Unit* u;
    if(utype==UnitType::WARRIOR) u=new Warrior(t);
    else if(utype==UnitType::RIDER) u=new Rider(t);
    else if(utype==UnitType::SHOOTER) u=new Shooter(t);
    temp->setUnit(u);
    return true;
}

// prints the current board
void Board::printBoard() const{
    // cout<<endl;
    cout<<"    ";
    for(int i=0;i<BOARD_WIDTH;i++){
        cout<<i<<"    ";
    }
    cout<<endl;
    for(int i=0;i<BOARD_LENGTH;i++){
        cout<<"  ";
        for(int j=0;j<BOARD_WIDTH;j++){
            cout<<"+----";
        }
        cout<<"+"<<endl;
        cout<<i<<" ";
        for(int j=0;j<BOARD_WIDTH;j++){
            Tile* curTile=board_grid_[i][j];
            cout<<"|";
            cout<<curTile->getUnitSymbol()<<curTile->getActionSymbol();
        }
        cout<<"|"<<endl;
        cout<<"  ";
        for(int j=0;j<BOARD_WIDTH;j++){
            Tile* curTile=board_grid_[i][j];
            cout<<"|"<<curTile->getBuildingSymbol()<<curTile->getTeamSymbol();
        }
        cout<<"|"<<endl;
    }
    cout<<"  ";
    for(int j=0;j<BOARD_WIDTH;j++){
        cout<<"+----";
    }
    cout<<"+"<<endl;
}

int Board::calcPoints(Team t) const{
    int res=0;
    for(int i=0;i<BOARD_LENGTH;i++){
        for(int j=0;j<BOARD_WIDTH;j++){
            Tile* temp=board_grid_[i][j];
            if(temp->getTeam()==t){
                res+=temp->getBuilding()->getPoints();
            }
        }
    }
    return res;
}

void Board::resetActions(Team t){
    for(int i=0;i<BOARD_LENGTH;i++){
        for(int j=0;j<BOARD_WIDTH;j++){
            Tile* curTile=board_grid_[i][j];
            if(curTile->hasUnit()&&curTile->getTeam()==t){
                curTile->resetAction();
            }
            else{
                curTile->useAction();
            }
        }
    }
}

Team Board::checkWin() const{
    if(board_grid_[0][0]->getTeam()==Team::WIZARD){
        return Team::WIZARD;
    }
    else if(board_grid_[BOARD_LENGTH-1][BOARD_WIDTH-1]->getTeam()==Team::KNIGHT){
        return Team::KNIGHT;
    }
    return Team::NONE;
}
