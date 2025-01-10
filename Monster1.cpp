#include <iostream>
#include <string>
#include <vector>
#include <random> // 랜덤 숫자 생성을 위해 추가
#include <algorithm> // std::clamp 사용
#include <cmath> // std::abs 사용

// std::clamp가 C++17에서 추가되었으므로, C++17 이상을 사용해야 합니다.
// 만약 C++17 이상을 사용하지 않는다면, 다음과 같이 직접 clamp 함수를 정의할 수 있습니다.
template <typename T>
const T& clamp(const T& v, const T& lo, const T& hi) {
    return std::max(lo, std::min(v, hi));
}

using namespace std;

class Monster {
public:
    virtual ~Monster() = default;

    virtual std::string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual int getAttack() const = 0;
    virtual void takeDamage(int damage) = 0;
    virtual int getLevel() const = 0; //몬스터 레벨 추가

protected:
    std::string name;
    int health;
    int attack;
    int level;
};

// Goblin 클래스 (이전 코드와 거의 동일, 레벨 변수 추가)
class Goblin : public Monster {
public:
    Goblin(int level) : level(level) {
        name = "고블린";
        health = 50 + level * 10;
        attack = 5 + level * 2;
    }

    std::string getName() const override { return name; }
    int getHealth() const override { return health; }
    int getAttack() const override { return attack; }
    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << "이(가) " << damage << "의 피해를 입었습니다. 남은 체력: " << health << std::endl;
    }
    int getLevel() const override { return level; }
private:
    int level;
};

// Orc 클래스 (이전 코드와 거의 동일, 레벨 변수 추가)
class Orc : public Monster {
public:
    Orc(int level) : level(level) {
        name = "오크";
        health = 80 + level * 15;
        attack = 8 + level * 3;
    }

    std::string getName() const override { return name; }
    int getHealth() const override { return health; }
    int getAttack() const override { return attack; }
    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << "이(가) " << damage << "의 피해를 입었습니다. 남은 체력: " << health << std::endl;
    }
    int getLevel() const override { return level; }
private:
    int level;
};

// Troll 클래스 (이전 코드와 거의 동일, 레벨 변수 추가)
class Troll : public Monster {
public:
    Troll(int level) : level(level) {
        name = "트롤";
        health = 120 + level * 20;
        attack = 12 + level * 4;
    }

    std::string getName() const override { return name; }
    int getHealth() const override { return health; }
    int getAttack() const override { return attack; }
    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << "이(가) " << damage << "의 피해를 입었습니다. 남은 체력: " << health << std::endl;
    }
    int getLevel() const override { return level; }
private:
    int level;
};

// Slime 클래스 (이전 코드와 거의 동일, 레벨 변수 추가)
class Slime : public Monster {
public:
    Slime(int level) : level(level) {
        name = "슬라임";
        health = 30 + level * 5;
        attack = 3 + level * 1;
    }

    std::string getName() const override { return name; }
    int getHealth() const override { return health; }
    int getAttack() const override { return attack; }
    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << "이(가) " << damage << "의 피해를 입었습니다. 남은 체력: " << health << std::endl;
    }
    int getLevel() const override { return level; }
private:
    int level;
};

// DragonHatchling 클래스 추가
class DragonHatchling : public Monster {
public:
    DragonHatchling(int level) : level(level) {
        name = "드래곤(해츨링)";
        health = 200 + level * 25;
        attack = 20 + level * 6;
    }

    std::string getName() const override { return name; }
    int getHealth() const override { return health; }
    int getAttack() const override { return attack; }
    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << "이(가) " << damage << "의 피해를 입었습니다. 남은 체력: " << health << std::endl;
    }
    int getLevel() const override { return level; }
private:
    int level;
};

// 몬스터 생성 함수
Monster* generateMonster(int playerLevel) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int monsterType;
    int monsterLevel;

    if (playerLevel < 3) {
        monsterType = 0; // 슬라임
        std::uniform_int_distribution<> distrib(1, clamp(playerLevel, 1, 3)); //플레이어 레벨을 최소 1, 최대 3으로 제한
        monsterLevel = distrib(gen);
    }
    else if (playerLevel < 5) {
        monsterType = 1; // 고블린
        std::uniform_int_distribution<> distrib(3, clamp(playerLevel + 2, 3, 5)); //플레이어 레벨+2를 최소 3, 최대 5로 제한
        monsterLevel = distrib(gen);
    }
    else if (playerLevel < 7) {
        monsterType = 2; // 오크
        std::uniform_int_distribution<> distrib(5, clamp(playerLevel + 2, 5, 7)); //플레이어 레벨+2를 최소 5, 최대 7으로 제한
        monsterLevel = distrib(gen);
    }
    else if (playerLevel < 10) {
        monsterType = 3; // 트롤
        std::uniform_int_distribution<> distrib(7, clamp(playerLevel + 2, 7, 9)); //플레이어 레벨+2를 최소 7, 최대 9로 제한
        monsterLevel = distrib(gen);
    }
    else {
        monsterType = 4; // 드래곤 해츨링
        std::uniform_int_distribution<> distrib(10, 10); // 플레이어 레벨이 10일 때 드래곤 해츨링의 레벨은 10
        monsterLevel = distrib(gen);
    }

    switch (monsterType) {
    case 0: return new Slime(monsterLevel);
    case 1: return new Goblin(monsterLevel);
    case 2: return new Orc(monsterLevel);
    case 3: return new Troll(monsterLevel);
    case 4: return new DragonHatchling(monsterLevel);
    default: return nullptr; // 예외 처리
    }
}

int main() {
    for (int i = 1; i <= 10; ++i) {
        std::cout << "플레이어 레벨: " << i << std::endl;
        Monster* monster = generateMonster(i);
        if (monster != nullptr) {
            std::cout << "조우한 몬스터: " << monster->getName() << ", 레벨: " << monster->getLevel() << std::endl;
            delete monster;
        }
        std::cout << "--------------------" << std::endl;
    }
    return 0;
}
