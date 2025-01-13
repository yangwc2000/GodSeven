//Monster.h
#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Monster {
protected:
    std::string name;
    int health;
    int attack;

public:
    Monster(const std::string& name, int health, int attack);
    virtual ~Monster() {}
    std::string getName() const;
    int getHealth() const;
    int getAttack() const;
    void takeDamage(int damage);
};

class Goblin : public Monster {
public:
    Goblin(int level);
};

class Orc : public Monster {
public:
    Orc(int level);
};

class Troll : public Monster {
public:
    Troll(int level);
};

class Slime : public Monster {
public:
    Slime(int level);
};

#endif // MONSTER_H
