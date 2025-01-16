#include <iostream>
#include <string>
#include <vector>
#include "Item.h"



class Character {
private:
    // 멤버 변수
    std::string name;
    int level;
    int health;
    int maxHealth;
    int attack;
    int experience;
    int gold;
    std::vector<Item*> inventory; // 인벤토리 추가

    // 싱글톤 인스턴스
    static Character* instance;

    // 생성자를 private으로 설정
    Character(const std::string& name)
        : name(name), level(1), health(200), maxHealth(200),
        attack(30), experience(0), gold(0) {
    }

public:
    // 싱글톤 인스턴스를 반환하는 메소드
    static Character* getInstance(const std::string& name = "") {
        if (instance == nullptr) {
            instance = new Character(name);
        }
        return instance;
    }

    // 캐릭터 상태 출력 메소드
    void displayStatus() const {
        std::cout << "이름: " << name
            << ", 레벨: " << level
            << ", 체력: " << health << "/" << maxHealth
            << ", 공격력: " << attack
            << ", 경험치: " << experience
            << ", 골드: " << gold << std::endl;
    }

    // 아이템 추가 메소드
    void addItem(Item* item) {
        inventory.push_back(item);
    }

    // 아이템 제거 메소드
    void removeItem(int index) {
        if (index >= 0 && index < inventory.size()) {
            delete inventory[index];
            inventory.erase(inventory.begin() + index);
        }
    }

    // 인벤토리 출력 메소드
    void printInventory() const {
        for (int i = 0; i < inventory.size(); ++i) {
            std::cout << i << ": " << inventory[i]->getName() << std::endl;
        }
    }

    // 아이템 사용 메소드
    void useItem(int index) {
        if (index >= 0 && index < inventory.size()) {
            inventory[index]->use(this);
            removeItem(index);
        }
    }

    // 골드 추가 메소드
    void addGold(int amount) {
        gold += amount;
    }

    // 골드 반환 메소드
    int getGold() const {
        return gold;
    }

    // 경험치 추가 메소드
    void addExperience(int amount) {
        experience += amount;
    }

    // 레벨 반환 메소드
    int getLevel() const {
        return level;
    }

    // 체력 반환 메소드
    int getHealth() const {
        return health;
    }

    // 공격력 반환 메소드
    int getAttack() const {
        return attack;
    }

    // 데미지 처리 메소드
    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    // 레벨업 메소드
    void levelUp() {
        if (experience >= level * 100) {
            level++;
            maxHealth += 20;
            attack += 5;
            health = maxHealth;
            std::cout << "레벨업! 현재 레벨: " << level << std::endl;
        }
    }

    // 아이템 반환 메소드
    Item* getItem(int index) const {
        if (index >= 0 && index < inventory.size()) {
            return inventory[index];
        }
        return nullptr;
    }
};

// 싱글톤 인스턴스 초기화
Character* Character::instance = nullptr;

// 메인 함수
int main() {
    std::string playerName;

    // 사용자로부터 이름 입력 받기
    std::cout << "캐릭터의 이름을 입력하세요: ";
    std::getline(std::cin, playerName);

    // 캐릭터 생성
    Character* player = Character::getInstance(playerName);

    // 상태 출력
    player->displayStatus();

    return 0;
}
