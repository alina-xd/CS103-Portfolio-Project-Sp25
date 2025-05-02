#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "tile.h"
#include "unit.h"
#include "building.h"

class Board{
    public: 
         //constructor 
         Board();
         //destructor 
         ~Board();
         //display board with all units/buildings
         void printBoard() const;
        //  //set a unit on a tile on the board
        //  void set_Unit(Unit* unit, int r, int c);
        //  // set a building on a tile on the board
        //  void set_Building(Building* building, int r, int c);
        int calcPoints(Team t) const; // returns the amount of points a player gains
        void resetActions(Team t);

         // actions
         bool attackUnit(int x1,int y1,int x2,int y2);
         bool moveUnit(int x1,int y1,int x2,int y2);
         bool upgradeBuilding(int x,int y);
         bool spawnUnit(Team t,UnitType utype);

         Team checkWin() const; // checks if either player wins

    private:
        //fixed size
        //board is a vector of vector of tiles
        std::vector<std::vector<Tile*>> board_grid_;
        // std::vector<Unit*> units_;
        // std::vector<Building*> buildings_;

        // helper functions
        void removeUnit(int x,int y);
};
#endif
