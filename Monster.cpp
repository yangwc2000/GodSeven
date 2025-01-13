#include <iostream>
#include <string>
#include <cstdlib>
// 난수를 생성하는 함수 rand(), srand()를 사용하기 위해 추가


using namespace std;

//Monster 클래스
class Monster
{
protected:
    string name;  // 몬스터 이름
    int level;    // 레벨
    int hp;       // 체력
    int attack;   // 공격력

public:
    Monster(const string& name, int playerLevel) // 몬스터의 이름과 플레이어의 레벨을 입력받음
        : name(name)
    {
        // 플레이어 레벨을 기반으로 몬스터 레벨 설정
        level = rand() % (playerLevel + 1 - (playerLevel - 1) + 1) + (playerLevel - 1); //레벨 범위는 플레이어 레벨 +- 1
        hp = rand() % (level * 30 - level * 20 + 1) + level * 20;       // 체력 범위는 몬스터의 레벨*20 ~ 레벨*30
        attack = rand() % (level * 10 - level * 5 + 1) + level * 5;     // 공격력 범위는 몬스터의 레벨*5 ~ 레벨*10
    }

    // 위에서 결정된 몬스터의 정보(스탯)를 출력
    virtual void printInfo() const
    {
        cout << "몬스터(이름: " << name
            << ", 레벨: " << level
            << ", HP: " << hp
            << ", 공격력: " << attack
            << ")" << endl;
    }

    virtual ~Monster() = default;
};

// Slime 클래스 (Monster의 상속 클래스)
class Slime : public Monster
{
public:
    Slime(int playerLevel) : Monster("슬라임", playerLevel) {}

    void printInfo() const override
    {
        cout << "슬라임이 나타났습니다!" << endl; // 슬라임 등장 대사 출력
        Monster::printInfo(); // 슬라임의 스탯 출력
    }
};

// Goblin 클래스 (Monster의 상속 클래스)
class Goblin : public Monster
{
public:
    Goblin(int playerLevel) : Monster("고블린", playerLevel) {}

    void printInfo() const override
    {
        cout << "고블린이 나타났습니다!" << endl; // 고블린 등장 대사 출력
        Monster::printInfo(); // 고블린의 스탯 출력
    }
};

// Orc 클래스 (Monster의 상속 클래스)
class Orc : public Monster
{
public:
    Orc(int playerLevel) : Monster("오크", playerLevel) {}

    void printInfo() const override
    {
        cout << "오크가 나타났습니다!" << endl; // 오크 등장 대사 출력
        Monster::printInfo(); // 오크의 스탯 출력
    }
};

// Troll 클래스 (Monster의 상속 클래스)
class Troll : public Monster
{
public:
    Troll(int playerLevel) : Monster("트롤", playerLevel) {}

    void printInfo() const override
    {
        cout << "트롤이 나타났습니다!" << endl; // 트롤 등장 대사 출력
        Monster::printInfo(); // 트롤의 스탯 출력
    }
};

// Hatchling 보스 클래스 (Monster의 상속 클래스)
class Hatchling : public Monster
{
public:
    Hatchling() : Monster("해츨링", 10) // 보스 몬스터(해츨링)의 레벨은 10으로 고정 (플레이어의 레벨이 10일때만 조우)
    {
        hp = rand() % (10 * 45 - 10 * 30 + 1) + 10 * 30; // 체력: 레벨*30 ~ 레벨*45
        attack = rand() % (10 * 15 - 10 * 8 + 1) + 10 * 8; // 공격력: 레벨*8 ~ 레벨*15
    }

    void printInfo() const override
    {
        cout << "보스 몬스터 - 해츨링이 나타났습니다!" << endl; // 보스 몬스터 - 해츨링 등장 대사 출력
        Monster::printInfo(); // 보스 몬스터 - 해츨링의 스탯 출력
    }
};

// 몬스터 생성 및 조우 함수
// 플레이어의 레벨에 따라 만나는 몬스터의 종류가 달라지도록 설정
void encounterMonster(int playerLevel) {
    if (playerLevel == 3)
    {
        // 레벨 3에서 슬라임 또는 고블린을 랜덤하게 조우
        int randomChoice = rand() % 2;  // 0 또는 1을 랜덤하게 생성
        if (randomChoice == 0)
        {
            Slime slime(playerLevel); // 플레이어의 레벨을 입력받고 슬라임의 스탯을 결정
            slime.printInfo();
        }
        else
        {
            Goblin goblin(playerLevel); // 플레이어의 레벨을 입력받고 고블린의 스탯을 결정
            goblin.printInfo();
        }
    }
    else if (playerLevel == 5)
    {
        // 레벨 5에서 고블린 또는 오크를 랜덤하게 조우
        int randomChoice = rand() % 2;  // 0 또는 1을 랜덤하게 생성
        if (randomChoice == 0)
        {
            Goblin goblin(playerLevel); // 플레이어의 레벨을 입력받고 고블린의 스탯을 결정
            goblin.printInfo();
        }
        else
        {
            Orc orc(playerLevel); // 플레이어의 레벨을 입력받고 오크의 스탯을 결정
            orc.printInfo();
        }
    }
    else if (playerLevel == 7)
    {
        // 레벨 7에서 오크 또는 트롤을 랜덤하게 조우
        int randomChoice = rand() % 2;  // 0 또는 1을 랜덤하게 생성
        if (randomChoice == 0)
        {
            Orc orc(playerLevel); // 플레이어의 레벨을 입력받고 오크의 스탯을 결정
            orc.printInfo();
        }
        else
        {
            Troll troll(playerLevel); // 플레이어의 레벨을 입력받고 트롤의 스탯을 결정
            troll.printInfo();
        }
    }
    // 
    else if (playerLevel >= 1 && playerLevel <= 2)
    {
        Slime slime(playerLevel); // 플레이어의 레벨을 입력받고 슬라임의 스탯을 결정
        slime.printInfo();
    }
    else if (playerLevel == 4)
    {
        Goblin goblin(playerLevel); // 플레이어의 레벨을 입력받고 고블린의 스탯을 결정
        goblin.printInfo();
    }
    else if (playerLevel == 6)
    {
        Orc orc(playerLevel); // 플레이어의 레벨을 입력받고 오크의 스탯을 결정
        orc.printInfo();
    }
    else if (playerLevel >= 8 && playerLevel <= 9)
    {
        Troll troll(playerLevel); // 플레이어의 레벨을 입력받고 트롤의 스탯을 결정
        troll.printInfo();
    }
    else if (playerLevel == 10)
    {
        Hatchling hatchling;  // 보스 몬스터의 레벨은 10으로 고정이기에, 플레이어의 레벨을 입력받지 않음
        hatchling.printInfo();
    }
}

int main()
{


    return 0;
}
