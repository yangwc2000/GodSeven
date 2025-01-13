// Boss.h
#pragma once
#include "Monster.h"
#include <string>

class Dragon : public Monster {
public:
    Dragon();
    virtual ~Dragon() {}

    // 드래곤 고유 공격 연출 등을 메서드로 만들 수도 있음
    void breathAttack();
};

