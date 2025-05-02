#include "game.h"
using namespace std;
int main(){
    // create game object
    // which controls the game flow
    Game game;
    // introduction
    game.printIntro();
    // enter gameplay
    // game goes on until one side wins
    while(!game.haveWinner()){
        // continues to the next turn
        game.nextTurn();
    }
    return 0;
}
