#include <iostream>
#include <string>

using namespace std;

class Character {
private:
    string name; // 캐릭터 이름
    int level; // 캐릭터 레벨
    int health; // 캐릭터 체력
    int maxHealth; // 최대 체력
    int attack; // 캐릭터 공격력
    int experience; // 경험치
    int gold; // 골드

    static Character* instance; // 싱글톤 인스턴스

    // 생성자는 private으로 설정되어 외부에서 호출 불가
    Character(const string& name)
        : name(name), level(1), health(200), maxHealth(200),
        attack(30), experience(0), gold(0) {
    }

public:
    // 싱글톤 인스턴스를 반환하는 메서드
    static Character* getInstance(const string& name = "") {
        if (instance == nullptr) {
            instance = new Character(name);
        }
        return instance;
    }

    // 캐릭터 상태 출력 함수
    void displayStatus() const {
        cout << "이름: " << name
            << ", 레벨: " << level
            << ", 체력: " << health << "/" << maxHealth
            << ", 공격력: " << attack
            << ", 경험치: " << experience
            << ", 골드: " << gold << endl;
    }

    // 접근자 메서드 (getters)
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getAttack() const { return attack; }

    // 수정자 메서드 (setters)
    void setHealth(int h) { health = h; }
    void setAttack(int a) { attack = a; }
};

// 싱글톤 인스턴스 초기화
Character* Character::instance = nullptr;
