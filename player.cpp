#include "player.h"
#include <iostream>
using namespace std;

Player::Player():points(0), emoji("None")
{

}

Player::Player(const std::string& emoji, int startingPoints)
    :points(startingPoints), emoji(emoji)
{

}

int Player::getPoints() const{
    return points;
}

std::string Player::getEmoji() const{
    return emoji;
}

const std::vector<Item*>& Player::getItems() const{
    return items;
}

void Player::setPoints(int newPoints){
    points=newPoints;
}

void Player::addPoints(int score){
    points+=score;
}

void Player::removePoints(int score){
    points-=score;
}

void Player::setEmoji(const std::string& newEmoji){
    emoji=newEmoji;
}


void Player::addItem(Item* item){
    items.push_back(item);
}

void Player::removeItem(Item* item){
    for(int i=0;i<items.size();i++){
        if(items[i]==item){
            items.erase(items.begin()+i);
            break;
        }
    }
}

bool Player::isAlive() const{
    return points>0;
}

void Player::printStatus() const{
    cout << "Player: " << emoji << endl;
    cout << "Points: " << points << endl;
    cout << "Items: " << items.size() << endl;

}

void Player::clean(){
    for(int i=0; i<items.size();){
        if(items[i]==NULL || !items[i]->isAlive()){
            items.erase(items.begin()+i);
        }
        else{
            i++;
        }
    }
}


