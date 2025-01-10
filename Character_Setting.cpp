#include <iostream>
#include <string>

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
