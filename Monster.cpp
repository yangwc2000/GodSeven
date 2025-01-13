#include "Monster.h"
#include "Hero.h" // Hero 클래스 참조를 위해 추가
#include <string>
#include <vector>
#include <random> // 랜덤 숫자 생성을 위해 추가
#include <algorithm>

Goblin::Goblin(int level) : level(level) {
    name = "고블린";
    health = 50 + level * 10;
    attack = 5 + level * 2;
}

std::string Goblin::getName() const { return name; }
int Goblin::getHealth() const { return health; }
int Goblin::getAttack() const { return attack; }
void Goblin::takeDamage(int damage, Hero* player) {
    health -= damage;
    if (health < 0) health = 0;
    std::cout << name << "이(가) " << damage << "의 피해를 입었습니다. 남은 체력: " << health << std::endl;
    if (health == 0) {
        std::cout << name << "이(가) 쓰러졌습니다." << std::endl;
        int experience = (level * 10) / player->getLevel(); // 경험치 계산
        std::cout << "플레이어가 " << experience << " 경험치를 얻었습니다." << std::endl;
        player->gainExperience(experience); // 플레이어에게 경험치 추가
    }
}
int Goblin::getLevel() const { return level; }
std::string Goblin::getDropItem() const { return "고블린의 이빨"; }
void Goblin::draw() const {
    std::cout << "    _.--\"\"--._    " << std::endl;
    std::cout << "  .'          `.  " << std::endl;
    std::cout << " /   (o)  (o)   \\ " << std::endl;
    std::cout << "|    \\  ^^  /    |" << std::endl;
    std::cout << " \\    `----'    / " << std::endl;
    std::cout << "  `. _______ .'  " << std::endl;
    std::cout << "    //_____\\    " << std::endl;
}

Orc::Orc(int level) : level(level) {
    name = "오크";
    health = 80 + level * 15;
    attack = 8 + level * 3;
}

std::string Orc::getName() const { return name; }
int Orc::getHealth() const { return health; }
int Orc::getAttack() const { return attack; }
void Orc::takeDamage(int damage, Hero* player) {
    health -= damage;
    if (health < 0) health = 0;
    std::cout << name << "이(가) " << damage << "의 피해를 입었습니다. 남은 체력: " << health << std::endl;
    if (health == 0) {
        std::cout << name << "이(가) 쓰러졌습니다." << std::endl;
        int experience = (level * 15) / player->getLevel(); // 경험치 계산
        std::cout << "플레이어가 " << experience << " 경험치를 얻었습니다." << std::endl;
        player->gainExperience(experience); // 플레이어에게 경험치 추가
    }
}
int Orc::getLevel() const { return level; }
std::string Orc::getDropItem() const { return "오크의 가죽"; }
void Orc::draw() const {
    std::cout << "     _.--\"\"--._     " << std::endl;
    std::cout << "   .'          `.   " << std::endl;
    std::cout << "  /   O      O   \\  " << std::endl; // 눈
    std::cout << " |    \\  ^^  /    | " << std::endl; // 입
    std::cout << " \\     `----'     / " << std::endl;
    std::cout << "  `. _______ .'   " << std::endl;
    std::cout << "    //_____\\     " << std::endl;
    std::cout << "   (( ____ ))    " << std::endl;
    std::cout << "    `------'     " << std::endl;
}

Troll::Troll(int level) : level(level) {
    name = "트롤";
    health = 120 + level * 20;
    attack = 12 + level * 4;
}

std::string Troll::getName() const { return name; }
int Troll::getHealth() const { return health; }
int Troll::getAttack() const { return attack; }
void Troll::takeDamage(int damage, Hero* player) {
    health -= damage;
    if (health < 0) health = 0;
    std::cout << name << "이(가) " << damage << "의 피해를 입었습니다. 남은 체력: " << health << std::endl;
    if (health == 0) {
        std::cout << name << "이(가) 쓰러졌습니다." << std::endl;
        int experience = (level * 20) / player->getLevel(); // 경험치 계산
        std::cout << "플레이어가 " << experience << " 경험치를 얻었습니다." << std::endl;
        player->gainExperience(experience); // 플레이어에게 경험치 추가
    }
}
int Troll::getLevel() const { return level; }
std::string Troll::getDropItem() const { return "트롤의 뼈"; }
void Troll::draw() const {
    std::cout << "        _.--\"\"--._        " << std::endl;
    std::cout << "      .'          `.      " << std::endl;
    std::cout << "     /   O      O   \\     " << std::endl;
    std::cout << "    |    \\  ^^  /    |    " << std::endl;
    std::cout << "     \\    `----'    /     " << std::endl;
    std::cout << "      `. _______ .'      " << std::endl;
    std::cout << "        //_____\\        " << std::endl;
    std::cout << "       (( ____ ))       " << std::endl;
    std::cout << "        `------'        " << std::endl;
    std::cout << "      /   ||   \\      " << std::endl;
    std::cout << "     /____||____\\     " << std::endl;
    std::cout << "    /__________\\    " << std::endl;
}

