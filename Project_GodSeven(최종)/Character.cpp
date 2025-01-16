#include "Character.h"
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include "Boss.h"

Character::Character(const std::string& name)
    : name(name), level(1), health(200), maxHealth(200), attack(30), experience(0), gold(0),
    monstersDefeated(0), totalGoldEarned(0), totalGoldSpent(0) {
}

std::string Character::getName() const {
    return name;
}

int Character::getLevel() const {
    return level;
}

int Character::getHealth() const {
    return health;
}

int Character::getAttack() const {
    return attack;
}

int Character::getMaxHealth() const {
    return maxHealth;
}

void Character::setHealth(int newHealth) {
    health = newHealth;
}

void Character::setAttack(int newAttack) {
    attack = newAttack;
}

int Character::getExperience() const {
    return experience;
}

int Character::getGold() const {
    return gold;
}


void Character::addGold(int amount) {
    gold += amount;
    totalGoldEarned += amount; // 총 획득한 골드 증가
}

bool Character::spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;           // 현재 골드 감소
        totalGoldSpent += amount; // 총 소모한 골드 증가
        return true;
    }
    else {
        return false;
    }
   
}


void Character::displayStatus() const {
    std::cout << "======== 현재 상태 ========\n"
        << "이름: " << name << "\n"
        << "레벨: " << level << "\n"
        << "체력: " << health << "/" << maxHealth << "\n"
        << "공격력: " << attack << "\n"
        << "경험치: " << experience << "\n"
        << "현재 골드: " << gold << "\n"
        << "----------------------------\n"
        << "지금까지 처치한 몬스터 수: " << monstersDefeated << "\n"
        << "총 획득한 골드: " << totalGoldEarned << "\n"
        << "총 소모한 골드: " << totalGoldSpent << "\n"
        << "============================\n";
}

void Character::levelUp() {
    level++;
    maxHealth += 20;
    health = maxHealth;
    attack += 5;
    std::cout << "레벨 업! 현재 레벨 " << level << ".\n";
}

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

void Character::addExperience(int exp) {
    experience += exp;
    if (experience >= level * 100) {
        experience -= level * 100;
        levelUp();
    }
}

void Character::addMonsterKill() {
    monstersDefeated++; // 몬스터 처치 수 증가
}

void Character::addItem(Item* item) {
    inventory.push_back(item);
}

void Character::useItem(int index) {
    if (index >= 0 && index < inventory.size()) {
        Item* item = inventory[index];
        if (dynamic_cast<Treasure*>(item) == nullptr) {
            item->use(this);
            delete item;
            inventory.erase(inventory.begin() + index);
        }
        else {
            std::cout << "이 아이템은 사용할 수 없습니다." << std::endl;
        }
    }
    else {
        std::cout << "잘못된 번호입니다." << std::endl;
    }
}

void Character::printInventory() const {
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << i << ": " << inventory[i]->getName() << "\n";
    }
    if (inventory.empty()) {
        std::cout << "(텅 비었습니다...)\n";
    }
}

Item* Character::getItem(int index) const {
    if (index >= 0 && index < inventory.size()) {
        return inventory[index];
    }
    return nullptr;
}

Item* Character::removeItem(int index) {
    if (index >= 0 && index < inventory.size()) {
        Item* item = inventory[index];
        inventory.erase(inventory.begin() + index);
        return item;
    }
    return nullptr;
}

int Character::performRandomAttack(Monster* target) {
    if (!target) return 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.5, 1.5);

    double randomMultiplier = dis(gen);
    int finalAttack = static_cast<int>(attack * randomMultiplier);

    target->takeDamage(finalAttack);

    std::cout << name << "의 공격! (공격력: " << finalAttack << ")";

    if (randomMultiplier > 1.0) { // 크리티컬 여부 확인
        std::cout << "\033[1;31m 크리티컬!\033[0m" << std::endl;
    }
    else {
        std::cout << std::endl;
    }

    return finalAttack;
}
