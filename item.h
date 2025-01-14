#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

// 전방 선언: Character 클래스가 Item 클래스에서 참조되므로 선언만 추가
class Character;

/*
 아이템 클래스
  모든 아이템은 이 클래스를 상속받아 구현
 각 아이템은 이름 반환과 사용 메서드를 반드시 구현
 */
class Item
{
public:
    virtual ~Item() = default; // 소멸자
    virtual std::string getName() const = 0; // 아이템 이름 반환
    virtual void use(Character* character) = 0; // 아이템 사용
};

/*
 체력 회복 아이템 클래스
 캐릭터의 체력을 회복시키는 아이템
 */
class HealthPotion : public Item
{
private:
    std::string name; // 아이템 이름
    int healthRestore; // 회복량

public:
    HealthPotion(); // 생성자
    std::string getName() const override; // 아이템 이름 반환
    void use(Character* character) override; // 아이템 사용
};

/*
 공격력 증가 아이템 클래스
 캐릭터의 공격력을 증가시키는 아이템
 */
class AttackBoost : public Item
{
private:
    std::string name; // 아이템 이름
    int attackBoost; // 공격력 증가량

public:
    AttackBoost(); // 생성자
    std::string getName() const override; // 아이템 이름 반환
    void use(Character* character) override; // 아이템 사용
    void remove(Character* character); // 아이템 효과 제거
};

#endif // ITEM_H
