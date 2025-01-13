// Item.h
#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <string>

class Character; // 전방 선언 (forward declaration)

class Item {
public:
    virtual ~Item() {}
    virtual std::string getName() const = 0;
    virtual void use(Character* character) = 0;
};

class HealthPotion : public Item {
private:
    int healthRestore;

public:
    HealthPotion();
    std::string getName() const override;
    void use(Character* character) override;
};

class AttackBoost : public Item {
private:
    int attackIncrease;

public:
    AttackBoost();
    std::string getName() const override;
    void use(Character* character) override;
};

#endif // ITEM_H
