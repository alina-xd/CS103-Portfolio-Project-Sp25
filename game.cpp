#include "game.h"
#include <iostream>
#include <string>
using namespace std;

// constructor
Game::Game(){
    turn_=0;
    points_[1]=0;
    points_[2]=0;
}

// destructor
Game::~Game(){
    
}

// gameflow functions
// move to next turn
void Game::nextTurn(){
    turn_++; // increment turn number
    Team player;
    if(turn_%2==1) player=Team::KNIGHT;
    else player=Team::WIZARD;
    int newPoints=board_.calcPoints(player); // points gained
    addPoints(player,newPoints); // add points gained to player's account
    board_.resetActions(player);
    bool flag=true;
    while(flag){
        flag=makeMove(player);// take player actions
    } 
}

// prompts user to make the next move
bool Game::makeMove(Team t){
    board_.printBoard(); // print the current board
    // print instructions
    cout<<"It's "<<TEAM_SYMBOLS[t]<<TEAM_NAMES[t]<<"'s turn!"<<endl;
    cout<<"Points left: "<<points_[t]<<endl;
    cout<<endl;
    cout<<"Choose an action:"<<endl;
    cout<<" 1. Move UNIT"<<endl;
    cout<<" 2. Attack Enemy UNIT"<<endl;
    cout<<" 3. Spawn UNIT"<<endl;
    cout<<" 4. Build/Upgrade BUILDING"<<endl;
    cout<<" 5. End Turn"<<endl;
    // ask for player input
    int action=-1;
    cout<<endl;
    cout<<"Enter the number of your action: ";
    cin>>action;
    while(action<1||action>5){
        cout<<"Please enter a valid action: ";
        cin>>action;
    }
    if(action==1){ // move unit
        int x1,y1,x2,y2;
        cout<<"Enter current position of unit (x y): ";
        cin>>x1>>y1;
        cout<<"Enter destination position (x y): ";
        cin>>x2>>y2;
        bool flag=board_.moveUnit(x1,y1,x2,y2);
        if(flag==false){
            cout<<"Failed. Please check your command."<<endl;
            return true;
        }
        cout<<"Success!"<<endl;
        return true;
    }
    else if(action==2){ // attack enemy
        int x1,y1,x2,y2;
        cout<<"Enter attacker’s position (x y): ";
        cin>>x1>>y1;
        cout<<"Enter enemy’s position to attack (x y): ",
        cin>>x2>>y2;
        bool flag=board_.attackUnit(x1,y1,x2,y2);
        if(flag==false){
            cout<<"Failed. Please check your command."<<endl;
            return true;
        }
        cout<<"Success!"<<endl;
        return true;
    }
    else if(action==3){ // spawn unit
        int choice;
        cout<<"UNITs can only be spawn at your CAPITAL."<<endl;
        cout<<"Choose unit type to spawn: "<<endl;
        cout<<" 1. WARRIOR"<<UNIT_SYMBOLS[t][0]<<" (5 pts)"<<endl;
        cout<<" 2. RIDER"<<UNIT_SYMBOLS[t][1]<<" (8 pts)"<<endl;
        cout<<" 3. SHOOTER"<<UNIT_SYMBOLS[t][2]<<" (8 pts)"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        while(choice<1||choice>3){
            cout<<"Please enter a valid choice: ";
            cin>>choice;
        }
        if(points_[t]<UNIT_COSTS[choice]){
            cout<<"You don't have enough points."<<endl;
            return true;
        }
        UnitType utype;
        if(choice==1){
            utype=UnitType::WARRIOR;
        }
        else if(choice==2){
            utype=UnitType::RIDER;
        }
        else if(choice==3){
            utype=UnitType::SHOOTER;
        }
        if(board_.spawnUnit(t,utype)){
            cout<<"Success!"<<endl;
            points_[t]-=UNIT_COSTS[choice];
        }
        else{
            cout<<"Failed. Please check your command."<<endl;
            return false;
        }
        return true;
    }
    else if(action==4){ // build/upgrade
        cout<<"All build/upgrade cost 3pts."<<endl;
        if(points_[t]<3){
            cout<<"You don't have enough points."<<endl;
            return true;
        }
        int x,y;
        cout<<"Enter the tile you want to build/upgrade on (x y): ";
        cin>>x>>y;
        bool flag=board_.upgradeBuilding(x,y);
        if(flag==false){
            cout<<"Failed. Please check your command."<<endl;
            return true;
        }
        points_[t]-=3;
        cout<<"Success!"<<endl;
        return true;
    }
    else{ // end turn
        return false;
    }
}

// add points to a player's account
void Game::addPoints(Team t,int amount){
    points_[t]+=amount;
}

// deduct points from a player's account
void Game::minusPoints(Team t,int amount){
    points_[t]-=amount;
}

// checks if either player wins
bool Game::haveWinner() const{
    Team winner=board_.checkWin();
    if(winner==Team::NONE){
        return false;
    }
    cout<<endl;
    cout<<"All glory to the "<<TEAM_SYMBOLS[winner]<<TEAM_NAMES[winner]<<"s!"<<endl;
    cout<<endl;
    cout<<"They conquered their enemy's CAPITAL in "<<turn_<<" turns."<<endl;
    cout<<"History will remember this day,"<<endl;
    cout<<"and their name shall be sung for generations to come."<<endl;
    cout<<endl;
    cout<<"Thank you for playing!"<<endl;
    return true;
} 

// prints 
void Game::printIntro() const{
    cout<<"╔═════════════════════════════════════════════╗"<<endl;
    cout<<"║  Knights vs Wizards: Battle for the Throne  ║"<<endl;
    cout<<"╚═════════════════════════════════════════════╝"<<endl;
    cout<<"Welcome, commanders!"<<endl;
    cout<<endl;
    cout<<"Two rival forces — the valiant KNIGHTS and the cunning WIZARDS"<<endl;
    cout<<"wage war against each other to seize control of the kingdom."<<endl;
    cout<<endl;
    cout<<"Take commands of your UNITs:"<<endl;
    cout<<" 🪖🔮WARRIORs - close-range and hardy"<<endl;
    cout<<" 🐎🦄RIDERs - swift and agile"<<endl;
    cout<<" 🏹🪄SHOOTERs - long-distance and deadly"<<endl;
    cout<<endl;
    cout<<"Construct and upgrade BUILDINGs:"<<endl;
    cout<<" 🛖VILLAGE -> 🏠TOWN -> 🏢CITY"<<endl;
    cout<<endl;
    cout<<"- Each side begins with a 🏰CAPITAL and a WARRIOR."<<endl;
    cout<<"- UNITs can move, attack, or build only once per turn."<<endl;
    cout<<"- Earn points each turn based on your BUILDINGs."<<endl;
    cout<<"- Spend points to train new UNITs / build or upgrade BUILDINGs."<<endl;
    cout<<"- Your objective: Conquer the enemy's CAPITAL."<<endl;
    cout<<endl;
    cout<<"Press [enter] to begin the battle..."<<endl;
    string dummy;
    getline(cin,dummy);
}

