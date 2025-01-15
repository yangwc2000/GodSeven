// Monster.h
#pragma once

#include <string>
#include "Item.h"

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
    virtual Item* dropItem() const = 0; // 드랍 아이템 메서드 추가

    // 기본 생성자 추가
    Monster() : name(""), health(0), attack(0) {}
};

class Goblin : public Monster {
public:
    Goblin(int level);
    Item* dropItem() const override; // 드랍 아이템 메서드 구현
};

class Orc : public Monster {
public:
    Orc(int level);
    Item* dropItem() const override; // 드랍 아이템 메서드 구현
};

class Troll : public Monster {
public:
    Troll(int level);
    Item* dropItem() const override; // 드랍 아이템 메서드 구현
};

class Slime : public Monster {
public:
    Slime(int level);
    Item* dropItem() const override; // 드랍 아이템 메서드 구현
};
