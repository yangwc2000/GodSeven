// Character.cpp
#include "Character.h"
#include <iostream>

Character::Character(const std::string& name)
    : name(name), level(1), health(200), maxHealth(200),
    attack(30), experience(0), gold(0)
{
}

std::string Character::getName() const {
    return name;
}

int Character::getHealth() const {
    return health;
}

int Character::getAttack() const {
    return attack;
}

int Character::getExperience() const {
    return experience;
}

int Character::getGold() const {
    return gold;
}

void Character::displayStatus() const {
    std::cout << "이름: " << name
        << ", 레벨: " << level
        << ", 체력: " << health << "/" << maxHealth
        << ", 공격력: " << attack
        << ", 경험치: " << experience
        << ", 골드: " << gold << std::endl;
}

void Character::levelUp() {
    // 경험치가 100 이상이고 레벨이 10 미만일 때 레벨업
    while (experience >= 100 && level < 10) {
        level++;
        experience -= 100;
        maxHealth += level * 20;
        attack += level * 5;
        health = maxHealth;
        std::cout << "레벨 업! 현재 레벨: " << level << std::endl;
    }
}

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

void Character::recoverHealth(int amount) {
    health += amount;
    if (health > maxHealth) {
        health = maxHealth;
    }
    std::cout << "체력을 " << amount << "만큼 회복했습니다. ("
        << health << "/" << maxHealth << ")\n";
}

void Character::increaseAttack(int amount) {
    attack += amount;
    std::cout << "공격력이 " << amount << "만큼 증가했습니다. (현재: "
        << attack << ")\n";
}

void Character::addExperience(int exp) {
    experience += exp;
    // 레벨업 조건이 되면 자동 레벨업
    levelUp();
}

void Character::addGold(int amount) {
    gold += amount;
}

void Character::addItem(Item* item) {
    inventory.push_back(item);
    std::cout << item->getName() << "이(가) 인벤토리에 추가되었습니다.\n";
}

void Character::useItem(int index) {
    if (index >= 0 && index < (int)inventory.size()) {
        inventory[index]->use(this);
        inventory.erase(inventory.begin() + index);
    }
    else {
        std::cout << "잘못된 인덱스입니다.\n";
    }
}

// 인벤토리 목록 출력
void Character::printInventory() const {
    std::cout << "===== 인벤토리 목록 =====\n";
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << i << ": " << inventory[i]->getName() << "\n";
    }
    if (inventory.empty()) {
        std::cout << "(비어 있음)\n";
    }
}
