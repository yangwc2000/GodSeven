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
    virtual int getPrice() const = 0;
};

class HealthPotion : public Item {
private:
    std::string name; // --------------------아이템 이름
    int healthRestore;

public:
    HealthPotion();
    std::string getName() const override;
    void use(Character* character) override;
    int getPrice() const override;
};

class AttackBoost : public Item {
private:
    std::string name; // ----------------------아이템 이름
    int attackIncrease;

public:
    AttackBoost();
    std::string getName() const override;
    void use(Character* character) override;
    int getPrice() const override;
};

// 새로운 환금용 아이템 클래스 추가
class Treasure : public Item {
private:
    std::string treasureName;
    int price;

public:
    Treasure(const std::string& name, int price);
    std::string getName() const override;
    void use(Character* character) override;
    int getPrice() const override;
};

#endif // ITEM_H