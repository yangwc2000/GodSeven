﻿// Character.cpp
#include "Character.h"
#include <iostream>
#include <random>

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

void Character::recoverHealth(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

void Character::increaseAttack(int amount) {
    attack += amount;
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

void Character::printInventory() const {
    for (int i = 0; i < inventory.size(); ++i) {
        std::cout << i << ": " << inventory[i]->getName() << "\n";
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

