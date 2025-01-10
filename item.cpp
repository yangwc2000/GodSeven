#include <string>
#include <vector>
using namespace std;

class Character; // 아이템이 속하는 클래스 이름이 Character라고 생각하고 일단 생성


// 아이템 클래스
class Item
{
public:
    virtual ~Item() = default; // 아이템 객체가 삭제될 때 호출
    virtual string getName() const = 0; // 아이템의 이름을 반환하는 함수
    virtual void use(Character* character) = 0; // 아이템을 사용하는 함수
};


// 아이템 클래스에 속하는 체력 회복 아이템
class HealthPotion : public Item
{
private:
    string name; // 아이템의 이름
    int healthRestore; // 체력 회복량

public:
    // 생성자: 이름을 "회복 포션"으로 설정하고, 체력 회복량을 50으로 설정
    HealthPotion() : name("회복 포션"), healthRestore(50) {}

    // getName 함수: 아이템의 이름을 반환
    string getName() const override
    {
        return name;
    }

    // use 함수: 캐릭터에게 아이템을 사용하여 체력을 회복시킴
    void use(Character* character) override
    {
        // character가 nullptr이 아닌 경우 체력을 회복
        if (character)
        {
            character->restoreHealth(healthRestore);
        }
        // 아이템 사용 후 삭제 (아직 전투 구현이 어떻게 될지 몰라서 미적용처리 했습니다.)
        //delete this;
    }
};


// 아이템 클래스에 속하는 공격력 증가 아이템
class AttackBoost : public Item
{
private:
    string name; // 아이템의 이름
    int attackBoost; // 공격력 증가량

public:
    // 이름을 "공격력증가 포션"으로 설정하고, 공격력 증가량을 10으로 설정
    AttackBoost() : name("공격력증가 포션"), attackBoost(10) {}    // 아이템 이름은 추후 컨셉에 맞게 수정 가능합니다.

    // getName 함수: 아이템의 이름을 반환
    string getName() const override
    {
        return name;
    }

    // use 함수: 캐릭터에게 아이템을 사용하여 공격력을 증가시킴
    void use(Character* character) override
    {
        // character가 nullptr이 아닌 경우 공격력을 증가
        if (character)
        {
            character->boostAttack(attackBoost);
        }
        // 아이템 사용 후 삭제 (아직 전투 구현이 어떻게 될지 몰라서 미적용처리 했습니다.)
        //delete this;
    }
};
