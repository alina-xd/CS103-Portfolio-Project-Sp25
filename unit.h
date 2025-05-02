#ifndef UNIT_H
#define UNIT_H
#include "asset.h"

/*
abstract base class for all units
*/
class Unit: public Asset{
    protected:
        UnitType type_;
        Team team_;
        int move_range_;
        int attack_range_;
        // bool attack_;
        // bool occupy_;
        

    public: 
        Unit();
        Unit(Team t);
        
        // getters
        UnitType getType() const;
        std::string getSymbol() const;
        Team getTeam() const;

        // check action conditions
        bool canMove(int x, int y) const;
        bool canAttack(Unit* other);

        // actions
        virtual void attack(Unit* other);
        virtual void move(int x,int y);
};

/*
Warrior class
inherits from Unit
*/
class Warrior: public Unit{
    public:
        // default ctor dtor
        Warrior();
        Warrior(Team t);
        ~Warrior();

    private:
};

/*
Rider class
inherits from Unit
*/
class Rider: public Unit{
    public:
        // default ctor
        Rider();
        Rider(Team t);
        ~Rider();

        // bool canMove(int x,int y) const;
        // void move(int x,int y);
    private:
};

/*
Shooter class
inherits from Unit
*/
class Shooter: public Unit{
    public:
        // default ctor
        Shooter();
        Shooter(Team t);
        ~Shooter();

        void attack(Unit* other);
    private:
};
#endif
