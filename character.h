#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <string>
#include "Item.h"


 /*캐릭터 클래스
 * 
 아이템 인벤토리*/
 
class Character
{
private:
    int health; // 현재 체력
    int maxHealth; // 최대 체력
    int attack; // 공격력
    std::vector<Item*> inventory; // 인벤토리 (보유 중인 아이템 목록)

public:
    Character(int health, int maxHealth, int attack); // 생성자
    ~Character(); // 소멸자

    int getHealth() const; // 현재 체력 반환
    int getMaxHealth() const; // 최대 체력 반환
    int getAttack() const; // 현재 공격력 반환

    void setHealth(int newHealth); // 체력 설정
    void setAttack(int newAttack); // 공격력 설정

    void addItem(Item* item); // 아이템 추가
    void useRandomItem(); // 인벤토리의 아이템을 확률적으로 사용
    void showInventory() const; // 현재 인벤토리 출력
};

#endif // CHARACTER_H