Slime::Slime(int level) : level(level) {
    name = "슬라임";
    health = 30 + level * 5;
    attack = 3 + level * 1;
}

std::string Slime::getName() const { return name; }
int Slime::getHealth() const { return health; }
int Slime::getAttack() const { return attack; }
void Slime::takeDamage(int damage, Hero* player) {
    health -= damage;
    if (health < 0) health = 0;
    std::cout << name << "이(가) " << damage << "의 피해를 입었습니다. 남은 체력: " << health << std::endl;
    if (health == 0) {
        std::cout << name << "이(가) 쓰러졌습니다." << std::endl;
        int experience = (level * 5) / player->getLevel(); // 경험치 계산
        std::cout << "플레이어가 " << experience << " 경험치를 얻었습니다." << std::endl;
        player->gainExperience(experience); // 플레이어에게 경험치 추가
    }
}
int Slime::getLevel() const { return level; }
std::string Slime::getDropItem() const { return "슬라임 젤리"; }
void Slime::draw() const {
    std::cout << "  .--.  " << std::endl;
    std::cout << " / o.o \\ " << std::endl;
    std::cout << "|  > <  |" << std::endl;
    std::cout << " \\ --- / " << std::endl;
    std::cout << "  `---'  " << std::endl;
}

DragonHatchling::DragonHatchling(int level) : level(level) {
    name = "드래곤 해츨링";
    health = 200 + level * 25;
    attack = 20 + level * 5;
}

std::string DragonHatchling::getName() const { return name; }
int DragonHatchling::getHealth() const { return health; }
int DragonHatchling::getAttack() const { return attack; }
void DragonHatchling::takeDamage(int damage, Hero* player) {
    health -= damage;
    if (health < 0) health = 0;
    std::cout << name << "이(가) " << damage << "의 피해를 입었습니다. 남은 체력: " << health << std::endl;
    if (health == 0) {
        std::cout << name << "이(가) 쓰러졌습니다." << std::endl;
        int experience = (level * 25) / player->getLevel(); // 경험치 계산
        std::cout << "플레이어가 " << experience << " 경험치를 얻었습니다." << std::endl;
        player->gainExperience(experience); // 플레이어에게 경험치 추가
    }
}
int DragonHatchling::getLevel() const { return level; }
std::string DragonHatchling::getDropItem() const { return "드래곤의 비늘"; }
void DragonHatchling::draw() const {
    std::cout << "      /\\_/\\     " << std::endl;
    std::cout << "     ( o.o )    " << std::endl;
    std::cout << "    > ^ <      " << std::endl;
    std::cout << "   /   \\      " << std::endl;
    std::cout << "  (( ____ ))   " << std::endl;
    std::cout << "   `------'    " << std::endl;
}

Monster* generateMonster(int playerLevel) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int monsterType;
    int monsterLevel;

    if (playerLevel < 3) {
        monsterType = 0; // 슬라임
        std::uniform_int_distribution<> distrib(1, clamp(playerLevel, 1, 3));
        monsterLevel = distrib(gen);
    }
    else if (playerLevel < 5) {
        monsterType = 1; // 고블린
        std::uniform_int_distribution<> distrib(3, clamp(playerLevel + 2, 3, 5));
        monsterLevel = distrib(gen);
    }
    else if (playerLevel < 7) {
        monsterType = 2; // 오크
        std::uniform_int_distribution<> distrib(5, clamp(playerLevel + 2, 5, 7));
        monsterLevel = distrib(gen);
    }
    else if (playerLevel < 10) {
        monsterType = 3; // 트롤
        std::uniform_int_distribution<> distrib(7, clamp(playerLevel + 2, 7, 9));
        monsterLevel = distrib(gen);
    }
    else {
        monsterType = 4; // 드래곤 해츨링
        std::uniform_int_distribution<> distrib(10, 10);
        monsterLevel = distrib(gen);
    }

    switch (monsterType) {
    case 0: return new Slime(monsterLevel);
    case 1: return new Goblin(monsterLevel);
    case 2: return new Orc(monsterLevel);
    case 3: return new Troll(monsterLevel);
    case 4: return new DragonHatchling(monsterLevel);
    default: return nullptr;
    }
}
