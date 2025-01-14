#include "Character.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// 생성자: 체력, 공격력 초기화 및 난수 초기화
Character::Character(int health, int maxHealth, int attack)
    : health(health), maxHealth(maxHealth), attack(attack)
{
    srand(static_cast<unsigned>(time(nullptr))); // 난수 초기화
}

// 소멸자: 인벤토리에 있는 아이템 삭제
Character::~Character()
{
    for (Item* item : inventory)
    {
        delete item;
    }
    inventory.clear();
}

int Character::getHealth() const
{
    return health;
}

int Character::getMaxHealth() const
{
    return maxHealth;
}

int Character::getAttack() const
{
    return attack;
}

void Character::setHealth(int newHealth)
{
    health = newHealth;
}

void Character::setAttack(int newAttack)
{
    attack = newAttack;
}

void Character::addItem(Item* item)
{
    inventory.push_back(item); // 인벤토리에 아이템 추가
    std::cout << item->getName() << "이(가) 인벤토리에 추가되었습니다!" << std::endl;
}

void Character::useRandomItem()
{
    if (!inventory.empty() && (rand() % 100) < 30) // 30% 확률로 실행
    {
        int randomIndex = rand() % inventory.size(); // 랜덤 인덱스 선택
        std::cout << "인벤토리를 열어봅니다." << std::endl; // 아이템 사용 전 출력
        inventory[randomIndex]->use(this); // 선택된 아이템 사용

        // 사용 후 아이템 제거
        delete inventory[randomIndex];
        inventory.erase(inventory.begin() + randomIndex);
    }
}

void Character::showInventory() const
{
    std::cout << "===== 인벤토리 목록 =====\n";
    for (size_t i = 0; i < inventory.size(); ++i)
    {
        std::cout << i << ": " << inventory[i]->getName() << "\n";
    }
    if (inventory.empty())
    {
        std::cout << "(텅 비었습니다...)\n";
    }
}
