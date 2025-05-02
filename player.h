#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>

class Item{
public:
    Item():alive(true){

    }
    bool isAlive() const{
        return alive;
    }
    void destroy() {
        alive=false;
    }
private:
    bool alive;
};


class Player {
    //constructor
public:
    Player();

    //accesors
    Player(const std::string& emoji, int startingPoints=0);
    std::string getEmoji() const;
    int getPoints() const;
    //int getLivesleft() const;
    //int getScore() const;
    //std::vector<std::string> getInventory() const;
    const std::vector<Item*>& getItems() const;

    void setEmoji(const std::string& newEmoji);
    //void changeLives(int totalHealth);
    void setPoints(int newPoints);
    void addPoints(int score);
    void removePoints (int score);
    void addItem(Item* item);
    void removeItem(Item* item);
    void clean();

    bool isAlive() const;
    void printStatus() const;

private:
    std::string emoji;
    int points;
    //int LivesLeft;
    //int Score;
    std::vector<Item*> items;
};
#endif
