/*
Game class:
controls gameflow and turns
*/
#ifndef GAME_H
#define GAME_H
#include "board.h"
// #include "player.h"
#include <iostream>
#include <vector>

class Game{
    public:
        Game();
        ~Game();

        // gameflow functions
        void nextTurn(); // move to next turn
        bool haveWinner() const; // checks if either player wins
        void printIntro() const;

    private:
        Board board_; // the board
        int turn_; // current turn
        int points_[5]; // current points the players have

        // helper functions
        void addPoints(Team t,int amount); // add points to a player's account
        void minusPoints(Team t,int amount); // deduct points from a player's account
        bool makeMove(Team t); // player takes move
};
#endif
