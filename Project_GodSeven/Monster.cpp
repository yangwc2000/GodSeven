// Monster.cpp
#include "Monster.h"
#include <cstdlib>  // rand()
#include <vector>

Monster::Monster(const std::string& name, int health, int attack)
    : name(name), health(health), attack(attack) {
}

std::string Monster::getName() const {
    return name;
}

int Monster::getHealth() const {
    return health;
}

int Monster::getAttack() const {
    return attack;
}

void Monster::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

// Goblin 클래스의 정의
Goblin::Goblin(int level)
    : Monster("Goblin", (level * 20 + rand() % 10) * 5, (level * 5 + rand() % 5) * 3) {
    if (level < 3) level = 3;
    if (level > 5) level = 5;
}

Item* Goblin::dropItem() const {
    return new Treasure("고블린 금화", 20);
}

// Orc 클래스의 정의
Orc::Orc(int level)
    : Monster("Orc", (level * 25 + rand() % 10) * 5, (level * 7 + rand() % 5) * 3) {
    if (level < 5) level = 5;
    if (level > 7) level = 7;
}

Item* Orc::dropItem() const {
    return new Treasure("오크의 어금니", 30);
}

// Troll 클래스의 정의
Troll::Troll(int level)
    : Monster("Troll", (level * 30 + rand() % 15) * 5, (level * 10 + rand() % 7) * 3) {
    if (level < 7) level = 7;
    if (level > 9) level = 9;
}

Item* Troll::dropItem() const {
    return new Treasure("트롤의 뼈", 40);
}

// Slime 클래스의 정의
Slime::Slime(int level)
    : Monster("Slime", (level * 15 + rand() % 5) * 5, (level * 4 + rand() % 3) * 3) {
    if (level < 1) level = 1;
    if (level > 3) level = 3;
}

Item* Slime::dropItem() const {
    return new Treasure("슬라임의 부서진 핵", 10);
}

std::vector<Monster*> encounterMonsters(int playerLevel) {
    std::vector<Monster*> monsters;
    if (playerLevel >= 1 && playerLevel <= 3) {
        monsters.push_back(new Slime(playerLevel));
    }
    if (playerLevel >= 3 && playerLevel <= 5) {
        monsters.push_back(new Goblin(playerLevel));
    }
    if (playerLevel >= 5 && playerLevel <= 7) {
        monsters.push_back(new Orc(playerLevel));
    }
    if (playerLevel >= 7 && playerLevel <= 9) {
        monsters.push_back(new Troll(playerLevel));
    }
    return monsters;
}
