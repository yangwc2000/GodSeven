// Item.cpp
#include "Item.h"
#include "Character.h"

// HealthPotion 클래스의 정의
HealthPotion::HealthPotion() : healthRestore(50) {}

std::string HealthPotion::getName() const {
    return "체력 포션";
}

void HealthPotion::use(Character* character) {
    character->recoverHealth(healthRestore);
}

int HealthPotion::getPrice() const {
    return 50;
}

// AttackBoost 클래스의 정의
AttackBoost::AttackBoost() : attackIncrease(10) {}

std::string AttackBoost::getName() const {
    return "영고항력의 신단";
}

void AttackBoost::use(Character* character) {
    character->increaseAttack(attackIncrease);
}

int AttackBoost::getPrice() const {
    return 70;
}

// Treasure 클래스의 정의
Treasure::Treasure(const std::string& name, int price) : treasureName(name), price(price) {}

std::string Treasure::getName() const {
    return treasureName;
}

void Treasure::use(Character* character) {
    // 환금용 아이템은 사용되지 않음
}

int Treasure::getPrice() const {
    return price;
}
