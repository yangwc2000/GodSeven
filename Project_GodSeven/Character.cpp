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

void Character::useItem(int index) {
    if (index >= 0 && index < inventory.size()) {
        inventory[index]->use(this);
        delete inventory[index];
        inventory.erase(inventory.begin() + index);
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
void Character::performRandomAttack(Monster* target) {
    if (!target) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.5, 1.5);

    double randomMultiplier = dis(gen);
    int finalAttack = static_cast<int>(attack * randomMultiplier);

    target->takeDamage(finalAttack); // target의 takeDamage 함수 호출
    std::cout << name << "의 공격! (공격력: " << finalAttack << ")" << std::endl;
}