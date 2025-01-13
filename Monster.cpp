//Monster.cpp
#include "Monster.h"
#include <cstdlib>  // rand()

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

Goblin::Goblin(int level)
    : Monster("Goblin", level * 20 + rand() % 10, level * 5 + rand() % 5) {
}

Orc::Orc(int level)
    : Monster("Orc", level * 25 + rand() % 10, level * 7 + rand() % 5) {
}

Troll::Troll(int level)
    : Monster("Troll", level * 30 + rand() % 15, level * 10 + rand() % 7) {
}

Slime::Slime(int level)
    : Monster("Slime", level * 15 + rand() % 5, level * 4 + rand() % 3) {
}
