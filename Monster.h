#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

template <typename T>
const T& clamp(const T& v, const T& lo, const T& hi) {
    return std::max(lo, std::min(v, hi));
}

class Hero; // Hero 클래스 전방 선언

class Monster {
public:
    virtual ~Monster() = default;

    virtual std::string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual int getAttack() const = 0;
    virtual void takeDamage(int damage, Hero* player) = 0; // player 매개변수 추가
    virtual int getLevel() const = 0;
    virtual std::string getDropItem() const = 0;
    virtual void draw() const = 0;

protected:
    std::string name;
    int health = 0; // 초기화
    int attack = 0; // 초기화
    int level = 0;  // 초기화
};

class Goblin : public Monster {
public:
    Goblin(int level);
    std::string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    void takeDamage(int damage, Hero* player) override; // player 매개변수 추가
    int getLevel() const override;
    std::string getDropItem() const override;
    void draw() const override;

private:
    int level;
};

class Orc : public Monster {
public:
    Orc(int level);
    std::string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    void takeDamage(int damage, Hero* player) override; // player 매개변수 추가
    int getLevel() const override;
    std::string getDropItem() const override;
    void draw() const override;

private:
    int level;
};

class Troll : public Monster {
public:
    Troll(int level);
    std::string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    void takeDamage(int damage, Hero* player) override; // player 매개변수 추가
    int getLevel() const override;
    std::string getDropItem() const override;
    void draw() const override;

private:
    int level;
};

class Slime : public Monster {
public:
    Slime(int level);
    std::string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    void takeDamage(int damage, Hero* player) override; // player 매개변수 추가
    int getLevel() const override;
    std::string getDropItem() const override;
    void draw() const override;

private:
    int level;
};

class DragonHatchling : public Monster {
public:
    DragonHatchling(int level);
    std::string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    void takeDamage(int damage, Hero* player) override; // player 매개변수 추가
    int getLevel() const override;
    std::string getDropItem() const override;
    void draw() const override;

private:
    int level;
};

Monster* generateMonster(int playerLevel);

#endif // MONSTER_H
