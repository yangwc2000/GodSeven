#include "Item.h"
#include "Character.h"

// HealthPotion 구현
HealthPotion::HealthPotion() : name("회복 포션"), healthRestore(50) {}

std::string HealthPotion::getName() const
{
    return name; // 아이템 이름 반환
}

void HealthPotion::use(Character* character)
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

// AttackBoost 구현
AttackBoost::AttackBoost() : name("공격력증가 쿠키"), attackBoost(10) {}

std::string AttackBoost::getName() const
{
    return name; // 아이템 이름 반환
}

void AttackBoost::use(Character* character)
{
    if (character)
    {
        character->setAttack(character->getAttack() + attackBoost); // 공격력 증가
        std::cout << name << "를 먹고 공격력이 " << attackBoost << "만큼 증가했습니다!" << std::endl;
    }
}

void AttackBoost::remove(Character* character)
{
    if (character)
    {
        character->setAttack(character->getAttack() - attackBoost); // 공격력 감소
        std::cout << name << "의 효과가 사라졌습니다. 공격력이 " << attackBoost << "만큼 감소했습니다!" << std::endl;
    }
}
