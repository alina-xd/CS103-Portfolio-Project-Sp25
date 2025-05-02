#ifndef BUILDING_H
#define BUILDING_H
#include "asset.h"

class Building: public Asset{

    protected: 
        BuildingType type_;
        
    public:
        // constructors
        Building();
        Building(BuildingType t);
        ~Building();

        //can you upgrade the building or is it a capital
        bool canUpgrade();
        //upgrade the building 
        bool upgrade();
        // //build a new building on a tile
        // void build(Tile* place, Building t);
        // //can a building be constructed or is the tile/land owned?
        // bool isOwned(Tile* place);

        std::string getSymbol() const;
        int getPoints() const;
};
#endif


