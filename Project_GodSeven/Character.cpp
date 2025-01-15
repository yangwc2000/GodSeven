// Character.cpp
#include "Character.h"
#include <iostream>
#include <random>
#include "Boss.h"

Character::Character(const std::string& name)
    : name(name), level(1), health(200), maxHealth(200), attack(30), experience(0), gold(0) {
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

// ----------------------------------------------- 추가
int Character::getMaxHealth() const
{
    return maxHealth;
}

void Character::setHealth(int newHealth)
{
    health = newHealth;
}

void Character::setAttack(int newAttack)
{
    attack = newAttack;
}
//------------------------------------------------


int Character::getExperience() const {
    return experience;
}

int Character::getGold() const {
    return gold;
}

void Character::displayStatus() const {
    std::cout << "이름: " << name << "\n"
        << "레벨: " << level << "\n"
        << "체력: " << health << "/" << maxHealth << "\n"
        << "공격력: " << attack << "\n"
        << "경험치: " << experience << "\n"
        << "골드: " << gold << "\n";
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

void Character::addGold(int amount) {
    gold += amount;
}

void Character::addItem(Item* item) {
    inventory.push_back(item);
}

void Character::useItem(int index) {//---------- 몬스터 드롭 아이템 사용시 없어지는 문제점 수정
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

void Character::printInventory() const//-------------------------------- 빈 문구 추가
{
    for (size_t i = 0; i < inventory.size(); ++i)
    {
        std::cout << i << ": " << inventory[i]->getName() << "\n";
    }
    if (inventory.empty())
    {
        std::cout << "(텅 비었습니다...)\n";
    }
}//----------------------------------------------------------------------

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
    if (!target) return 0; // 타겟이 없을 경우 0 반환

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.5, 1.5);

    double randomMultiplier = dis(gen);
    int finalAttack = static_cast<int>(attack * randomMultiplier);

    target->takeDamage(finalAttack);
    std::cout << name << "의 공격! (공격력: " << finalAttack << ")" << std::endl; // 공격 시 출력은 그대로 유지
    return finalAttack; // 계산된 공격력 반환
}