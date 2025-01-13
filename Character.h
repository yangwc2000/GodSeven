// Character.h
#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "Item.h"

class Character {
private:
    std::string name;
    int level;
    int health;
    int maxHealth;
    int attack;
    int experience;
    int gold;
    std::vector<Item*> inventory;

public:
    Character(const std::string& name);

    std::string getName() const;

    int getLevel() const { return level; }      // 레벨 참조용
    int getHealth() const;
    int getAttack() const;
    int getExperience() const;
    int getGold() const;

    void displayStatus() const;
    void levelUp();

    // 체력, 공격력 관련 메서드
    void takeDamage(int damage);
    void recoverHealth(int amount);
    void increaseAttack(int amount);

    // 경험치, 골드
    void addExperience(int exp);
    void addGold(int amount);

    // 아이템
    void addItem(Item* item);
    void useItem(int index);

    // 인벤토리 목록 출력
    void printInventory() const;
};

#endif // CHARACTER_H
