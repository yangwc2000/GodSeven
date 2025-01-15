// Monster.cpp
#include "Monster.h"
#include <cstdlib>  // rand()
#include <vector>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

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

// Goblin 클래스
Goblin::Goblin(int level) {
    // 레벨 범위 검사 및 조정 (생성자 시작 부분)
    if (level < 3) level = 3;
    if (level > 5) level = 5;

    std::uniform_int_distribution<> healthDist(0, 9); // 0~9 난수 생성
    std::uniform_int_distribution<> attackDist(0, 4); // 0~4 난수 생성

    health = (level * 17 + healthDist(gen)) * 2;
    attack = (level * 3 + attackDist(gen)) * 2;
    name = "Goblin";
}

Item* Goblin::dropItem() const {
    return new Treasure("고블린 금화", 20);
}

// Orc 클래스 (동일한 방식으로 수정)
Orc::Orc(int level) {
    if (level < 5) level = 5;
    if (level > 7) level = 7;

    std::uniform_int_distribution<> healthDist(0, 9);
    std::uniform_int_distribution<> attackDist(0, 4);

    health = (level * 20 + healthDist(gen)) * 2;
    attack = (level * 5 + attackDist(gen)) * 2;
    name = "Orc";
}

Item* Orc::dropItem() const {
    return new Treasure("오크의 어금니", 30);
}

// Troll 클래스 (동일한 방식으로 수정)
Troll::Troll(int level) {
    if (level < 7) level = 7;
    if (level > 9) level = 9;

    std::uniform_int_distribution<> healthDist(0, 14);
    std::uniform_int_distribution<> attackDist(0, 6);

    health = (level * 25 + healthDist(gen)) * 3;
    attack = (level * 7 + attackDist(gen)); // *1은 생략
    name = "Troll";
}

Item* Troll::dropItem() const {
    return new Treasure("트롤의 뼈", 40);
}

// Slime 클래스 (동일한 방식으로 수정)
Slime::Slime(int level) {
    if (level < 1) level = 1;
    if (level > 3) level = 3;

    std::uniform_int_distribution<> healthDist(0, 4);
    std::uniform_int_distribution<> attackDist(0, 2);

    health = (level * 12 + healthDist(gen)) * 2;
    attack = (level * 3 + attackDist(gen)) * 2;
    name = "Slime";
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

Monster* createMonsterByHabitat(int habitat, int playerLevel) {
    switch (habitat) {
    case 0: // 숲 (슬라임)
        return new Slime(playerLevel);
    case 1: // 동굴 (고블린)
        return new Goblin(playerLevel);
    case 2: // 늪지대 (오크)
        return new Orc(playerLevel);
    case 3: // 산 (트롤)
        return new Troll(playerLevel);
    default:
        return nullptr; // 잘못된 서식지 ID
    }
}