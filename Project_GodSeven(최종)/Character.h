﻿#pragma once

#include <string>
#include <vector>
#include "Item.h"
#include "Monster.h"

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

    // 새로운 멤버 변수 선언
    int monstersDefeated;    // 지금까지 처치한 몬스터 수
    int totalGoldEarned;     // 지금까지 획득한 총 골드
    int totalGoldSpent;      // 지금까지 소모한 총 골드

public:
    Character(const std::string& name);
    std::string getName() const;
    int getLevel() const;
    int getHealth() const;
    int getAttack() const;

    int getMaxHealth() const;  // 최대 체력 반환
    void setHealth(int newHealth);  // 체력 설정
    void setAttack(int newAttack);  // 공격력 설정

    int getExperience() const;
    int getGold() const;
    void displayStatus() const;
    void levelUp();
    void takeDamage(int damage);

    void addExperience(int exp);
    void addGold(int amount);
    bool spendGold(int amount);         // 골드 소모 메서드 추가
    void addMonsterKill();              // 몬스터 처치 기록 메서드 추가

    void addItem(Item* item);
    void useItem(int index);
    void printInventory() const;
    int performRandomAttack(Monster* target); // void에서 int로 변경
    Item* getItem(int index) const;
    Item* removeItem(int index);
};
