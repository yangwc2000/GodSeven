//item.cpp
#include "Item.h"
#include "Character.h"
#include <iostream>

HealthPotion::HealthPotion() : healthRestore(50) {}

std::string HealthPotion::getName() const {
    return "Health Potion";
}

void HealthPotion::use(Character* character) {
    if (character) {
        std::cout << getName() << " 을(를) 사용합니다!\n";
        // 실제로 체력 회복 로직을 호출
        character->recoverHealth(healthRestore);
    }
}

AttackBoost::AttackBoost() : attackIncrease(10) {}

std::string AttackBoost::getName() const {
    return "Attack Boost";
}

void AttackBoost::use(Character* character) {
    if (character) {
        std::cout << getName() << " 을(를) 사용합니다!\n";
        // 실제로 공격력 증가 로직을 호출
        character->increaseAttack(attackIncrease);
    }
}
