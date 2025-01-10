#include <iostream>
#include <string>
#include <vector>
#include <random> // ���� ���� ������ ���� �߰�
#include <algorithm> // std::clamp ���
#include <cmath> // std::abs ���

// std::clamp�� C++17���� �߰��Ǿ����Ƿ�, C++17 �̻��� ����ؾ� �մϴ�.
// ���� C++17 �̻��� ������� �ʴ´ٸ�, ������ ���� ���� clamp �Լ��� ������ �� �ֽ��ϴ�.
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
    virtual int getLevel() const = 0; //���� ���� �߰�

protected:
    std::string name;
    int health;
    int attack;
    int level;
};

// Goblin Ŭ���� (���� �ڵ�� ���� ����, ���� ���� �߰�)
class Goblin : public Monster {
public:
    Goblin(int level) : level(level) {
        name = "���";
        health = 50 + level * 10;
        attack = 5 + level * 2;
    }

    std::string getName() const override { return name; }
    int getHealth() const override { return health; }
    int getAttack() const override { return attack; }
    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << "��(��) " << damage << "�� ���ظ� �Ծ����ϴ�. ���� ü��: " << health << std::endl;
    }
    int getLevel() const override { return level; }
private:
    int level;
};

// Orc Ŭ���� (���� �ڵ�� ���� ����, ���� ���� �߰�)
class Orc : public Monster {
public:
    Orc(int level) : level(level) {
        name = "��ũ";
        health = 80 + level * 15;
        attack = 8 + level * 3;
    }

    std::string getName() const override { return name; }
    int getHealth() const override { return health; }
    int getAttack() const override { return attack; }
    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << "��(��) " << damage << "�� ���ظ� �Ծ����ϴ�. ���� ü��: " << health << std::endl;
    }
    int getLevel() const override { return level; }
private:
    int level;
};

// Troll Ŭ���� (���� �ڵ�� ���� ����, ���� ���� �߰�)
class Troll : public Monster {
public:
    Troll(int level) : level(level) {
        name = "Ʈ��";
        health = 120 + level * 20;
        attack = 12 + level * 4;
    }

    std::string getName() const override { return name; }
    int getHealth() const override { return health; }
    int getAttack() const override { return attack; }
    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << "��(��) " << damage << "�� ���ظ� �Ծ����ϴ�. ���� ü��: " << health << std::endl;
    }
    int getLevel() const override { return level; }
private:
    int level;
};

// Slime Ŭ���� (���� �ڵ�� ���� ����, ���� ���� �߰�)
class Slime : public Monster {
public:
    Slime(int level) : level(level) {
        name = "������";
        health = 30 + level * 5;
        attack = 3 + level * 1;
    }

    std::string getName() const override { return name; }
    int getHealth() const override { return health; }
    int getAttack() const override { return attack; }
    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << "��(��) " << damage << "�� ���ظ� �Ծ����ϴ�. ���� ü��: " << health << std::endl;
    }
    int getLevel() const override { return level; }
private:
    int level;
};

// DragonHatchling Ŭ���� �߰�
class DragonHatchling : public Monster {
public:
    DragonHatchling(int level) : level(level) {
        name = "�巡��(������)";
        health = 200 + level * 25;
        attack = 20 + level * 6;
    }

    std::string getName() const override { return name; }
    int getHealth() const override { return health; }
    int getAttack() const override { return attack; }
    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << "��(��) " << damage << "�� ���ظ� �Ծ����ϴ�. ���� ü��: " << health << std::endl;
    }
    int getLevel() const override { return level; }
private:
    int level;
};

// ���� ���� �Լ�
Monster* generateMonster(int playerLevel) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int monsterType;
    int monsterLevel;

    if (playerLevel < 3) {
        monsterType = 0; // ������
        std::uniform_int_distribution<> distrib(1, clamp(playerLevel, 1, 3)); //�÷��̾� ������ �ּ� 1, �ִ� 3���� ����
        monsterLevel = distrib(gen);
    }
    else if (playerLevel < 5) {
        monsterType = 1; // ���
        std::uniform_int_distribution<> distrib(3, clamp(playerLevel + 2, 3, 5)); //�÷��̾� ����+2�� �ּ� 3, �ִ� 5�� ����
        monsterLevel = distrib(gen);
    }
    else if (playerLevel < 7) {
        monsterType = 2; // ��ũ
        std::uniform_int_distribution<> distrib(5, clamp(playerLevel + 2, 5, 7)); //�÷��̾� ����+2�� �ּ� 5, �ִ� 7���� ����
        monsterLevel = distrib(gen);
    }
    else if (playerLevel < 10) {
        monsterType = 3; // Ʈ��
        std::uniform_int_distribution<> distrib(7, clamp(playerLevel + 2, 7, 9)); //�÷��̾� ����+2�� �ּ� 7, �ִ� 9�� ����
        monsterLevel = distrib(gen);
    }
    else {
        monsterType = 4; // �巡�� ������
        std::uniform_int_distribution<> distrib(10, 10); // �÷��̾� ������ 10�� �� �巡�� �������� ������ 10
        monsterLevel = distrib(gen);
    }

    switch (monsterType) {
    case 0: return new Slime(monsterLevel);
    case 1: return new Goblin(monsterLevel);
    case 2: return new Orc(monsterLevel);
    case 3: return new Troll(monsterLevel);
    case 4: return new DragonHatchling(monsterLevel);
    default: return nullptr; // ���� ó��
    }
}

int main() {
    for (int i = 1; i <= 10; ++i) {
        std::cout << "�÷��̾� ����: " << i << std::endl;
        Monster* monster = generateMonster(i);
        if (monster != nullptr) {
            std::cout << "������ ����: " << monster->getName() << ", ����: " << monster->getLevel() << std::endl;
            delete monster;
        }
        std::cout << "--------------------" << std::endl;
    }
    return 0;
}
