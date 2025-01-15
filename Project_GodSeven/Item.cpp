// Item.cpp
#include "Item.h"
#include "Character.h"
#include <iostream>

// HealthPotion 클래스의 정의
HealthPotion::HealthPotion() : name("체력 회복 포션"), healthRestore(50) {}

std::string HealthPotion::getName() const
{
    return name; // 아이템 이름 반환
}

void HealthPotion::use(Character* character) //--------------------------------- 수정
{
    if (character)
    {
        int newHealth = character->getHealth() + healthRestore; // 체력 회복량 계산
        if (newHealth > character->getMaxHealth())
        {
            newHealth = character->getMaxHealth(); // 최대 체력을 초과하지 않음
        }
        character->setHealth(newHealth); // 회복된 체력 설정
        std::cout << name << "을 마시고 체력이 " << healthRestore << "만큼 회복되었습니다!" << std::endl;
    }
}

int HealthPotion::getPrice() const {
    return 50;
}

// AttackBoost 클래스의 정의
AttackBoost::AttackBoost() : name("영고항력의 신단(공격력증가)"), attackIncrease(10) {}

std::string AttackBoost::getName() const {
    return name; // 아이템 이름 반환
}

void AttackBoost::use(Character* character)//--------------------------------- 수정
{
    if (character)
    {
        character->setAttack(character->getAttack() + attackIncrease); // 공격력 증가
        std::cout << name << "을 먹고 공격력이 " << attackIncrease << "만큼 증가했습니다!" << std::endl;
    }
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